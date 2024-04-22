#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

vector<int> factor(int);

int main()
{
	vector<int> result;
	int num = 0;
	cout<<"Please enter the value to factor: "<<endl;
	cin>>num;
	
	result = factor(num);
	for(unsigned int i = 0; i<result.size(); i++)
		cout<<result[i]<<" ";
	cout<<endl;
}

vector<int> factor(int n)
{
	vector<int> result;
	long end = static_cast<int>(sqrt(n));
	for(int i = 2; i<=end; i++){
		if(n%i == 0){
			result.push_back(i);
		}
	}
	return result;
}
