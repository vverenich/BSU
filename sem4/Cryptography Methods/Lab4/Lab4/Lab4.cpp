#include <iostream>
#include <time.h>
#include <fstream>
#include <string>
#include "G.h"

typedef union 
{
    char arr[4];
    int number;
} raw_int;


void BlockIterativeHashing(const std::string* filename);

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
    BlockIterativeHashing(&filename);
    //ECB_Encryption(&filename, key);
    //ECB_Decryption(&filename, key);
    //CST(filename, key);
    return 0;
}

void BlockIterativeHashing(const std::string* filename) {
    for (int d = 1; d <= 8; ++d) {
        std::ifstream fin;
        fin.open(filename->c_str(), std::ios::in | std::ios::binary);
        std::ofstream fout;
        fout.open(("h_" + std::to_string(d) + *filename).c_str()/*, std::ios::out | std::ios::binary*/);
        unsigned long long t1 = time(NULL);

        raw_int y;
        y.number = 2;
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

        fout.write(y.arr, sizeof(int));
        //fout << std::ios::hex << y.number;
        unsigned long long t2 = time(NULL);
        std::cout << "\nTime Hashing: " << (t2 - t1) << " seconds";
        fin.close();
        fout.close();
    }
}