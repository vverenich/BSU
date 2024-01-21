#ifndef LAB1_VIGENERE_H
#define LAB1_VIGENERE_H
#include <string>

std::string generateValidKey(const std::string& key);
std::string vigenere(std::string text, std::string key, bool isEncryption);

#endif //LAB1_VIGENERE_H
