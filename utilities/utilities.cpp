/*
* **Implementation for utilities.h** 
* Author: Cole Barbes
* Date created: 3/1/24
* Last Edited: 3/1/24
*/
#include "utilities.h"
#include <vector>
#include "InfInt.h"

using namespace std;

/* Modulus funcion
* vector of infinite integer class with the layout vector[0] as m and vector[1] as n
* output: Infinite iteger 
* args[0] is the value, args[1] is the mod 
*/
InfInt utilities::MOD(vector<InfInt> args)
{
	InfInt result = args[0];
	if(args[0] > 0){
		result = result/args[1];
		args[0] -= (result*args[1]);
	}else{
		args[0] = args[0]*-1;
		result = args[0]%args[1];
		args[0] = args[1] - result;
	}
	return args[0];
}

/*
* GCD function to find the Greatest Common Divisor of 2 numbers
* Return Infinite integer 
*/
InfInt utilities::GCD(vector<InfInt> args)
{
	if(args.size() == 2){
		InfInt a, b;
		if(args[0] >= args[1]){
			a = args[0];
			b = args[1];
		}else{
			a = args[1];
			b = args[0];
		}

		while(b!=0){
			InfInt temp = b;
			b = a % b;
			a = temp;
		}
		return a;
	}
	return args[0];
}

/*
*	GCDEX function to find the s, t of a*s + b*t = GCD(a, b, GCD)
* 
*/
vector<InfInt> utilities::GCDEX(vector<InfInt> args)
{
	// variables
	// [0]		[1]		[2]		[3]
	// x1 = 1, y1 = 0, x2 = 0, y2 = 1
	vector<InfInt> variables = {1, 0, 0, 1};
	InfInt temp, quotient;
	

	if(args[0] < args[1]){
		temp = args[1];
		args[1] = args[0];
		args[0] = temp;
	}

	InfInt a = args[0];
	InfInt b = args[1];
	
	while(args[1]!= 0){
		quotient = args[0] / args[1];
		temp = args[1];
		args[1] = args[0]%args[1];
		args[0] = temp;

		temp = variables[2];
		variables[2] = variables[0] - quotient * variables[2];
		variables[0] = temp;

		temp = variables[3];
		variables[3] = variables[1] - quotient *variables[3];
		variables[1] = temp;
	}
	return {args[0], variables[0], variables[1]};
}

/*
* Simple Modular inverse function 
* given a (mod n) 
* return a^-1 (mod n) 
* Meaning a*a^-1 congruent to 1 (mod n)
*/
InfInt utilities::ModInv(vector<InfInt> args)
{
	if(GCD(args) == 1){
		vector<InfInt> exdGCD = GCDEX(args);
		return exdGCD[1];
	}
	else
		return -1;
}

/*
* Chinese Remainder theorem for Arbitrary number of inputs
*/
InfInt utilities::CRT(vector<InfInt> values, vector<InfInt> mods, int i)
{
	if(i == mods.size())
		return values[i-1];

	if(GCD({mods[i-1], mods[i]}) != 1)
		return -1;
		
	vector<InfInt> equation = GCDEX({mods[i-1], mods[i]});
	InfInt x = MOD({values[i]*equation[1]*mods[i-1] + values[i-1]*equation[2]*mods[i], mods[i-1]*mods[i]});
	values[i] = x;
	mods[i] = mods[i-1]*mods[i];
	return CRT(values, mods, i+1);
}

/*
* take large powers in modulus a^b (mod n)
* return the result
*/
InfInt utilities::PowMod(vector<InfInt> args)
{
	InfInt b = 1;
	InfInt a = args[1], c = args[0];
	while(a != 0){
		if(a%2 == 0){
			a = a/2;
			c = (c*c)%args[2];
		}else{
			a = a-1;
			b = (b*c)%args[2];
		}
	}
	return b;
}