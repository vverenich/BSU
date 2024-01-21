#include <iostream>
#include <time.h>
#include <vector>
#include <fstream>
#include <string>
#include "G.h"
#include "RSA.h"


typedef union {
    char arr[4];
    int number;
} raw_int;


raw_int BlockIterativeHashing(const std::string* filename) {
    int d = 8;
    std::ifstream fin;
    fin.open(filename->c_str(), std::ios::in | std::ios::binary);
    unsigned long long t1 = time(NULL);

    raw_int y;
    y.number = 1;
    raw_int xT_plus_1;
    xT_plus_1.number = 0;

    while (fin.peek() != std::ifstream::traits_type::eof()) {
        std::vector<char> key(8);
        for (int i = 0; i < 4; ++i) {
            key[i] = y.arr[i];
            key[i + 4] = key[i];
        }

        G system(key, d);

        raw_int a;
        a.arr[0] = a.arr[1] = a.arr[2] = a.arr[3] = 0;
        fin.read(a.arr, sizeof(int));

        xT_plus_1.number += fin.gcount() * 8;


        int x = a.number;
        a.number ^= y.number;
        for (int i = 0; i < 4; i += 2) {
            std::bitset<8> left(a.arr[i]);
            std::bitset<8> right(a.arr[i + 1]);
            system.iterativeHashing(left, right);
            char g = (char)left.to_ulong();
            char h = (char)right.to_ulong();
            a.arr[i] = g;
            a.arr[i + 1] = h;
        }

        a.number ^= x;
        y.number = a.number;
    }

    std::vector<char> key(8);
    for (int i = 0; i < 4; ++i) {
        key[i] = y.arr[i];
        key[i + 4] = key[i];
    }

    G system(key, d);

    int x = xT_plus_1.number;
    xT_plus_1.number ^= y.number;
    for (int i = 0; i < 4; i += 2) {
        std::bitset<8> left(xT_plus_1.arr[i]);
        std::bitset<8> right(xT_plus_1.arr[i + 1]);
        system.iterativeHashing(left, right);
        char g = (char)left.to_ulong();
        char h = (char)right.to_ulong();
        xT_plus_1.arr[i] = g;
        xT_plus_1.arr[i + 1] = h;
    }

    xT_plus_1.number ^= x;
    y.number = xT_plus_1.number;

    unsigned long long t2 = time(NULL);
    //std::cout << "\nTime Hashing: " << (t2 - t1) << " seconds\n\n";
    fin.close();

    return y;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::vector<char> key(8);
    std::ifstream fin;
    fin.open("key.txt", std::ios::in | std::ios::binary);
    for (int i = 0; i < 4; ++i) {
        fin.read(&key[i], sizeof(char));
        key[i + 4] = key[i];
    }
    fin.close();

    std::string filename = "input.txt";
    raw_int y = BlockIterativeHashing(&filename);
    long long h = (unsigned int)y.number;

    RSA rsa;
    //auto primeNumbers = rsa.generateTwoPrimeNumbers(10'000'000);
    //long long p = primeNumbers.first;
    //long long q = primeNumbers.second;
    //long long p = 9'999'973;        
    //long long q = 9'999'991;
    long long p = 79997;
    long long q = 32117;

    auto keys = rsa.createKeys(p, q);
    auto e_n = keys.getPublicKey();

    long long e = e_n.first;
    long long n = e_n.second;

    long long d = keys.getPrivateKey();

    long long s{ rsa.calculateBobSign(h, d, n) };
    long long h_{ rsa.calculateAliceSign(s, e, n) };

    std::cout << "h  = " << h % n << "\n";

    std::cout << "h' = " << h_ % n << "\n";

    std::cout << "s  = " << s << "\n";

    std::cout << "n  = " << n << "\n";




    return 0;
}
