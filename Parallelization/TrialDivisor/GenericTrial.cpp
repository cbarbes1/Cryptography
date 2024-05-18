#include <iostream>
#include "../InfInt.h"
#include <chrono>


using namespace std;
using namespace std::chrono;

int main(int argc, char *argv[])
{
    InfInt number = string(argv[1]);
    InfInt factor = -1;
    bool tester = false;
    auto start = high_resolution_clock::now();
    
    for(InfInt i = 2; i<=number.intSqrt() && !tester; i++){
        if(number%i == 0){
            tester = true;
            factor = i;
        }
    }

    auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
    if(tester){
        cout<<number<<" = "<<factor<<" * "<<number/factor<<endl;
    }else{
        cout<<"Could not factor or number is prime"<<endl;
    }

    cout << "Time to factor the number: " << duration.count() / 1000000.0 << " seconds"<< endl;
}