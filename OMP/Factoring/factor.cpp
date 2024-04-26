#include <iostream>
#include <omp.h>
#include "../InfInt.h"
#include <vector>
#include <string.h>

vector<InfInt> PollardPM1(InfInt n, int bound = INFINITY){
        InfInt result = 2, start, end;
        InfInt p = 1;
        InfInt q = 1;
	int tid, nthreads;
        bool stop = false;
        // from i = 2 -> i < bound
	#pragma omp parallel private(tid, result, p, q, stop, start, end) shared(n, bound, nthreads)  
        for(int i = 2; i<bound && !stop; i++){
                result = PowMod({result, i, n});
                p = GCD({result-1, n});

                // if the result is a non-trivial factor then get the other factor and terminate
                if(p > 1 && p < n){
                        stop = true;
                        q = n/p;
                }
        }

        if(stop){ // if found then return the 2 factors
                return {p, q};
        }else return {-1};
}

int main(int argv, char **argv)
{

	InfInt number = std:string s(argv[1]);
	

	return 0;
}
