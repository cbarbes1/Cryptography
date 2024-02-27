/*
 * Author: Cole Barbes
 * Purpose: test different mathematical functions for cryptography 
 */
#include "functions.h"

using namespace std;

int main()
{
	string type;
	cout<<"Choose a function to run (MOD, GCD, GCDEX, MODINV, CRT, POWMOD)"<<endl;
	cin>>type;
	if(type == "MOD"){
		InfInt value, n;
		InfInt output;
		cout<<"Enter a number: "<<endl;
		cin>>value;
		cout<<"Enter the MOD we will work in: "<<endl;
		cin>>n;

		output = MOD({value, n});

		cout<<"The output of modulus: "<<output<<endl;
	}else if(type == "GCD"){
		vector<InfInt> values;
		InfInt output;
		for(int i = 0; i<2; i++){
			InfInt val;
			cout<<"Enter a value "<<i<<" :"<<endl;
			cin>>val;
			values.push_back(val);
		}
		output = GCD(values);
		printf("The Greatest Common Denominator GCD(%d, %d) = %d", values[0].toInt(), values[1].toInt(), output.toInt());
	}else if(type == "GCDEX"){

	}
	return 0;
}
