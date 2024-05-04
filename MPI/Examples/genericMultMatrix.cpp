#include <iostream>
#include <vector>

using namespace std;

int dot_product(vector<int> v1, vector<int> v2);


int main()
{
    vector<int> v1 = {1, 4, 7};
    vector<int> v2 = {1, 2, 3};

    cout<<"dot product of 2 vectors "<<dot_product(v1, v2)<<endl;
}

int dot_product(vector<int> v1, vector<int> v2)
{
    int result = 0;
    for(unsigned int i = 0; i<v1.size(); i++){
        
        result += v1[i]*v2[i];
    }
    return result;
}