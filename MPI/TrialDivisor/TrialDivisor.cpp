#include "mpi.h"
#include <iostream>
#include <cmath>

int factor_range(int, int, int); // function to factor numbers in a given range

int main(int argc, char** argv)
{
    // if(argc != 2){
    //     std::cerr<<"Invalid arguments!"<<std::endl;
    // }
    //int trial_count = atoi(argv[1]);
    std::cout<<"Starting Trial Divisor Factoring Algorithm"<<std::endl;
    MPI_Init(NULL, NULL);

    int world_size, world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    //int number_of_test = trial_count / world_size;

    printf("%d\n", world_rank);
    
    MPI_Finalize();
}

/*
*   Given a number and a range to factor this function will find a factor of a number using trial division
*   Parameters: the number, the start of the 
*/
int factor_range(int, int, int){

    return 0;
}