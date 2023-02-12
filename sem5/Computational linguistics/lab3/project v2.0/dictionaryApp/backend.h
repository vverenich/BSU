#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>

#include "dictionary.h"

class BackEnd : public QObject {

    Q_OBJECT

  public:
    BackEnd();

  public slots:
    void initializeDictionary();
    int getNumberOfWordsInDictionary();
    int getTotalNumberOfWords();
    void addWordToTheDictionary(const QString& word, int number = 1);
    void removeWord(const QString& word);
    bool isWordInTheDictionary(const QString& word);
    double getWordFrequency(const QString& word);
    void readTextFromFile(const QString& fileName);
    void replaceWord(const QString& from, const QString& to);
    void getMatchesBegin(const QString& subStr);
    void getMatchesEnd(const QString& subStr);
    QString getMatchesSortedAlphabetically();
    QString getMatchesSortedByFrequencyAsc();
    QString getMatchesSortedByFrequencyDesc();
    int getNumberOfUniqueMatches();
    int getTotalNumberOfMatches();
    void saveText(const QString& word);
    QString getWordsSortedAlphabetically();
    QString getWordsSortedByFrequencyAsc();
    QString getWordsSortedByFrequencyDesc();
    void saveDictionary(const QString& fileName);
    void clearDictionary();

  private:
    Dictionary dictionary{};
    QString text{};
    QStringList listOfWordsinText{};
    std::vector<std::pair<QString, int64_t>> mapCopyMatches{};
};

#endif // BACKEND_H
