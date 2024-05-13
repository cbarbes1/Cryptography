#include <stdio.h>
#include <omp.h>

int main()
{
    #pragma omp parallel
    {
        int thread = omp_get_thread_num();
        printf("hello world! from thread # %d\n", thread);
    }
    return 0;
}