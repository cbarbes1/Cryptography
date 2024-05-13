#include <mpi.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <stdlib.h>
#include <string.h>
#include "InfInt.h"
#include "omp.h"
#include "../ellipticCurveStructure/ellipticCurve.h"


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

    // print check for problems later on 
    InfInt n_value = std::string(argv[1]);
    printf("Here is the number: %s\n", n_value.toString().c_str());

	double start_time = MPI_Wtime();

    //
    // Elliptic curve parallelized version:
    // broadcast the number and each node will factor the number using a curve 
    // each node will continually get new random curves until the factor is found 
    // Once a factor is found the process will broadcast to each of the other nodes to shutdown safely
    // If the 1000! bound is reached the 
    bool found = false;

	bool stop = false;

	InfInt curve_count = 1;
	Point test(1, 3, 10);

    #pragma omp parallel shared(stop) 
    {
        while(!stop){
            test.setCurve(rand()*100000+rand(), rand()*100000+rand(), n_value);
            for(InfInt i = 2; i<1000 && !stop; i++){
                test = i*test;
                if(test.getFactor() != 1){
                    #pragma omp critical
                    {      
                        stop = true;
                    }
                }
            }
			if(stop){
            	test.setHalt(stop);
			}else{
				curve_count++;
			}
        }
        if(test.getFactor() != 1){
            double end_time = MPI_Wtime(); // Stop the timer
            printf("The factor of %s is %s\n", n_value.toString().c_str(), test.getFactor().toString().c_str());
            
            printf("Time to factor: %f Seconds Number of curves: %s\n", (end_time - start_time), curve_count.toString().c_str());
        }
   }
    MPI_Bcast(&stop, 1, MPI_C_BOOL, 0, MPI_COMM_WORLD);

    
    
    MPI_Finalize();
    return 0;
}