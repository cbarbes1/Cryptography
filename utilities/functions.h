#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <vector>
#include "InfInt.h"

using namespace std;

InfInt MOD(vector<InfInt>); // Modulus one number m by another number n

InfInt GCD(vector<InfInt>); // Greatest Common Divisor

vector<InfInt> GCDEX(vector<InfInt>); // Greatest Common Divisor Extended Equation will return s and t

vector<InfInt> ModInv(vector<InfInt>);

vector<InfInt> CRT(vector<InfInt>);

InfInt PowMod(vector<InfInt>);

#endif
