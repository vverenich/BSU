
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

long long G::IntPow(long long number, unsigned long power) {
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