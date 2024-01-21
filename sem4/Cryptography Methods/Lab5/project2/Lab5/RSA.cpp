#include "RSA.h"
#include <vector>
#include <algorithm>

long long RSA::modInv(const long long& base, const long long& mod)
{
    long long u1 = 1, u3 = base, v1 = 0, v3 = mod, t1 = 0, t3 = 0, q = 0;
    int iter = 1;

    while (v3 != 0)
    {
        q = u3 / v3;
        t3 = u3 % v3;
        t1 = u1 + q * v1;

        u1 = v1; v1 = t1; u3 = v3; v3 = t3;
        iter = -iter;
    }

    if (u3 != 1)
        return 0;

    if (iter < 0)
        return mod - u1;
    else
        return u1;
}

long long RSA::gcd(long long a, long long b)
{
    while (a and b) {
        if (a > b)
            a %= b;
        else
            b %= a;
    }
    return a + b;
}

long long RSA::pow(long long base, unsigned long power, long long mod)
{
    long long c(1);
    for (int i = 1; i <= power; ++i) {
        c = ((base % mod) * (c % mod)) % mod;
    }

    return c;
}

std::pair<int, int> RSA::generateTwoPrimeNumbers(int upperBound) {
    // Create a boolean array "prime[0..n]" and initialize
    // all entries it as true. A value in prime[i] will
    // finally be false if i is Not a prime, else true.
    std::vector<bool> prime(upperBound + 1, true);

    for (int p = 2; p * p <= upperBound; p++) {
        if (prime[p] == true) {
            for (int i = p * p; i <= upperBound; i += p)
                prime[i] = false;
        }
    }


    // Add to vector all prime numbers
    int countOfPrimes{};
    int firstPrime{};
    int secondPrime{};
    for (int p = upperBound; p >= 2; p--) {
        if (countOfPrimes == 2) {
            break;
        }

        if (prime[p]) {
            if (secondPrime) {
                firstPrime = p;
            }
            else {
                secondPrime = p;
            }

            countOfPrimes++;
        }
    }

    return std::make_pair(firstPrime, secondPrime);
}

long long RSA::calculateN(int p, int q)
{
    return static_cast<long long>(p) * q;
}

long long RSA::calculatePhi(int p, int q)
{
    return static_cast<long long>(p - 1) * static_cast<long long>(q - 1);
}

long long RSA::calculateD(long long phi, long long e)
{
    long long gcd = this->modInv(e, phi);
    return gcd;
}

Key RSA::createKeys(int p, int q)
{
    long long e = 59;
    long long n = calculateN(p, q);

    long long phi = calculatePhi(p, q);
    long long d = this->modInv(e, phi);

    Key key{ std::make_pair(e, n), d };
    return key;
}

long long RSA::calculateBobSign(long long h, unsigned long d, long long n) 
{
    return pow(h, d, n);
}

long long RSA::calculateAliceSign(long long s, unsigned long e, long long n)
{
    return pow(s, e, n);
}

bool RSA::verifySign(long long h, long long h_)
{
    return h == h_;
}
