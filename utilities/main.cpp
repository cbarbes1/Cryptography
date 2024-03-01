/*
 * Author: Cole Barbes
 * Purpose: test different mathematical functions for cryptography 
 */
#include "utilities.h"

using namespace std;
using namespace utilities;

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

		vector<InfInt> values;
		InfInt a, b;
		cout<<"Please enter the first value ";
		cin>>a;
		cout<<"Please enter the second value ";
		cin>>b;

		values = GCDEX({a, b});
		cout<<"The extended euclidean equation: "<<endl;
		cout<<a<<"*"<<values[1]<<" + "<<b<<"*"<<values[2]<<endl;
	}
	return 0;
}
