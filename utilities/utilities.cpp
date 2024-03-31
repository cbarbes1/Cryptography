/*
* **Implementation for utilities.h** 
* Author: Cole Barbes
* Date created: 3/1/24
* Last Edited: 3/1/24
*/
#include "utilities.h"
#include <vector>
#include "InfInt.h"
#include <map>
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
		int index = 1;
		if(args[0] < args[1])
			index = 2;
		return exdGCD[index];
	}
	else
		return -1;
}

/*
* Chinese Remainder theorem for Arbitrary number of inputs
*/
InfInt utilities::CRT(vector<InfInt> values, vector<InfInt> mods, int i)
{
	InfInt prod = 1;
	for(int i = 0; i<mods.size(); i++)
		prod *= mods[i];

	InfInt result = 0;
	for(int i = 0; i<mods.size(); i++){
		InfInt pp = prod / mods[i];
		result += (values[i] * ModInv({pp, mods[i]}) * pp);
	}

	return MOD({result, prod});
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

/*
 * Fermats Theorem Primality Test 
 * Parameter: Number to be checked
 * Return True or false to whether it is prime
 */
bool utilities::FermatsTest(int p)
{
	// Thought Process For Project understanding purposes
	// Iterative 
	// while random number a ^ n-1 power is 1 mod n
	// end loop if the var was switched to false
	// end loop at ten then return true
	//
	srand(time(0));

	bool checker = true;

	for(int i = 0; i < 10 && checker != false; i++){
		int randNum = (rand() % (p-3))+2;
		InfInt result = PowMod({randNum, p-1, p});
		cout<<randNum<<result<<endl;
		if(result != 1)
			checker = false;
	}

	return checker;
}

/*
 * Eulers theorem to find the number of numbers that are co prime to p 
 * Return: number of numbers coprime to p and list of them
 */
vector<InfInt> utilities::EulerPhi(InfInt p)
{
	InfInt count = 0;
	vector<InfInt> result;
	result.push_back(0);
	for(InfInt i = 1; i<= p; i++){
		InfInt gcd = GCD({i, p});
		if(gcd == 1){
			count++;
			result.push_back(i);
		}
	}
	result[0] = count;
	return result;
}

/*
 * Determine if a given number is a primitive root
 * return: whether it is a primitive root or not
 */
bool utilities::prim_root(InfInt a, InfInt n)
{
	// use EulerPhi function to get 
	//
	if(GCD({a, n}) != 1)
		return false;

	vector<InfInt> powers = EulerPhi(n);
	bool check = true;
	for(unsigned int i = 1; i<powers.size() && check; i++){
		InfInt result = PowMod({a, powers[i], n});
		if(result == 1 && powers[i] != n-1)
			check = false;
	}

	return check;
}

/*
 * Find the sqrts in a certain modulus
 */
vector<InfInt> utilities::MOD_SQRT(InfInt a, InfInt p)
{
	vector<InfInt> output;
	InfInt mod = MOD({p, 4});
	if(LegendreSymbol(a, p) == -1 || mod != 3){
		output.push_back(-1);
	}else{
		InfInt x = PowMod({a, (p+1)/4, p});
		output.push_back(x);
		output.push_back(-x);
	}
	return output;
}

/*
 * Test if there is a sqrt in mod p
 */
InfInt utilities::LegendreSymbol(InfInt a, InfInt p)
{
	InfInt result;
	if(MOD({a, p}) == 0){
		result = 0;
	}else{
		result = PowMod({a, (p-1)/2, p});
		if(result != 1)
			result = result - p;
	}
	return result;
}

/*
 * Test if there isnt a sqrt in mod n n being a composite
 */     
InfInt utilities::JacobiSymbol(InfInt a, InfInt n)
{
	if(GCD({a, n}) != 1)
		return -1;

	InfInt output = 1;

	// if the number is less than 0 check if it is 3 mod 4 if it is then flip the sign
	if(a < 0){
		a = -a;
		if(n%4 == 3){
			output = -output;
		}
	}

	while(a != 0){ // continually apply the rules until the result is found
		while(a%2 == 0){
			a/=2;
			if(n%8 == 3 || n%8 == 5){ // rule 4  -1
				output = -output;
			}
		}
		if(a%2 == 1 && n%2 == 1){
			InfInt temp = a;
			a = n;
			n = temp;
			if(a%4 == 3 && n%4 == 3){ // rule 5
				output = -output;
			}
		}
		a = a%n;
	}
	return output;
}

/*
 * Rational number continued fraction
 */
vector<InfInt> utilities::RCF(InfInt a, InfInt b)
{
	vector<InfInt> output;
	while(b != 0){
		InfInt num = a/b;
		InfInt rem = MOD({a, b});
		output.push_back(num);
		a = b;
		b = rem;
	}

	return output;
}
   
/*
 * Double number continued fraction
 */
vector<InfInt> utilities::DCF(double a, int n)
{
	InfInt a_value;
	vector<InfInt> output;
	for(int i = 0; i<n; i++){
		a_value = static_cast<int>(a);
		a = a - a_value.toInt();
		a = 1/a;
		output.push_back(a_value);
	}
	return output;
}

/* Miller-Rabin Primality Test 
 * Parameters: The number to be tested
 * Return: True if the number is probably prime, False if the number is composite
 */
bool utilities::MR_Primality_Test(InfInt n, int t){

	srand(time(0));
	map<InfInt, int> randints;
	bool checker = false;
	//write n-1 = 2^k*m
	for(int i = 0; i<t; i++){
		int randInt = rand()%(n-1).toInt()+1;
		while(randints.find(randInt) != randints.end()){
			randInt = rand()%(n-1).toInt()+1;
		}
		randints[randInt] = 1;

		// b0 = a^m(mod n)
		// if b0 = +-1(mod n) stop and declare n is prob prime
		// otherwise, let b1 = b0^2(mod n).
		// if b1 = 1 (mod n), then n is composite gcd(b0-1, n) gives a nontrivial factor of n
		// if b1 = -1 (mod n), then n is prob prime
		// otherwise, let b2 = b1^2(mod n) 
		// if b2 = 1 (mod n) then n is composite
		// if b2 = -1 (mod n) then n is prob prime
		// continue until bk-1, if bk-1 != -1 (mod n) then n is composite
	}
}
