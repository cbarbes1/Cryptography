#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>

using namespace std;
using namespace std::chrono;

int dot_product(int* v1, int* v2, int size);
int mp_dot_product(int* v1, int* v2, int size);

int* randomVector(int size);

int main()
{
    int TEST_SIZE = 3;
    cout<<"What size would you like to test?"<<endl;
    cin>>TEST_SIZE;

    cout<<"Vector Dot product generic: "<<endl;
    int* v1 = randomVector(TEST_SIZE);

    int* v2 = randomVector(TEST_SIZE);
    auto start = high_resolution_clock::now();
    cout<<"The dot product of these 2 vectors is "<<dot_product(v1, v2, TEST_SIZE)<<endl;

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    
    // output the needed information
    cout <<"Time to compute dot product generic: "<< duration.count() / 1000000.0 << " seconds" << endl;

	
    cout<<"Vector Dot product in parallel: "<<endl;
    start = high_resolution_clock::now();
    cout<<"The dot product of these 2 vectors is "<<mp_dot_product(v1, v2, TEST_SIZE)<<endl;

    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    
    // output the needed information
    cout <<"Time to compute dot product parallel: "<< duration.count() / 1000000.0 << " seconds" << endl;
    

    delete [] v1;
    delete [] v2;
}

int dot_product(int* v1, int* v2, int size)
{
    int result = 0;
    for(int i = 0; i<size; i++){
        
        result += v1[i]*v2[i];
    }
    return result;
}

int mp_dot_product(int* v1, int* v2, int size)
{
    int result = 0;

    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        int nthrds = omp_get_num_threads();
        int items_per_thread = size / nthrds;
        int lb = id * items_per_thread;
        int ub = (id == nthrds - 1) ? size : (id + 1) * items_per_thread;

        int *p1 = v1+lb;
        int *p2 = v2+lb;

        int local_sum = 0;

        for(int i = lb; i<ub; i++){
            local_sum += p1[i-lb]*p2[i-lb];
        }

        #pragma omp critical
        {
            result += local_sum;
        }
    }
    return result;
}


int* randomVector(int size)
{
    int* v1 = new int[size];
    for(int i = 0; i<size; i++){
        v1[i] = rand()%1000+1;
    }
    return v1;
}
