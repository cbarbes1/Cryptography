#include "mpi.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include "../InfInt.h"
#include "omp.h"


void get_range(InfInt number, int world_rank, int world_size, InfInt *start, InfInt *size)
{
    *start = number / world_size * (world_rank) + 2;
    *size = number / world_size;
    if (world_rank == world_size - 1)
    {
        *size += number % world_size;
    }
}

int main(int argc, char **argv)
{
    srand(time(0));

    
    if (argc != 2)
    {
        printf("Insufficient Argument's");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    // initialize MPI
    int world_size, world_rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // #pragma omp parallel default(none) shared(world_rank, world_size)
    // {
    //     int thread_id = omp_get_thread_num();
    //     int num_threads = omp_get_num_threads();
    //     printf("Hello from thread %d out of %d in process %d out of %d\n", thread_id, num_threads, world_rank, world_size);
    // }
    
    int size = strlen(argv[1])+1;
    char number[size];
    InfInt range_size;
    InfInt start;
    bool found = false;

    // if parent then add number parameter sqrt and the number
    // save the size
    if (world_rank == 0)
    {
        strcpy(number, argv[1]);
        std::cout<<number<<std::endl;
    }
    // send the data and children recieve
    MPI_Bcast(number, size, MPI_CHAR, 0, MPI_COMM_WORLD);

    // print check for problems later on 
    InfInt n_value = std::string(number);
    // std::cout<<n_value<<std::endl;

    //get the ranges that the processes will test for factor
    get_range(n_value, world_rank, world_size, &start, &range_size);
    InfInt end = range_size + start;
    printf("Here is my start and my size: %s %s %s\n", start.toString().c_str(), end.toString().c_str(),range_size.toString().c_str());

    InfInt factor = -1;
    for (InfInt i = start; i <= (start + range_size - 1) && !found; i++)
    {
        if (n_value % i == 0)
        {
            factor = i;
            found = true;
        }
    }
    std::string temp = factor.toString();
    strcpy(number, temp.c_str());
    printf("I am rank %d sending %s\n", world_rank, number);
    MPI_Abort(MPI_COMM_WORLD, 1);
    
    

    MPI_Finalize();
}