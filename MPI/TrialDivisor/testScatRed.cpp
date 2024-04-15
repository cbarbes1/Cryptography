#include "mpi.h"
#include <iostream>
#include <cmath>
#include <vector>


int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // The root process defines the array to be scattered
    int root = 0;
    int *array = NULL;
    int n = 20; // Total number of elements in the array
    int sub_array_size = n / world_size; // Size of sub-array for each process
    int *sub_array = (int*) malloc(sizeof(int) * sub_array_size);
    int *result_array = NULL;

    if (world_rank == root) {
        array = (int*) malloc(sizeof(int) * n);
        result_array = (int*) malloc(sizeof(int) * n);
        // Initialize the array with some values
        for (int i = 0; i < n; i++) {
            array[i] = i;
        }
    }

    // Scatter the array to all processes
    MPI_Scatter(array, sub_array_size, MPI_INT, sub_array, sub_array_size, MPI_INT, root, MPI_COMM_WORLD);

    // Each process computes the square of each element
    for (int i = 0; i < sub_array_size; i++) {
        sub_array[i] = sub_array[i] * sub_array[i];
    }

    // Gather the results back to the root process
    MPI_Gather(sub_array, sub_array_size, MPI_INT, result_array, sub_array_size, MPI_INT, root, MPI_COMM_WORLD);

    // Root process prints the result
    if (world_rank == root) {
        printf("Result array:\n");
        for (int i = 0; i < n; i++) {
            printf("%d ", result_array[i]);
        }
        printf("\n");

        free(array);
        free(result_array);
    }

    free(sub_array);
    MPI_Finalize();
}
