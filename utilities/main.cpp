/*
 * Author: Cole Barbes
 * Purpose: test different mathematical functions for cryptography 
 */
#include "utilities.h"

using namespace std;
using namespace utilities;

/*
*/
int main()
{
	string type;
	cout<<"Choose a function to run (MOD, GCD, GCDEX, MODINV, CRT, POWMOD, FermatsTest, EulerPhi, PrimRoot, MODSQRT, LSYM, JSYM, RCF, DCF, MR (Miller-Rabin)), PM1(Pollard p-1), PRHO (Pollard Rho)"<<endl;
	cin>>type;
	if(type == "MOD"){
		InfInt value, n;
		InfInt output;
		cout<<"Enter a number: "<<endl;
		cin>>value;
		cout<<"Enter the MOD we will work in: "<<endl;
		cin>>n;

		output = MOD({value, n});

		cout<<"The output of modulus: "<<output<<endl;
	}else if(type == "GCD"){
		vector<InfInt> values;
		InfInt output;
		for(int i = 0; i<2; i++){
			InfInt val;
			cout<<"Enter a value "<<i<<" :"<<endl;
			cin>>val;
			values.push_back(val);
		}
		output = GCD(values);
		printf("The Greatest Common Denominator GCD(%d, %d) = %d", values[0].toInt(), values[1].toInt(), output.toInt());
	}else if(type == "GCDEX"){

		vector<InfInt> values;
		InfInt a, b;
		cout<<"Please enter the first value ";
		cin>>a;
		cout<<"Please enter the second value ";
		cin>>b;

		values = GCDEX({a, b, 17});
		cout<<"The extended euclidean equation: "<<endl;
		cout<<a<<"*"<<values[1]<<" + "<<b<<"*"<<values[2]<<" = "<<values[0]<<endl;
	}else if(type == "MODINV"){
		InfInt a, n;
		cout<<"Enter the mod to work in: "<<endl;
		cin>>n;
		cout<<"Enter the number a to find the inverse: "<<endl;
		cin>>a;
		InfInt result =	ModInv({a, n});
		cout<<"The inverse of "<<a<<" in MOD "<<n<<" is "<<result<<endl;
	}else if(type == "CRT"){
		InfInt val1;
		InfInt val2;
		InfInt mod1;
		InfInt mod2;
		cout<<"Please enter the first value followed by the mod: "<<endl;
		cin>>val1>>mod1;
		cout<<"Please enter the second value followed by the mod: "<<endl;
		cin>>val2>>mod2;
		InfInt result = CRT({val1, val2}, {mod1, mod2});
		cout<<"The result of chinese remainder theorem: "<<result<<endl;
	}else if(type == "POWMOD"){
		InfInt a, b, n;
		cout<<"Please enter the base value: "<<endl;
		cin>>a;
		cout<<"Please enter the exponent value: "<<endl;
		cin>>b;
		cout<<"Please enter the mod we are working in: "<<endl;
		cin>>n;

		InfInt result = PowMod({a, b, n});

		cout<<"The result of the exponentiation: "<<endl;
		cout<<result<<endl;
	}else if(type == "FermatsTest"){
		int TestPrime = 0;
		cout<<"Please enter a number to test its primality: "<<endl;
		cin>>TestPrime;
		if(FermatsTest(TestPrime)){
			cout<<"The number "<<TestPrime<<" is a prime"<<endl;
		}else{
			cout<<"The number "<<TestPrime<<" is a composite and not a prime"<<endl;
		}
	}else if(type == "EulerPhi"){
		InfInt InputNumber = 0;
		cout<<"Please enter the number to find how many number that are relatively prime to it: "<<endl;
		cin>>InputNumber;
		vector<InfInt> output = EulerPhi(InputNumber);
		cout<<"There are "<<output[0]<<" numbers relatively prime to "<<InputNumber<<endl;
	}else if(type == "PrimRoot"){
		InfInt InputNumber, mod;
		cout<<"Please enter the number to check if it is a primitive root:"<<endl;
		cin>>InputNumber;
		cout<<"Please enter the mod you are working in: "<<endl;
		cin>>mod;

		if(prim_root(InputNumber, mod)){
			cout<<"The number "<< InputNumber<<" is a primitive root mod"<<mod<<endl;
		}else{
			cout<<"Not a primitive root mod "<<mod<<endl;
		}
	}else if(type == "MODSQRT"){
		InfInt a, p;
		cout<<"Please enter the value you would like to get the sqrt"<<endl;
		cin>>a;
		cout<<"Please enter the modulus you are working in "<<endl;
		cin>>p;

		vector<InfInt> output = MOD_SQRT(a, p);

		cout<<"The square roots of "<<a<<" in mod "<<p<<" are ";

		for(unsigned int i = 0; i<output.size(); i++)
			cout<<output[i]<<" ";
		cout<<endl;
	}else if(type == "LSYM"){
		InfInt a, p;
		cout<<"Please enter the value of a s.t x^2 is congruent to a (mod p) to test "<<endl;
		cin>>a;
		cout<<"Please enter the mod you are working in"<<endl;
		cin>>p;
		InfInt testval = LegendreSymbol(a, p);
		if(testval == 1)
			cout<<"The congruence x^2 congruent to "<<a<<" (mod "<<p<<") has a solution"<<endl;
		else
			cout<<"No solution to the congruence"<<endl;
	}else if(type == "JSYM"){
		InfInt a, n;

		cout<<"Please enter the value you would like to test "<<endl;
		cin>>a;
		cout<<"Please enter the composite mod you want to work in "<<endl;
		cin>>n;

		InfInt result = JacobiSymbol(a, n);
		if(result == 1)
			cout<<"There is not results to find here since the jacobi symbol was 1"<<endl;
		else
			cout<<"Since jacobi symbol was "<<result<<", There is no square root mod "<<n<<endl;
	}else if(type == "RCF"){
		InfInt a, b;

		cout<<"Please enter the numerator of the quotient "<<endl;
		cin>>a;
		cout<<"Please enter the denominator of the quotient "<<endl;
		cin>>b;
		
		vector<InfInt> output = RCF(a, b);

		for(unsigned int i = 0; i< output.size(); i++){
			cout<<"a"<<i<<" : "<<output[i]<<endl;
		}
	}else if(type == "DCF"){
		double a;
		int n;
		cout<<"What is value would you like to approximate? "<<endl;
		cin>>a;
		cout<<"Enter how many a value you want to approximate to :"<<endl;
		cin>>n;

		vector<InfInt> output = DCF(a, n);
		int i = 0;
		for(InfInt a : output){
			i++;
			cout<<"a"<<i<<" is "<<a<<endl;
		}
	}else if(type == "MR"){
		string number = "";
		int t = 0;
		cout<<"Please enter the number: "<<endl;
		cin>>number;
		cout<<"Please enter the stopping point of a values"<<endl;
		cin>>t;
		InfInt num = number;
		InfInt tester = MR_Primality_Test(num, t);
		if(tester == 1){
			cout<<"The number is prime"<<endl;
		}else if(tester >1){
			cout<<"The number is composite"<<endl;
			cout<<"Here is the factor(s) "<<tester<<" * "<<num/tester<<" = "<<number<<endl;
		}else{
			cout<<"Test was inconclusive"<<endl;
		}
	}else if (type == "PM1"){
		string number = "";
		cout<<"Please enter the number to factor: "<<endl;
		cin>>number;

		InfInt num = number;
		int bound = 100000;
		vector<InfInt> output = PollardPM1(num, bound);
		if(output[0] != -1)
			cout<<"The factors of n = "<<num<<" is p = "<<output[0]<<" q = "<<output[1]<<endl;
		else
			cout<<"Pollard p-1 failed"<<endl;
	}else if (type == "PRHO"){
		string number = "";
		cout<<"Please enter the number to factor: "<<endl;
		cin>>number;

		InfInt num = number;
		vector<InfInt> output = PollardRho(num);
		if(output[0] != -1)
			cout<<"The factors of n = "<<num<<" is p = "<<output[0]<<" q = "<<output[1]<<endl;
		else
			cout<<"Pollard Rho failed"<<endl;
	}

	return 0;
}
