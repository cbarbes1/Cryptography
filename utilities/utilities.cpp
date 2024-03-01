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
*	GCDEX function to find the s, t of a*s + b*t = GCD(a, b)
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
	
	while(args[1] != 0){
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

vector<InfInt> utilities::ModInv(vector<InfInt> args)
{
	return {0};
}
			
vector<InfInt> utilities::CRT(vector<InfInt> args)
{
	return {0};
}
	
InfInt utilities::PowMod(vector<InfInt> args)
{
	return 0;
}