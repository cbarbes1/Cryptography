/*
 * Author: Cole Barbes
 * Purpose: test different mathematical functions for cryptography 
 */
#include "functions.h"

using namespace std;

int main()
{
	InfInt value, n;
	InfInt output;
	cout<<"Enter a number: "<<endl;
	cin>>value;
	cout<<"Enter the MOD we will work in: "<<endl;
	cin>>n;

	output = MOD({value, n});

	cout<<"The output of modulus: "<<output<<endl;
	return 0;
}
