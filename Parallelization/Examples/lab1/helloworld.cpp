#include <cstdlib>
#include <iostream>
#include <mpi.h>
#include <cmath>

int main() 
{
	int rank;
	int size;
	int name_len;
	char processor_name[MPI_MAX_PROCESSOR_NAME];

	MPI_Init(NULL, NULL);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);


	MPI_Get_processor_name(processor_name, &name_len); 
	std::cout<<"Hello from processor "<<processor_name<<", rank "<<rank<<" out of "<<size<<" processors\n"<<std::endl;
	
	MPI_Finalize();
	return 0;
}
