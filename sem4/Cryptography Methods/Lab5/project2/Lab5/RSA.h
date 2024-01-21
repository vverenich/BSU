#ifndef _RSA_H
#define _RSA_H

#include <utility>
#include <vector>

#include "Key.h"

class RSA {
private:
	long long gcd(long long a, long long b);
	long long pow(long long base, unsigned long power, long long mod);
	long long modInv(const long long& base, const long long& mod);
public:
	std::pair<int, int> generateTwoPrimeNumbers(int upperBound);
	
	long long calculateN(int p, int q);
	long long calculatePhi(int p, int q);

	long long calculateD(long long phi, long long e);

	Key createKeys(int p, int q);

	long long calculateBobSign(long long h, unsigned long d, long long n);

	long long calculateAliceSign(long long s, unsigned long e, long long n);

	bool verifySign(long long h, long long h_);
};

#endif // _RSA_H


