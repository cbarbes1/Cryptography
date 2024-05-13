#include "mpi.h"
#include <iostream>
#include <cmath>

void err_sys(MPI_Comm comm, const char *err){
    printf("%s\n", err);
    MPI_Abort(comm, 0);
}

int main(int argc, char** argv)
{
    int world_size, world_rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int number;

    if(world_rank == 0){
        printf("Hello my children I am your father at rank %d\n", world_rank );
        if(argc < 2){
            err_sys(MPI_COMM_WORLD,"Too few Arguments");
        }
        number = atoi(argv[1]);
    }
    MPI_Bcast(&number, 1, MPI_INT, 0, MPI_COMM_WORLD);
    printf("Process %d recieved data : %d\n", world_rank, number);
    
    MPI_Finalize();
    return 0;
}