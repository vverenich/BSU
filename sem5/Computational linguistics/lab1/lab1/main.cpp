#include <iostream>
#include <fstream>
#include <sstream>

#include <QCoreApplication>
#include <QRegularExpression>

#include <dictionary.h>

void menu()
{
    Dictionary dictionary{};
    QString text{};
    QStringList listOfWordsinText{};

    while(true) {
        std::cout << "\n\nChoose one of the following options.\n\n";
        std::cout << "\n1) Initialize dictionary.";
        std::cout << "\n2) Get the number of words in the dictionary.";
        std::cout << "\n3) Add the word.";
        std::cout << "\n4) Remove word.";
        std::cout << "\n5) Check if the word is in the dictionary.";
        std::cout << "\n6) Get the word frequency";
        std::cout << "\n7) Read text.";
        std::cout << "\n8) Replace word in the text.";
        std::cout << "\n9) Find words in text by substring.";
        std::cout << "\n10) Save text.";
        std::cout << "\n11) Sort dictionary by frequency.";
        std::cout << "\n12) Sort dictionary alphabetically.";
        std::cout << "\n13) Exit.";

        std::cout << "\n\nYour choice: ";
        int choice;
        std::cin >> choice;

        switch(choice) {
          case 1: {
            std::fstream file;
            file.open(qApp->applicationDirPath().toStdString() + "/words.txt");
            if(!file.is_open()) {
                std::cout << "\nFile with words hasn't been opened.";
                break;
            }

            std::ostringstream ss;
            ss << file.rdbuf();
            auto textString = QString::fromStdString(ss.str());

            auto listOfWordsinTextDictionary = textString.split(QRegularExpression(R"(\?| |,|-|\.|!|;|"|')"));

            for(const auto& i: listOfWordsinTextDictionary) {
                dictionary.addWord(i.toStdString());
            }

            file.close();

            break;
          }
          case 2: {
            std::cout << "\ndictionary size: " << dictionary.getDictionarySize();

            break;
          }
          case 3: {
            std::cout << "\nEnter the word: ";
            std::string newWord;
            std::cin >> newWord;
            dictionary.addWord(newWord);

            break;
          }
          case 4: {
            std::cout << "\nEnter the word: ";
            std::string word;
            std::cin >> word;

            std::cout << "\nARE YOU SURE YOU WANT TO DELETE THE WORD?";
            std::cout << "\nAnswer(y/n): ";
            char answer;
            std::cin >> answer;

            if(answer == 'y') {
                dictionary.removeWord(word);
            }

            break;
          }
          case 5: {
            std::cout << "\nEnter the word: ";
            std::string word;
            std::cin >> word;

            if(dictionary.isWordInTheDictionary(word)) {
                std::cout << "\nThe word is in the dictionary.";
            } else {
                std::cout << "\nThe word is not in the dictionary.";
            }

            break;
          }
          case 6: {
            std::cout << "\nEnter the word: ";
            std::string word;
            std::cin >> word;

            std::cout << "\nThe freaquency of the word: " << dictionary.getWordFrequency(word);

            break;
          }
          case 7: {
            std::fstream file(qApp->applicationDirPath().toStdString() + "/text.txt");
            if(!file.is_open()) {
                std::cout << "\nFile with text hasn't been opened.";
                break;
            }

            std::ostringstream ss;
            ss << file.rdbuf();
            text = QString::fromStdString(ss.str());

            listOfWordsinText = text.split(QRegularExpression(R"(\?| |,|-|\.|!|;|"|')"));

            for(const auto& i: listOfWordsinText) {
                dictionary.addWord(i.toStdString());
            }

            file.close();

            break;
          }
          case 8: {
            std::cout << "\nEnter the substring before: ";
            std::string subStrBefore;
            std::cin >> subStrBefore;

            std::cout << "\nEnter the substring after: ";
            std::string subStrAfter;
            std::cin >> subStrAfter;

            text.replace(QString::fromStdString(subStrBefore), QString::fromStdString(subStrAfter));

            if(dictionary.isWordInTheDictionary(subStrBefore)) {
                int64_t frequency = dictionary.getWordFrequency(subStrBefore);
                dictionary.setWordFrequency(subStrAfter, dictionary.getWordFrequency(subStrAfter) + frequency);
                dictionary.removeWord(subStrBefore);
            }

            break;
          }
          case 9: {
            std::cout << "\nEnter the substring: ";
            std::string subStr;
            std::cin >> subStr;

            if(!listOfWordsinText.empty()) {
                listOfWordsinText = text.split(QRegularExpression(R"(\?| |,|-|\.|!|;|"|')"));
            }

            std::cout << "\nMatches:";
            for(const auto& i: listOfWordsinText) {
                if(i.contains(QString::fromStdString(subStr))) {
                    std::cout << "\n" << i.toStdString();
                }
            }

            break;
          }
          case 10: {
            std::ofstream file;
            file.open(qApp->applicationDirPath().toStdString() + "/text.txt");
            if(!file.is_open()) {
                std::cout << "\nFile with text hasn't been opened.";
                break;
            }

            file << text.toStdString();

            file.close();

            break;
          }
          case 11: {
            std::vector<std::pair<std::string, int64_t>> mapCopy(dictionary.begin(), dictionary.end());
            std::sort(mapCopy.begin(), mapCopy.end(), [](const std::pair<std::string, int64_t>& a, const std::pair<std::string, int64_t>& b) {
                return a.second < b.second;
            });

            std::ofstream file;
            file.open(qApp->applicationDirPath().toStdString() + "/frequencySort.txt");
            if(!file.is_open()) {
                std::cout << "\nFile with alphabetical sort hasn't been opened.";
                break;
            }

            for(const auto& i : mapCopy) {
                file << i.first << "\t" << i.second << "\n";
            }

            break;
          }
          case 12: {
            std::vector<std::pair<std::string, int64_t>> mapCopy(dictionary.begin(), dictionary.end());
            std::sort(mapCopy.begin(), mapCopy.end(), [](const std::pair<std::string, int64_t>& a, const std::pair<std::string, int64_t>& b) {
                return a.first < b.first;
            });

            std::ofstream file;
            file.open(qApp->applicationDirPath().toStdString() + "/alphabeticalSort.txt");
            if(!file.is_open()) {
                std::cout << "\nFile with frequency sort hasn't been opened.";
                break;
            }

            for(const auto& i : mapCopy) {
                file << i.first << "\t" << i.second << "\n";
            }

            break;
          }
          case 13: {
            return;
          }
          default: {
            std::cout << "\nWrong input";

            break;
          }
        }

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    menu();

    return a.exec();
}
