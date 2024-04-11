#include "mpi.h"
#include <iostream>
#include <cmath>
#include <vector>

//vector<int> factor_range(int, int, int); // function to factor numbers in a given range

int main(int argc, char** argv)
{
    int world_size, world_rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int number = static_cast<int>(sqrt(atoi(argv[1])));
    int range_size = number / world_size;
    int start = world_rank + (range_size*world_rank) + 1;
    int end = range_size + (world_rank*range_size);

    printf("Process %d computing range[ %d, %d ]\n", world_rank, start, end);

    for(int i = start; i<=end; i++){
        if(number % i == 0){
            printf("Process %d found factor: %d\n", world_rank, i);
        }
        //sleep(6);
    }
    
    MPI_Finalize();
}

/*
*   Given a number and a range to factor this function will find a factor of a number using trial division
*   Parameters: the number, the start of the 
*/
// vector<int> factor_range(int start, int end, int number){
//     vector<int>
//     for(int i = start; i<=end; i++){
//         if(number % i == 0){
            
//         }
//     }

//     return 0;
// }