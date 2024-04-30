#include "mpi.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include "../InfInt.h"
#include "omp.h"
#include "../utilities/utilities.h"

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

    
    MPI_Finalize();
    return 0;
}
