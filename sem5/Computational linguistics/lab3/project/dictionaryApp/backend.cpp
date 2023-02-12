#include <iostream>
#include <fstream>
#include <sstream>

#include <QCoreApplication>
#include <QRegularExpression>

#include "backend.h"

BackEnd::BackEnd()
{

}

void BackEnd::initializeDictionary()
{
    std::fstream file;
    file.open(qApp->applicationDirPath().toStdString() + "/text.txt");
    if (!file.is_open()) {
        std::cout << "\nFile with words hasn't been opened.";
        return;
    }

    std::ostringstream ss;
    ss << file.rdbuf();
    auto textString = QString::fromStdString(ss.str());

    auto listOfWordsinTextDictionary =
            textString.split(QRegularExpression(R"(\?| |,|-|\.|!|;|"|')"));

    for (const auto& i: listOfWordsinTextDictionary) {
        if (i.toStdString() != "") {
            dictionary.addWord(i.toStdString());
        }
    }

    file.close();

    return;
}

int BackEnd::getNumberOfWordsInDictionary()
{
    return dictionary.getDictionarySize();
}

int BackEnd::getTotalNumberOfWords()
{
    return dictionary.getTotalNumberOfWordsInDictionary();
}

void BackEnd::addWordToTheDictionary(const QString &word, int number)
{
    dictionary.addWord(word.toStdString(), number);
}

void BackEnd::removeWord(const QString &word)
{
    dictionary.removeWord(word.toStdString());
}

bool BackEnd::isWordInTheDictionary(const QString &word)
{
    return dictionary.isWordInTheDictionary(word.toStdString());
}

double BackEnd::getWordFrequency(const QString &word)
{
    int64_t number = dictionary.getWordFrequency(word.toStdString());
    if (number == -1) {
        return number;
    }

    return (double)number / dictionary.getTotalNumberOfWordsInDictionary();
}

void BackEnd::readTextFromFile(const QString &fileName)
{
    std::fstream file(qApp->applicationDirPath().toStdString() + "/" + fileName.toStdString());
    if (!file.is_open()) {
        std::cout << "\nFile with text hasn't been opened.";
        return;
    }

    std::ostringstream ss;
    ss << file.rdbuf();
    text = QString::fromStdString(ss.str());

    listOfWordsinText = text.split(QRegularExpression(R"(\?| |,|-|\.|!|;|"|'|\n|\t)"));

    for (const auto& i: listOfWordsinText) {
        if (i == "") {
            continue;
        }
        dictionary.addWord(i.toStdString());
    }

    file.close();

    return;
}

void BackEnd::replaceWord(const QString &from, const QString &to)
{
    text.replace(from, to);

    if (dictionary.isWordInTheDictionary(from.toStdString())) {
        int64_t frequency = dictionary.getWordFrequency(from.toStdString());
        dictionary.setWordFrequency(to.toStdString(),
                                    dictionary.getWordFrequency(to.toStdString()) + frequency);
        dictionary.removeWord(from.toStdString());
    }

    return;
}

void BackEnd::getMatchesBegin(const QString &subStr)
{
    std::vector<std::pair<QString, int64_t>> mapCopy(dictionary.getDictionarySize());
    int index = 0;
    for (auto i = dictionary.begin(); i != dictionary.end(); ++i, ++index) {
        mapCopy.at(index).first = QString::fromStdString(i->first);
        mapCopy.at(index).second = i->second;
    }

    mapCopyMatches.clear();
    mapCopyMatches.reserve(mapCopy.size());

    for (const auto& i: mapCopy) {
        if (i.first.size() == 0 || subStr.size() == 0) {
            continue;
        }

        if (i.first.contains(subStr, Qt::CaseInsensitive)) {
            // Check if the substring at the beginning of the word
            int index = 0;
            for (index = 0; index < subStr.size(); ++index) {
                if (i.first.at(index).toLower() != subStr.at(index).toLower()) {
                    break;
                }
            }

            if (index != subStr.size()) {
                continue;
            }

            mapCopyMatches.push_back(std::make_pair(i.first, i.second));
        }
    }
}

void BackEnd::getMatchesEnd(const QString &subStr)
{
    std::vector<std::pair<QString, int64_t>> mapCopy(dictionary.getDictionarySize());
    int index = 0;
    for (auto i = dictionary.begin(); i != dictionary.end(); ++i, ++index) {
        mapCopy.at(index).first = QString::fromStdString(i->first);
        mapCopy.at(index).second = i->second;
    }

    mapCopyMatches.clear();
    mapCopyMatches.reserve(mapCopy.size());

    for (const auto& i: mapCopy) {
        if (i.first.size() == 0 || subStr.size() == 0) {
            continue;
        }

        if (i.first.contains(subStr, Qt::CaseInsensitive)) {
            // Check if the substring at the beginning of the word
            int indexOfCharInSubstr = subStr.size() - 1;
            int indexOfCharInWord = i.first.size() - 1;
            for (indexOfCharInSubstr = subStr.size() - 1; indexOfCharInSubstr >= 0; --indexOfCharInSubstr, --indexOfCharInWord) {
                if (i.first.at(indexOfCharInWord).toLower() != subStr.at(indexOfCharInSubstr).toLower()) {
                    break;
                }
            }

            if (indexOfCharInSubstr != -1) {
                continue;
            }

            mapCopyMatches.push_back(std::make_pair(i.first, i.second));
        }
    }
}

QString BackEnd::getMatchesSortedAlphabetically()
{
    int numberOfWords = dictionary.getTotalNumberOfWordsInDictionary();
    std::sort(mapCopyMatches.begin(), mapCopyMatches.end(),
              [](const std::pair<QString, int64_t>& a,
                 const std::pair<QString, int64_t>& b)
                {
                    return a.first < b.first;
                });

    QString result{};
    for(const auto& i : mapCopyMatches) {
        result += i.first + "\t" + QString::number((double)i.second / numberOfWords) + "\n";
    }

    return result;
}

QString BackEnd::getMatchesSortedByFrequencyAsc()
{
    int numberOfWords = dictionary.getTotalNumberOfWordsInDictionary();
    std::sort(mapCopyMatches.begin(), mapCopyMatches.end(),
              [](const std::pair<QString, int64_t>& a,
                 const std::pair<QString, int64_t>& b)
                {
                    return a.second < b.second;
                });

    QString result{};
    for (const auto& i : mapCopyMatches) {
        result += i.first + "\t" + QString::number((double)i.second / numberOfWords) + "\n";
    }

    return result;
}

QString BackEnd::getMatchesSortedByFrequencyDesc()
{
    int numberOfWords = dictionary.getTotalNumberOfWordsInDictionary();
    std::sort(mapCopyMatches.begin(), mapCopyMatches.end(),
              [](const std::pair<QString, int64_t>& a,
                 const std::pair<QString, int64_t>& b)
                {
                    return a.second > b.second;
                });

    QString result{};
    for(const auto& i : mapCopyMatches) {
        result += i.first + "\t" + QString::number((double)i.second / numberOfWords) + "\n";
    }

    return result;
}

int BackEnd::getNumberOfUniqueMatches()
{
    return mapCopyMatches.size();
}

int BackEnd::getTotalNumberOfMatches()
{
    int sum = 0;
    for(const auto& i : mapCopyMatches) {
        sum += i.second;
    }

    return sum;
}

void BackEnd::saveText(const QString& word)
{
    std::ofstream file;
    file.open(qApp->applicationDirPath().toStdString() + "/" + word.toStdString());
    if(!file.is_open()) {
        std::cout << "\nFile with text hasn't been opened.";
        return;
    }

    file << text.toStdString();

    file.close();

    return;
}

QString BackEnd::getWordsSortedAlphabetically()
{
    int numberOfWords = dictionary.getTotalNumberOfWordsInDictionary();
    std::vector<std::pair<std::string, int64_t>> mapCopy(dictionary.begin(), dictionary.end());
    std::sort(mapCopy.begin(), mapCopy.end(),
              [](const std::pair<std::string, int64_t>& a,
                 const std::pair<std::string, int64_t>& b)
                {
                    return a.first < b.first;
                });

    QString result{};
    for (const auto& i : mapCopy) {
        result += QString::fromStdString(i.first + "\t" +
                                         std::to_string((double)i.second / numberOfWords) + "\n");
    }

    return result;
}

QString BackEnd::getWordsSortedByFrequencyAsc()
{
    int numberOfWords = dictionary.getTotalNumberOfWordsInDictionary();
    std::vector<std::pair<std::string, int64_t>> mapCopy(dictionary.begin(), dictionary.end());
    std::sort(mapCopy.begin(), mapCopy.end(),
              [](const std::pair<std::string, int64_t>& a,
                 const std::pair<std::string, int64_t>& b)
                {
                    return a.second < b.second;
                });

    QString result{};
    for (const auto& i : mapCopy) {
        result += QString::fromStdString(i.first + "\t" +
                                         std::to_string((double)i.second / numberOfWords) + "\n");
    }

    return result;
}

QString BackEnd::getWordsSortedByFrequencyDesc()
{
    int numberOfWords = dictionary.getTotalNumberOfWordsInDictionary();
    std::vector<std::pair<std::string, int64_t>> mapCopy(dictionary.begin(), dictionary.end());
    std::sort(mapCopy.begin(), mapCopy.end(),
              [](const std::pair<std::string, int64_t>& a,
                 const std::pair<std::string, int64_t>& b)
                {
                    return a.second > b.second;
                });

    QString result{};
    for (const auto& i : mapCopy) {
        result += QString::fromStdString(i.first + "\t" +
                                         std::to_string((double)i.second / numberOfWords) + "\n");
    }

    return result;
}

void BackEnd::saveDictionary(const QString &fileName)
{
    std::ofstream file;
    file.open(qApp->applicationDirPath().toStdString() + "/" + fileName.toStdString());
    if (!file.is_open()) {
        std::cout << "\nFile with frequency sort hasn't been opened.";
        return;
    }

    for (auto i = dictionary.begin(); i != dictionary.end(); ++i) {
        file << i->first << "\t" << (double)i->second << "\n";
    }

}

void BackEnd::clearDictionary()
{
    dictionary.clearDictionary();
}

void BackEnd::restoreDictionary(const QString &fileName)
{
    dictionary.clearDictionary();

    std::ifstream file;
    file.open(qApp->applicationDirPath().toStdString() + "/" + fileName.toStdString());
    if (!file.is_open()) {
        std::cout << "\nFile with frequency sort hasn't been opened.";
        return;
    }

    while(!file.eof()) {

        std::string word;
        file >> word;
        int freq;
        file >> freq;

        dictionary.addWord(word);
        dictionary.setWordFrequency(word, freq);
    }
}
