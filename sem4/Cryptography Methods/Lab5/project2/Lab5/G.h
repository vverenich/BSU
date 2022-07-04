#ifndef _G_H
#define _G_H

#include <vector>
#include <bitset>

class G {
private:
    std::vector<char> clock_keys;
    int clocks;

    static long long IntPow(long long number, unsigned long power);
    static void getSBlocks(std::bitset<8>& b);
public:
    G(const std::vector<char>& clock_keys, int clocks = 1);
    ~G() {}
    void Encryption(std::bitset<8>& a, std::bitset<8>& b);
    void Decryption(std::bitset<8>& a, std::bitset<8>& b);
    void iterativeHashing(std::bitset<8>& x, std::bitset<8>& y);
};

#endif