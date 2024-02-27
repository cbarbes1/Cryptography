#include "functions.h"
#include <cmath>
/* Modulus funcion
 * vector of infinite integer class with the layout vector[0] as m and vector[1] as n
 * output: Infinite iteger 
 * args[0] is the value, args[1] is the mod 
 */
InfInt MOD(vector<InfInt> args)
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

InfInt GCD(vector<InfInt> args)
{
	vector<vector<InfInt>> equations;

	InfInt a, b;
	if(args[0] >= args[1]){
		a = args[0];
		b = args[1];
	}else{
		a = args[1];
		b = args[0];
	}

	vector<InfInt> equation = {a, 1, b, 1};
	
	while(equation[3] != 0){
		
		equation[1] = equation[0] / equation[2];
		equation[3] = equation[0] - (equation[1]*equation[2]);
		equations.push_back(equation);
		
	}

	return equation[2];
}

vector<InfInt> GCDEX(vector<InfInt> args)
{

	return {0};
}

vector<InfInt> ModInv(vector<InfInt> args)
{
	return {0};
}
         
vector<InfInt> CRT(vector<InfInt> args)
{
	return {0};
}
 
InfInt PowMod(vector<InfInt> args)
{
	return 0;
}
