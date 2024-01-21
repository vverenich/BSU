#include <map>
#include <unordered_map>
#include "kasiski.h"

std::string filterText(std::string text) {
    std::string filteredText;
    for (char c : text) {
        char newC = toupper(c);
        if (isalpha(newC)) {
            filteredText.push_back(newC);
        }
    }
    return filteredText;
}

int gcd(int a, int b) {
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

int findGCD(std::vector<int> vector) {
    int result = vector.front();
    for(auto it = vector.begin() + 1; it != vector.end(); ++it) {
        result = gcd(*it, result);
    }
    return result;
}

int getKeyLength(std::string text) {
    std::unordered_map<std::string, std::vector<int>> map;
    std::string filteredText = filterText(text);

    for(int i = 0; i < filteredText.length(); ++i) {
        auto currentGramm = std::string(&filteredText[i], &filteredText[i] + 3);
        for(int j = i + 3; j < filteredText.length() - 3; ++j) {
            auto tmpGramm = std::string(&filteredText[j], &filteredText[j] + 3);
            if (currentGramm == tmpGramm) {
                if (map.find(currentGramm) == map.end()) {
                    map.insert(make_pair(currentGramm, std::vector<int>()));
                }
                map.at(currentGramm).push_back(j - i);
            }
        }
    }
    if (map.empty())
        return 0;
    std::vector<int> maxVector;
    for(auto & it : map) {
        if (maxVector.size() <= it.second.size()) {
            maxVector = it.second;
        }
    }
    return findGCD(maxVector);
}

std::pair<char, double > mostUsedLetter(std::vector<char> letters) {
    std::map <char ,int> map;
    for(auto&i : letters) {
        if (map.find(i) == map.end()) {
            map[i] = 1;
        }
        map[i] += 1;
    }
    char mostUsed;
    int count = 0;
    for(auto&it : map) {
        if (count <= it.second) {
            count = it.second;
            mostUsed = it.first;
        }
    }
    return std::make_pair(mostUsed, 1.0 * count/letters.size());
}

void resetMap(std::map <char, double>& map)
{
    for (auto& [letter, count] : map) {
        count = 0;
    }
}

 char getLetter(std::vector<char> letters, const std::map <char ,double>& lettersFreq) {
    std::map <char , double> map = lettersFreq;
    resetMap(map);
    for(auto&i : letters) {
        map[i] += 1.0;
    }

    for (auto& [letter, freq] : map) {
        freq /= letters.size();
    }


    std::pair<char, double> letter{'A', std::numeric_limits<double>::max()};
    auto iterations = lettersFreq.size();
    for (size_t shift{0}; shift < iterations; ++shift) {
        double diff = 0;
        for (size_t j{0}; j < iterations; ++j) {
            diff += std::abs(map.at('A' + (j + shift) % iterations) - lettersFreq.at('A' + j));
        }

        if (letter.second > diff) {
            letter.first = 'A' + shift;
            letter.second = diff;
        }
    }

    return letter.first;
}





std::string getKey(int keyLength, std::string text, const std::map <char ,double>& lettersFreq) {
    if (keyLength == 0)
        return "";
    std::string filteredText = filterText(text);
    std::vector<std::vector<char>> tmp(keyLength);
    std::string key;

    for(unsigned i = 0; i < filteredText.length(); i+= keyLength) {
        int j = 0;
        while (j != keyLength && i+j < filteredText.length()) {
            tmp[j].push_back(filteredText[i+j]);
            j++;
        }
    }

    for(auto& letters : tmp) {
        char letter = getLetter(letters, lettersFreq);
        key += letter;
    }

    return key;
}
