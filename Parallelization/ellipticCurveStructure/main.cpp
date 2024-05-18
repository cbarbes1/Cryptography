#include <iostream>
#include <chrono>
#include "ellipticCurve.h"
#include <omp.h>

using namespace std;
using namespace std::chrono;

int main()
{
    srand(time(0));

    // create the x and y values for the curve and set the mod
    Point P(rand(), rand(), 35);
    // print the point
    P.printPoint();

    // double P
    P = P.doubleP();

    // print P
    P.printPoint();

    // set the curve to a specific curve
    P.setCurve(1, 3, 2773);

    // print P
    P.printPoint();

    // triple P
    P = 3 * P;

    // Point test(1, 3, 10);
    InfInt number;
    string num;
    cout << "Please enter a number to factor: " << endl;
    cin >> num;
    number = num;

    bool stop = false;
    auto start = high_resolution_clock::now();
    // while(!stop)
    // {
    //     Point test(1, 3, 10);
    //     test.setCurve(rand() * 100000 + rand(), rand() * 100000 + rand(), number);
    //     for (InfInt i = 2; i < 1000 && !stop; i++)
    //     {
    //         test = test * i;
    //         if (test.getFactor() != 1)
    //         {
    //             stop = true;
    //         }
    //     }
    //     if (stop)
    //     {
    //         test.setHalt(stop);
    //     }
    // }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);

    // output the needed information
    cout << "Time to compute with 1 processor: " << duration.count() / 1000000.0 << " seconds" << endl;

    stop = false;
    Point OG(1, 3, 5);

    start = high_resolution_clock::now();
    #pragma omp parallel shared(stop)
    {
        if (omp_get_thread_num() == 0) {  
            int nthreads = omp_get_num_threads();
            printf("Total number of threads: %d\n", nthreads);
        }
        while (!stop)
        {
            Point test(1, 3, 10);
            
            test.setCurve(rand() * 100000 + rand(), rand() * 100000 + rand(), number);
            OG = test;
            for (InfInt i = 2; i < 1000 && !stop; i++)
            {
                test = test * i;
                if (test.getFactor() != 1)
                {
                    stop = true;
                }
            }
            if (stop)
            {
                test.setHalt(stop);
            }
        }
    }

    end = high_resolution_clock::now();
    duration = duration_cast<microseconds>(end - start);

    // output the needed information
    
    cout << "Time to compute on : " << duration.count() / 1000000.0 << " seconds" << endl;
    return 0;
}
