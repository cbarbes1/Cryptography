#include "mpi.h"
#include <iostream>
#include <cmath>
#include <vector>

void get_range(int number, int world_rank, int world_size, int *start, int *size)
{
    *start = number / world_size * (world_rank - 1) + 2;
    *size = number / world_size;
    if (world_rank == world_size - 1)
    {
        size += number % world_size;
    }
}

int main(int argc, char **argv)
{
    srand(time(0));

    if (argc != 2)
    {
        printf("Insufficient Argument's");
        exit(0);
    }

    // initialize MPI
    int world_size, world_rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // initialize local vars
    std::vector<int> number;
    int size;
    int range_size;
    int start;

    // if parent then add number parameter sqrt and the number
    // save the size
    if (world_rank == 0)
    {
        number.push_back(atoi(argv[1]));
        number.push_back(static_cast<int>(sqrt(atoi(argv[1]))));
        size = static_cast<int>(number.size());
    }

    // broadcast the size of the vector so each child knows how big to make the vector
    MPI_Bcast(&size, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // change size to the given size
    if (world_rank != 0)
    {
        number.resize(size);
    }

    // send the data and children recieve
    MPI_Bcast(number.data(), size, MPI_INT, 0, MPI_COMM_WORLD);
    // get the ranges that the children will test for factor
    if (world_rank != 0)
    {
        get_range(number[1], world_rank, world_size, &start, &range_size);
        printf("Here is my start and my size: %d %d\n", start, range_size);
    }

    MPI_Barrier(MPI_COMM_WORLD);

    if (world_rank == 0)
    {
        int test;
        MPI_Status status;
        MPI_Recv(&test, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
        
        printf("Recieved %d from rank %d \n", test, status.MPI_SOURCE);
        MPI_Abort(MPI_COMM_WORLD, 0);
    }
    else if (world_rank == 1)
    {
        int factor = -1;
        bool found = false;
        for (int i = start; i <= (start + range_size - 1) && !found; i++)
        {
            if (number[0] % i == 0)
            {
                factor = i;
                found = true;
            }
        }
        printf("I am rank %d sending %d\n", world_rank, factor);
        MPI_Send(&factor, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
}