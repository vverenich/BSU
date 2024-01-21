#include "vigenere.h"

bool isSmallLetter(char c) {
    return c >= 'a' && c <= 'z';
}

bool isBigLetter(char c) {
    return c >= 'A' && c <= 'Z';
}

std::string generateValidKey(const std::string& key) {
    std::string validKey;
    for (char c : key) {
        if (isSmallLetter(c))
            validKey.push_back(toupper(c));
        else if (isBigLetter(c))
            validKey.push_back(c);
    }
    return validKey;
}

std::string vigenere(std::string text, std::string key, bool isEncryption) {
    std::string newText;

    for (unsigned int i = 0, j = 0; i < text.length(); ++i) {
        char c = text[i];
        bool isSmall = isSmallLetter(c);

        if (isSmall)
            c = toupper(c);
        else if (!isBigLetter(c)) {
            newText.push_back(c);
            continue;
        }

        if (isEncryption)
            newText.push_back((c + key[j]) % 26 + (isSmall ? 'a' : 'A'));
        else
            newText.push_back((c - key[j] + 26) % 26 + (isSmall ? 'a' : 'A'));
        j = (j + 1) % key.length();
    }

    return newText;
}