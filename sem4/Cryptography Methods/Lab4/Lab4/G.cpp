
#include "G.h"

G::G(const std::vector<char>& clock_keys, int clocks) {
    this->clock_keys = std::vector<char>(clock_keys);
    this->clocks = clocks;
}

void G::getSBlocks(std::bitset<8>& b) {
    auto s1 = (b >> 4);
    auto s2 = (b << 4) >> 4;

    b = std::bitset<8>(((((G::IntPow(3, s1.to_ulong()) % 17) + 2) % 16) << 4)
        | (((G::IntPow(5, s2.to_ulong()) % 17) + 7) % 16));
}

int G::IntPow(int number, unsigned long power) {
    if (power == 0)
        return 1;
    if (power % 2 == 0) {
        int pow = G::IntPow(number, power / 2);
        return pow * pow;
    }
    else
        return G::IntPow(number, power - 1) * number;
}

void G::Encryption(std::bitset<8>& a, std::bitset<8>& b) {
    auto temp = b;
    for (size_t i = 0; i < clocks; ++i) {
        b ^= clock_keys[i];

        G::getSBlocks(b);
        b = ((b << 3) | (b >> 5)) ^ a;
        a = temp;
        temp = b;
    }
}

void G::Decryption(std::bitset<8>& a, std::bitset<8>& b) {
    auto temp = a;
    for (size_t i = 0; i < clocks; ++i) {
        a ^= clock_keys[clocks - i - 1];

        G::getSBlocks(a);
        a = ((a << 3) | (a >> 5)) ^ b;
        b = temp;
        temp = a;
    }
}

void G::iterativeHashing(std::bitset<8>& x, std::bitset<8>& y) {
    Encryption(x, y);
}

double G::cumulativeDistribution(double x)
{
    return (1.0 / 2) * (1 + erf(x / sqrt(2)));
}

double G::CumulativeSumsTest(const std::string& sequence, bool mode)
{
    int n = sequence.size();
    std::vector<int> X(n);
    for (int i = 0; i < sequence.size(); ++i) {
        if (sequence[i] == '1') {
            X[i] = 1;
        }
        else if (sequence[i] == '0') {
            X[i] = -1;
        }
    }

    std::vector<int> S(n);

    if (!mode) {
        S[0] = X.front();
        for (int i = 1; i < X.size(); ++i) {
            S[i] = S[i - 1] + X[i];
        }
    }
    else {
        S[0] = X.back();
        for (int i = 1; i < X.size(); ++i) {
            S[i] = S[i - 1] + X[X.size() - i - 1];
        }
    }

    int z = 0;
    for (int val : S) {
        z = std::max(z, std::abs(val));
    }


    double firstValue = 0.0;
    for (int k = (-n / z + 1) / 4; k <= (n / z - 1) / 4; k++) {
        double firstV = cumulativeDistribution(((4.0 * k + 1) * z) / sqrt(n));
        double secondV = cumulativeDistribution(((4.0 * k - 1) * z) / sqrt(n));
        firstValue += firstV - secondV;
    }


    double secondValue = 0.0;
    for (int k = (-n / z - 3) / 4; k <= (n / z - 1) / 4; k++) {
        double firstV = cumulativeDistribution(((4.0 * k + 3) * z) / sqrt(n));
        double secondV = cumulativeDistribution(((4.0 * k + 1) * z) / sqrt(n));
        secondValue += firstV - secondV;
    }

    double pValue = 1 - firstValue + secondValue;

    return pValue;
}
