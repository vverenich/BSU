#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include <QDebug>
const std::string alphabet { "abcdefghijklmnopqrstuvwxyz" };

void encryptStringVigenere(std::string& text, const std::string& key)
{
    for (size_t i { 0 }; i < text.size(); ++i) {
        text.at(i) = (text.at(i) - 'a' + key[i % key.size()] - 'a') % 26 + 'a';
    }
}

void decryptStringVigenere(std::string& text, const std::string& key)
{
    for (size_t i { 0 }; i < text.size(); ++i) {
        if (text.at(i) >= key[i % key.size()]) {
            text.at(i) = text.at(i) - key[i % key.size()] + 'a';
        } else {
            text.at(i) = (text.at(i) - 'a' + 26 - (key[i % key.size()] - 'a')) + 'a';
        }
    }
}

void encryptStringSubstitute(std::string& text, const std::string& key)
{
    for (auto& i : text) {
        if ('a' <= i && i <= 'z') {
            i = key[i - 'a'];
        }
    }
}

void decryptStringSubstitute(std::string& text, const std::string& key)
{
    std::map<char, char> dictionary;
    for (size_t i { 0 }; i < key.size(); ++i) {
        dictionary.insert(std::pair<char, char>(key.at(i), 'a' + i));
    }

    for (size_t i { 0 }; i < text.size(); ++i) {
        if ('a' <= text.at(i) && i <= 'z') {
            text.at(i) = dictionary[text.at(i)];
        }
    }
}

void customShuffle(std::string& key)
{
    std::mt19937 mersenne(static_cast<unsigned int>(time(0)));

    for (size_t i { 0 }; i < key.size(); ++i) {
        std::swap(key[i], key[mersenne() % key.size()]);
    }
}

int main()
{
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
    std::fstream inOutKey("key.txt");

    if (!fin.is_open()) {
        return 0;
    }

    int isEncrypting;
    fin >> isEncrypting;

    std::vector<std::string> text;

    fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    int cipherType;
    fin >> cipherType;

    fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (fin.peek() != EOF) {
        std::string row;
        std::getline(fin, row, '\n');
        text.emplace_back(row);
    }

    std::string key;
    if (isEncrypting) {
        if (cipherType == 1) {
            key = alphabet;
            customShuffle(key);
            //fout << "KEY: " << key << "\n";
        }

        if (cipherType == 2) {
            std::cout << "Enter key: ";
            std::cin >> key;
        }
        inOutKey << key;
    } else {
        //key = text.back();
        inOutKey >> key;
        //text.pop_back();
    }

    for (auto& i : text) {
        if (cipherType == 1) {
            if (isEncrypting) {
                encryptStringSubstitute(i, key);
            } else {
                decryptStringSubstitute(i, key);
            }
        }

        if (cipherType == 2) {
            if (isEncrypting) {
                encryptStringVigenere(i, key);
            } else {
                decryptStringVigenere(i, key);
            }
        }
        fout << i;
    }

    fin.close();
    fout.close();
}
