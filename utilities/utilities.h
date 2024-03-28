/*
* Author: Cole Barbes
* Purpose: library of functions for Cryptography
* Date Created: 3/1/24
* Last edited 3/1/24
*/
#ifndef utilities_H
#define utilities_H

#include <cmath>
#include <iostream>
#include "InfInt.h"
#include <vector>

// namespace for convenience
namespace utilities {
	using namespace std;

	InfInt MOD(vector<InfInt>); // Modulus one number m by another number n

	InfInt GCD(vector<InfInt>); // Greatest Common Divisor

	vector<InfInt> GCDEX(vector<InfInt>); // Greatest Common Divisor Extended Equation will return s and t
	InfInt ModInv(vector<InfInt>);

	InfInt CRT(vector<InfInt> values, vector<InfInt> mods, int i = 1);
	InfInt PowMod(vector<InfInt>);

	bool FermatsTest(int); 

	vector<InfInt> EulerPhi(InfInt);

	bool prim_root(InfInt, InfInt);

	vector<InfInt> MOD_SQRT(InfInt, InfInt);

	InfInt LegendreSymbol(InfInt, InfInt);

	InfInt JacobiSymbol(InfInt, InfInt);

	vector<InfInt> RCF(InfInt a, InfInt b);

	vector<InfInt> DCF(double, int);

	bool MR_Primality_Test(InfInt n);
}

#endif
