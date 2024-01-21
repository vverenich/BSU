#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include "vigenere.h"
#include "kasiski.h"

std::map <char , double> enLettersFreq = {
        {'A', 0.08167},
        {'B', 0.01492},
        {'C', 0.02782},
        {'D', 0.04253},
        {'E', 0.12702},
        {'F', 0.0228},
        {'G', 0.02015},
        {'H', 0.06094},
        {'I', 0.06966},
        {'J', 0.00153},
        {'K', 0.00772},
        {'L', 0.04025},
        {'M', 0.02406},
        {'N', 0.06749},
        {'O', 0.07507},
        {'P', 0.01929},
        {'Q', 0.00095},
        {'R', 0.05987},
        {'S', 0.06327},
        {'T', 0.09056},
        {'U', 0.02758},
        {'V', 0.00978},
        {'W', 0.0236},
        {'X', 0.0015},
        {'Y', 0.01974},
        {'Z', 0.00074}
};

std::string removePunctuationAndSpacesFromText(const std::string& text)
{
    auto result{text};
    result.erase(std::remove_if(result.begin(),
                               result.end(),
                               [](unsigned char x) { return x == ' '
                                                            || x == '.'
                                                            || x == ','
                                                            || x == '!'
                                                            || x == '"'
                                                            || x == '-'
                                                            || x == '?'
                                                            || x == ':'
                                                            || x == ')'
                                                            || x == '('
                                                             || x == '\n'; }), result.end());

    return result;
}

std::string readFromFileAndDoSomeWork(std::string fileName, std::string key) {
    std::ifstream fin(fileName);
    std::string text((std::istreambuf_iterator<char>(fin)),
                     std::istreambuf_iterator<char>());

    text = removePunctuationAndSpacesFromText(text);
    auto encryptedText = vigenere(text, key, true);
    auto keyLength = getKeyLength(encryptedText);
    auto keyq = getKey(keyLength, encryptedText, enLettersFreq);

    fin.close();
    return keyq;
}

//in{i}.txt and key{i}.txt
void runTest(std::string inDir, std::ofstream& fout) {
    fout << "CURRENT FOLDER IS " << inDir << std::endl;
    int p = 0;
    for(int i = 1; i <= 5; ++i) {
        std::ifstream fin(inDir + "key" + std::to_string(i) + ".txt");
        std::string keyword;
        std::getline(fin, keyword);
        fin.close();

        //auto key = generateValidKey(keyword);
        auto pKey = readFromFileAndDoSomeWork(inDir + "text" + std::to_string(i) + ".txt", keyword);

        if (pKey == keyword) {
            p++;
            fout << "SUCCESS ";
        } else {
            fout << "FAILED ";
        }
        fout << pKey << " and " << keyword << std::endl;


    }
    fout << "SUCCESSFULLY PASSED " << p << " FROM 5" << std::endl;
    fout << "PROBABILITY IS " << p * 1.0/5;
    fout << std::endl << std::endl;
}

void runKeyTests() {

    std::string dir{"/home/verchik/Vlad/Education/BucketList/BSU/crypto/lab1/Lab1/tests/key/"};

    std::ofstream fout(dir + "out_key_tests.txt");

    std::string keyword;

    int p = 0;
    const size_t numberOfFiles{5};
    for(size_t i = 1; i <= numberOfFiles; ++i) {
        fout << "current key is: key" + std::to_string(i) + ".txt";

        std::ifstream fin(dir + "key" + std::to_string(i) + ".txt");
        std::string keyword;
        std::getline(fin, keyword);
        fin.close();

        auto pKey = readFromFileAndDoSomeWork(dir + "text.txt", keyword);

        fout << "\n";
        if (pKey == keyword) {
            p++;
            fout << "SUCCESS: ";
        } else {
            fout << "FAIL:    ";
        }
        fout << pKey << " and " << keyword << std::endl;


    }
    fout << "\n\n";
    fout << "SUCCESSFULLY PASSED " << p << " FROM " << std::to_string(numberOfFiles) << std::endl;
    fout << "PROBABILITY IS " << p * 1.0/numberOfFiles;
    fout << std::endl << std::endl;

    fout.close();
}

void runTextTests() {
    std::string dir{"/home/verchik/Vlad/Education/BucketList/BSU/crypto/lab1/Lab1/tests/text/"};

    std::ofstream fout(dir + "out_text_tests.txt");

    std::ifstream fin(dir + "key.txt");
    std::string keyword;
    std::getline(fin, keyword);
    fin.close();

    int p = 0;
    const size_t numberOfFiles{5};
    for(size_t i = 1; i <= numberOfFiles; ++i) {
        fout << "current file is: text" + std::to_string(i) + ".txt";

        auto pKey = readFromFileAndDoSomeWork(dir + "text" + std::to_string(i) + ".txt", keyword);

        fout << "\n";
        if (pKey == keyword) {
            p++;
            fout << "SUCCESS: ";
        } else {
            fout << "FAIL:    ";
        }
        fout << pKey << " and " << keyword << std::endl;


    }
    fout << "\n\n";
    fout << "SUCCESSFULLY PASSED " << p << " FROM " << std::to_string(numberOfFiles) << std::endl;
    fout << "PROBABILITY IS " << p * 1.0/numberOfFiles;
    fout << std::endl << std::endl;

    fout.close();
}

int main() {
    runKeyTests();
    runTextTests();

    return 0;
}
