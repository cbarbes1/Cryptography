/*
 * Author: Cole Barbes
 * Purpose: test different mathematical functions for cryptography 
 */
#include "utilities.h"

using namespace std;
using namespace utilities;

/*
* Answers to the Questions
* 1. 
*	GCD(8765, 23485)
*	Choose a function to run (MOD, GCD, GCDEX, MODINV, CRT, POWMOD)
*	GCD
*	Enter a value 0 :
*	8765
*	Enter a value 1 :
*	23485
*	The Greatest Common Denominator GCD(8765, 23485) = 5
* 2. 
*	65537*-1405 + 3511*26226 = 1
* 	Not understanding this one
* 4. 
*	3^1234567
*	last 5 digits: 40587
* 8. 
*	4856955
*/

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

		values = GCDEX({a, b, 17});
		cout<<"The extended euclidean equation: "<<endl;
		cout<<a<<"*"<<values[1]<<" + "<<b<<"*"<<values[2]<<" = "<<values[0]<<endl;
	}else if(type == "MODINV"){
		InfInt a, n;
		cout<<"Enter the mod to work in: "<<endl;
		cin>>n;
		cout<<"Enter the number a to find the inverse: "<<endl;
		cin>>a;
		InfInt result =	ModInv({a, n});
		cout<<"The inverse of "<<a<<" in MOD "<<n<<" is "<<result<<endl;
	}else if(type == "CRT"){
		// x = 17 (mod 101)
		// x = 18 (mod 201)
		// x = 19 (mod 301)
		InfInt result = CRT({17, 18, 19}, {101, 201, 301});
		cout<<"The result of chinese remainder theorem: "<<result<<endl;
	}else if(type == "POWMOD"){
		InfInt a, b, n;
		cout<<"Please enter the base value: "<<endl;
		cin>>a;
		cout<<"Please enter the exponent value: "<<endl;
		cin>>b;
		cout<<"Please enter the mod we are working in: "<<endl;
		cin>>n;

		InfInt result = PowMod({a, b, n});

		cout<<"The result of the exponentiation: "<<endl;
		cout<<result<<endl;
	}
	return 0;
}
