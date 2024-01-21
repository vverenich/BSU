#ifndef LAB3_2_G_H
#define LAB3_2_G_H

#include <vector>
#include <bitset>

class G {
private:
    std::vector<char> clock_keys;
    int clocks;
    static int IntPow(int number, unsigned long power);
    static void getSBlocks(std::bitset<8>& b);
    double cumulativeDistribution(double x);
public:
    G(const std::vector<char>& clock_keys, int clocks = 1);
    ~G() {}
    void Encryption(std::bitset<8>& a, std::bitset<8>& b);
    void Decryption(std::bitset<8>& a, std::bitset<8>& b);
    void iterativeHashing(std::bitset<8>& x, std::bitset<8>& y);
    double CumulativeSumsTest(const std::string& sequence, bool mode);
};

#endif