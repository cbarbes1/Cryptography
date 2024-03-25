#include <omp.h>
#include <iostream>
#define INTERVAL 10000
using namespace std;

int main()
{
	#pragma omp parallel num_threads(15)
	{
		printf("Hello World! From thread number %d\n", static_cast<int>(omp_get_thread_num()));
	}
	return 0;
}
