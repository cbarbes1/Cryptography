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
#include <cmath>
#include <exception>
using namespace std;

/* Modulus funcion
 * vector of infinite integer class with the layout vector[0] as m and vector[1] as n
 * output: Infinite iteger
 * args[0] is the value, args[1] is the mod
 */
InfInt utilities::MOD(vector<InfInt> args)
{
	InfInt result = args[0];
	if (args[0] > 0)
	{
		args[0] = args[0]%args[1];
	}
	else
	{
		args[0] = args[0] * -1;
		result = args[0] % args[1];
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
	if (args.size() == 2)
	{
		InfInt a, b;
		if (args[0] >= args[1])
		{
			a = args[0];
			b = args[1];
		}
		else
		{
			a = args[1];
			b = args[0];
		}

		while (b != 0)
		{
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

	if (args[0] < args[1])
	{
		temp = args[1];
		args[1] = args[0];
		args[0] = temp;
	}

	InfInt a = args[0];
	InfInt b = args[1];

	while (args[1] != 0)
	{
		quotient = args[0] / args[1];
		temp = args[1];
		args[1] = args[0] % args[1];
		args[0] = temp;

		temp = variables[2];
		variables[2] = variables[0] - quotient * variables[2];
		variables[0] = temp;

		temp = variables[3];
		variables[3] = variables[1] - quotient * variables[3];
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
	if (GCD(args) == 1)
	{
		vector<InfInt> exdGCD = GCDEX(args);
		int index = 1;
		if (args[0] < args[1])
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
	for (unsigned int i = 0; i < mods.size(); i++)
		prod *= mods[i];

	InfInt result = 0;
	for (unsigned int i = 0; i < mods.size(); i++)
	{
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
	while (a != 0)
	{
		if (a % 2 == 0)
		{
			a = a / 2;
			c = (c * c) % args[2];
		}
		else
		{
			a = a - 1;
			b = (b * c) % args[2];
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

	for (int i = 0; i < 10 && checker != false; i++)
	{
		InfInt result = PowMod({(rand() % (p - 3)) + 2, p - 1, p});
		if (result != 1)
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
	for (InfInt i = 1; i <= p; i++)
	{
		InfInt gcd = GCD({i, p});
		if (gcd == 1)
		{
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
	if (GCD({a, n}) != 1)
		return false;

	vector<InfInt> powers = EulerPhi(n);
	bool check = true;
	for (unsigned int i = 1; i < powers.size() && check; i++)
	{
		InfInt result = PowMod({a, powers[i], n});
		if (result == 1 && powers[i] != n - 1)
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

	bool prime = false;

	prime = MR_Primality_Test(p, 1000);

	if (prime)
	{
		InfInt mod = MOD({p, 4});
		if (LegendreSymbol(a, p) == -1 || mod != 3)
		{
			InfInt x = PowMod({MOD({-a, p}), (p + 1) / 4, p});
			output.push_back(x);
			output.push_back(-x);
		}
		else
		{
			InfInt x = PowMod({a, (p + 1) / 4, p});
			output.push_back(x);
			output.push_back(-x);
		}
	}
	else
	{
		output.push_back(-1);
	}
	return output;
}

/*
 * Test if there is a sqrt in mod p
 */
InfInt utilities::LegendreSymbol(InfInt a, InfInt p)
{
	InfInt result;
	if (MOD({a, p}) == 0)
	{
		result = 0;
	}
	else
	{
		result = PowMod({a, (p - 1) / 2, p});
		if (result != 1)
			result = result - p;
	}
	return result;
}

/*
 * Test if there isnt a sqrt in mod n n being a composite
 */
InfInt utilities::JacobiSymbol(InfInt a, InfInt n)
{
	if (GCD({a, n}) != 1)
		return -1;

	InfInt output = 1;

	// if the number is less than 0 check if it is 3 mod 4 if it is then flip the sign
	if (a < 0)
	{
		a = -a;
		if (n % 4 == 3)
		{
			output = -output;
		}
	}

	while (a != 0)
	{ // continually apply the rules until the result is found
		while (a % 2 == 0)
		{
			a /= 2;
			if (n % 8 == 3 || n % 8 == 5)
			{ // rule 4  -1
				output = -output;
			}
		}
		if (a % 2 == 1 && n % 2 == 1)
		{
			InfInt temp = a;
			a = n;
			n = temp;
			if (a % 4 == 3 && n % 4 == 3)
			{ // rule 5
				output = -output;
			}
		}
		a = a % n;
	}
	return output;
}

/*
 * Rational number continued fraction
 */
vector<InfInt> utilities::RCF(InfInt a, InfInt b)
{
	vector<InfInt> output;
	while (b != 0)
	{
		InfInt num = a / b;
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
	for (int i = 0; i < n; i++)
	{
		a_value = static_cast<int>(a);
		a = a - a_value.toInt();
		a = 1 / a;
		output.push_back(a_value);
	}
	return output;
}

/* Miller-Rabin Primality Test
 * Parameters: The number to be tested
 * Return: 1 if the number is probably prime, GCD(b-1, n) if the number is composite
 */
bool utilities::MR_Primality_Test(InfInt n, int t)
{

	srand(time(0));
	InfInt m = n - 1;
	int k = 0;
	InfInt b = 0;
	InfInt b0 = 0;
	bool check = true;
	while (m % 2 == 0)
	{
		m = m / 2;
		k++;
	}
	check = (k == 1);
	// write n-1 = 2^k*m
	bool result = false;
	for (int i = 0; i < t && check; i++)
	{

		InfInt randInt = rand() % t + 1;

		// b0 = a^m(mod n)
		b = PowMod({randInt, m, n});
		b0 = b;

		// if b0 = +-1(mod n) stop and declare n is prob prime
		if (b == 1 || b == n - 1)
		{
			result = true;
			check = false;
		}

		// otherwise,

		for (int j = 1; j < k && check; j++)
		{
			// let b1 = b0^2(mod n).
			b = MOD({(b * b), n});
			// if b1 = 1 (mod n), then n is composite gcd(b0-1, n) gives a nontrivial factor of n
			if (b == 1)
			{
				result = false;
				check = false;
			}
			// // if b1 = -1 (mod n), then n is prob prime
			if (b == n - 1)
			{
				result = true;
				check = false;
			}
			// otherwise, let b2 = b1^2(mod n)
			// if b2 = 1 (mod n) then n is composite
			// if b2 = -1 (mod n) then n is prob prime
			// continue until bk-1, if bk-1 != -1 (mod n) then n is composite
			b0 = b;
		}
	}
	return result;
}

/*
 *	Pollard p-1 algorithm
 *	Parameters: A number n to factor
 *	Return: A factor or -1 on failure
 *	Notes: pollard p-1 takes a number a and does the following a^(B!)(mod n) for a >1 and B
 */

vector<InfInt> utilities::PollardPM1(InfInt n, int bound = 1000000)
{
	InfInt result = 2;
	InfInt p = 1;
	InfInt q = 1;
	bool stop = false;
	// from i = 2 -> i < bound
	for (int i = 2; i < bound && !stop; i++)
	{
		result = PowMod({result, i, n});
		p = GCD({result - 1, n});

		// if the result is a non-trivial factor then get the other factor and terminate
		if (p > 1 && p < n)
		{
			stop = true;
			q = n / p;
		}
	}

	if (stop)
	{ // if found then return the 2 factors
		return {p, q};
	}
	else
		return {-1};
}

/*	Pollard rho algorithm that uses cycle detection
 *	Parameters: The number to be factored
 *	Return: the 2 factors if found and -1 if not found
 */
vector<InfInt> utilities::PollardRho(InfInt n)
{
	InfInt x = "2", y = x, result = 0, q = 0;

	int finder = 0;
	while (finder != 1)
	{
		// floyds cycle detection f(x)
		x = MOD({(x * x + 1), n});
		// f(f(y))
		y = MOD({((y * y + 1) * (y * y + 1) + 1), n});

		// if x-y is positive then use that, if negative then negate it
		result = GCD({x - y > 0 ? x - y : -(x - y), n});
		if (result > 1 && result < n)
		{
			finder = 1;
			q = n / result;
		}
	}
	// if success return the factors
	if (finder == 1)
		return {result, q};
	else
		return {-1};
}

/*
 * Create an elliptic random elliptic curve mod n
 * given a number n find a point P then find the curve that it lies on
 */
vector<InfInt> utilities::get_curve(InfInt n)
{
	InfInt c;

	InfInt x = MOD({rand(), n});
	InfInt y = MOD({rand(), n});

	InfInt b = MOD({rand(), n});
	InfInt result = MOD({x * x * x + x * b, n});
	InfInt y2 = PowMod({y, 2, n});
	c = MOD({y2 - result, n});

	bool found = (y2 == MOD({result + c, n}));
	vector<InfInt> res;

	if (found)
	{
		res = {b, c, x, y};
	}
	else
	{
		res = {-1};
	}

	return res;
}

/*
 * Factoring algorithm that harnesses the elliptic curve factoring method
 * a point P is chosen and an elliptic curve that the point exists on is found
 * the algorithm then tests different curves to find a factor of n
 * parameters: The number being factored n and the max factorial
 */
InfInt utilities::ec_factor(InfInt n, InfInt max)
{
	InfInt result = 1, x, y, m, x1, y1;
	
	bool tester = false;
	int curve_count = 0;
	while(result == 1){
		// curve returns b, c, x, y
		vector<InfInt> curve = get_curve(n);
		// if the curve getter fails try again until it succeeds
		while (curve[0] == -1)
			curve = get_curve(n);

		InfInt d1 = MOD({((curve[2]*curve[2]*3) + curve[0]), n});
		InfInt d2 = MOD({curve[3]*2, n});

		// make sure the gcd is 1 before inverting
		result = GCD({d2, n});
		if(result != 1){
			tester = true;
		}else{
			m = d1*ModInv({d2, n});
			// find the x and y points using the slope equation
			x = MOD({m*m - curve[2] - curve[2], n});
			y = MOD({m*(curve[2]-x) - curve[3], n});
			x1 = curve[2];
			y1 = curve[3];
		}

		
		for (InfInt i = 3; i < max && !tester; i++)
		{
			// save x_prev, y_prev for odd addition
			// even calc 
			// for loop through each 2 in the number until you reach k <= i;
			InfInt x_prev = x;
			InfInt y_prev = y;
			for(InfInt k = 0; k<i-1 && !tester; k+=2){
				// Using a tangent line we find the double of each point until we run out of doubles or we find a factor
				d1 = MOD({((x * x * 3) + curve[0]), n});
				d2 = MOD({y * 2, n});
				// make sure the gcd is 1 before inverting
				result = GCD({d2, n});
				if (result != 1 && result != n)
				{
					tester = true;
				}
				else
				{
					m = d1 * ModInv({d2, n});
					// find the x and y points using the slope equation
					x1 = x;
					x = MOD({m * m, n});
					y = MOD({m * (x1 - x) - y, n});
				}
			}
			// each odd number has one addition after consecutive doubling
			if(i%2 == 1 && !tester){
				// regular slope calculation
				d2 = MOD({(x - x_prev), n});
				d1 = MOD({y - y_prev, n});
				result = GCD({d2, n});

				if (result != 1 && result != n)
				{
					tester = true;
				}
				else
				{
					m = d1 * ModInv({d2, n});
					x1 = x;
					x = MOD({m * m - x - x_prev, n});
					y = MOD({m * (x1 - x) - y, n});
				}
			}
		}
		curve_count++;
	}
	
	return result;
}
