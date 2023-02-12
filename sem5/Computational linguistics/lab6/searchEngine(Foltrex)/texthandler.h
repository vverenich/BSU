#ifndef TEXTHANDLER_H
#define TEXTHANDLER_H

#include <map>

#include <QString>

#include "pod.h"
#include "dictionary.h"
#include "poz.h"

class TextHandler
{
public:
    TextHandler();

    void initializeTextHandler();
    void handleText(const QString& text, const QString& fileName);
    void tagText(const QString& text);
    QString getTaggedText();
    void countWordsAndGetWordWeight(const QString& text);
    QString getVectorOfWordsAndWeight();
    void createPOD(const std::string& fileName);
    std::vector<POD> pods;
    void createPOZ(const QString& text);
    POZ poz{};
    QString getWordsPOZ();
    void findRelevantDocs();
    QString getDocsAndRelevantCoeffs();


private:
    void addPOStoTaggedWords(const std::string& fileName, const QString& tag);

    QString m_taggedText{};
    std::map<QString, QString> m_taggedWords{};
    Dictionary m_dictionary{};
    std::vector<std::pair<std::string, int64_t>> m_wordsAndFreq;
    std::vector<std::pair<std::string, double>> m_docsAndRelevantCoefficient;
};

#endif // TEXTHANDLER_H
