#include "mpi.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include "../InfInt.h"
#include "omp.h"
#include "../../utilities/utilities.h"

using namespace utilities;

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


    int size = strlen(argv[1])+1;
    char number[size];

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
    printf("Here is the number: %s\n", n_value.toString().c_str());

    //
    // Elliptic curve parallelized version:
    // broadcast the number and each node will factor the number using a curve 
    // each node will continually get new random curves until the factor is found 
    // Once a factor is found the process will broadcast to each of the other nodes to shutdown safely
    // If the 1000! bound is reached the 
    bool stop = false;
    bool found = false;
    InfInt result = 1;
    result = ec_factor(n_value, stop);
    MPI_Bcast(&stop, 1, MPI_C_BOOL, 0, MPI_COMM_WORLD);

    if(result != 1){
        printf("The factor of %s is %s\n", n_value.toString().c_str(), result.toString().c_str());
    }
    
    MPI_Finalize();
    return 0;
}
