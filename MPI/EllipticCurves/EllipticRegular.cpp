
#include <iostream>
#include <cmath>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include "../InfInt.h"

using namespace std;

vector<InfInt> dxdy(InfInt x, InfInt y, InfInt b){
    return {(x*x)*3+b, (y*2)};
}

InfInt GCD(vector<InfInt> args)
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

InfInt ModInv(vector<InfInt> args)
{
	if(GCD(args) == 1){
		vector<InfInt> exdGCD = GCDEX(args);
		int index = 1;
		if(args[0] < args[1])
			index = 2;
		return exdGCD[index];
	}
	else
		return -1;
}

int main()
{
    InfInt n = 2773;
    InfInt x = 1, y = 3, b = 4;
    InfInt c = (y*y) - (x*x*x) - b*x;

    std::cout<<n<<" "<<y<<"^2 = "<<x<<"^3 + "<<b<<"*"<<x<<" + "<<c<<std::endl;
    vector<InfInt> result = dxdy(x, y, b);
    std::cout<<result[0]<<", "<<result[1]<<std::endl;
    std::cout<<GCD({result[1], n})<<std::endl;
    cout<<ModInv({result[1], n})<<endl;

}