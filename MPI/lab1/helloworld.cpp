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
	// if(rank%2 != 0){
	// 	int number = -1;
	// 	std::cout<<"Process "<<rank<<" is sending Process "<<1<<" some dept "<<std::endl;
	// 	MPI_Send(&number, 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD);
	// }else if(rank%2==0){
	// 	int number;
	// 	MPI_Recv(&number, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, NULL);
	// 	std::cout<<"-----------------------------------------------------------------------"<<std::endl;
	// 	std::cout<<"Process 1 reveived number "<< number<< " from process 0\n"<<std::endl;
	// 	std::cout<<"-----------------------------------------------------------------------"<<std::endl;
	// }
	MPI_Finalize();
	return 0;
}
