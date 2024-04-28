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

	InfInt CRT(vector<InfInt> values, vector<InfInt> mods, int i = 1); // chinese remainder theorem

	InfInt PowMod(vector<InfInt>);// power modulus

	bool FermatsTest(int); //fermat primality

	vector<InfInt> EulerPhi(InfInt); //euler phi function

	bool prim_root(InfInt, InfInt); // primitive roots

	vector<InfInt> MOD_SQRT(InfInt, InfInt); // modulus sqrt

	InfInt LegendreSymbol(InfInt, InfInt);

	InfInt JacobiSymbol(InfInt, InfInt);

	vector<InfInt> RCF(InfInt a, InfInt b);

	vector<InfInt> DCF(double, int);

	bool MR_Primality_Test(InfInt n, int t);

	vector<InfInt> PollardPM1(InfInt n, int bound); // pollard p-1 algorithm 

	vector<InfInt> PollardRho(InfInt n); // pollard rho

	vector<InfInt> get_curve(InfInt n);

	InfInt ec_factor(InfInt n, InfInt max = 1000);

	
}

#endif
