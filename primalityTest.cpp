#include <iostream>
#include <mpi.h>
#include <cmath>

using namespace std;

int main()
{
	if(argc != 2){
		cout<<"Error no argument "<<endl;
		return 1;
	}
	unsigned long int input = 0;
	unsigned long int maxfactor = 0;
	int index = 1;
	cout<<"Please enter the number to test if it is prime: "<<endl;
	cin>> input;

	maxfactor = sqrt(input);

	MPI_Init(NULL, NULL);
	MPI_Comm world = MPI_COMM_WORLD;
	int worldSize;
	int myRank = MPI_Comm_rank(world, &worldSize); 
	MPI_Bcast();
	MPI_Finalize();
	return 0;
}
