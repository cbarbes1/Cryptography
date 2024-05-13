/*
* Author: Cole Barbes
* Last Edited: 5/2/24
* Purpose: To implement trial divisors in mpi using ranges of test numbers
*/
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

    double start_time = MPI_Wtime(); // start the timer
    
    int size = strlen(argv[1])+1;
    char number[size];
    InfInt range_size;
    InfInt start;
    bool found = false;

    // print check for problems later on 
    InfInt n_value = std::string(argv[1]);
    InfInt ceiling = n_value.intSqrt();

    //get the ranges that the processes will test for factor
    get_range(ceiling, world_rank, world_size, &start, &range_size);
    InfInt end = range_size + start;
    printf("Here is my start and my size: %s %s %s\n", start.toString().c_str(), end.toString().c_str(),range_size.toString().c_str());

    InfInt factor = -1;
    for (InfInt i = start; i <= (start + range_size - 1) && !found; i++)
    {
        // if find a factor then set found and set the factor
        if (n_value % i == 0)
        {
            factor = i;
            found = true;
        }
        
    }
    MPI_Bcast(&found, 1, MPI_C_BOOL, 0, MPI_COMM_WORLD);
    if(factor != -1){
        std::string temp = factor.toString();
        printf("I am rank %d sending %s\n", world_rank, temp.c_str());
        double end_time = MPI_Wtime(); // Stop the timer
        
        std::cout << "Total execution time: " << (end_time - start_time) << " seconds." << std::endl;
    }
    
    MPI_Finalize();
}