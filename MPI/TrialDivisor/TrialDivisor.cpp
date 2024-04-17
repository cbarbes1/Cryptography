#include "mpi.h"
#include <iostream>
#include <cmath>
#include <vector>


//vector<int> factor_range(int, int, int); // function to factor numbers in a given range

int main(int argc, char** argv)
{
    srand(time(0));
    int world_size, world_rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // int number = static_cast<int>(sqrt(atoi(argv[1])));
    // int range_size = number / world_size;
    // int start = world_rank + (range_size*world_rank) + 1;
    // int end = range_size + (world_rank*range_size);

    if(argc != 2){
        printf("Insufficient Argument's");
        exit(0);
    }

    // The root process defines the array to be scattered
    int root = 0;
    
    int *array = NULL;
    
    int *sub_array = (int*) malloc(sizeof(int)*1);
    int *result_array = NULL;
    int number = static_cast<int>(sqrt(atoi(argv[1])));
    

    if (world_rank == root) {
        array = (int*) malloc(sizeof(int) * world_size);
        result_array = (int*) malloc(sizeof(int) * world_size);
        int range = number / world_size;
        int end = number;
        // Initialize the array with the test factors
        for (int i = 0; i <world_size; i++) {
            // end = end-range;
            array[i] = rand()%(end)+1;
            
        }
    }

    // Scatter the array to all processes
    MPI_Scatter(array, 1, MPI_INT, sub_array, 1, MPI_INT, root, MPI_COMM_WORLD);
    
    // for (int i = 0; i < sub_array_size; i++) {
        
    // if(number%sub_array[world_rank-1] != 0){
    //     sub_array[world_rank-1] = 0;
    // }

    // Gather the results back to the root process
    MPI_Gather(sub_array, 1, MPI_INT, result_array, 1, MPI_INT, root, MPI_COMM_WORLD);

    // Root process prints the result
    if (world_rank == root) {
        printf("Result array:\n");
        for (int i = 0; i < world_size; i++) {
            printf("%d ", result_array[i]);
        }
        printf("\n");

        free(array);
        free(result_array);
    }

    free(sub_array);
    
    MPI_Finalize();
}