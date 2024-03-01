#ifndef utilities_H
#define utilities_H

#include <cmath>
#include <iostream>
#include "InfInt.h"
#include <vector>

namespace utilities {
	using namespace std;

	InfInt MOD(vector<InfInt>); // Modulus one number m by another number n

	InfInt GCD(vector<InfInt>); // Greatest Common Divisor

	vector<InfInt> GCDEX(vector<InfInt>); // Greatest Common Divisor Extended Equation will return s and t
	vector<InfInt> ModInv(vector<InfInt>);

	vector<InfInt> CRT(vector<InfInt>);

	InfInt PowMod(vector<InfInt>);
}

#endif
