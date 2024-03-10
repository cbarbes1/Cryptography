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

	MPI_init(NULL, NULL);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);


	MPI_Get_processor_name(processor_name, &name_len); 
	std::cout<<"Hello from processor "<<processor_name<<", rank "<<rank<<" out of "<<size<<" processors\n"<<std::endl;
	if(rank == 0){
		int number = -1;
		MPI_Send(&number, 1, MPI_INIT, 1, 0, MPI_COMM_WORLD);
	}else if(rank == 1){
		int number;
		MPI+Recv(&number, 1, MPI_INIT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		std::cout<<"Process 1 reveived number "<< number<< " from process 0\n"<<std::endl;
	}
	MPI_Finalize(NULL);
	return 0;
}
