#include <fstream>
#include <iostream>

#include <QCoreApplication>
#include <QDebug>
#include <QRegularExpression>

#include "texthandler.h"

TextHandler::TextHandler()
{
    initializeTextHandler();

    //QString text = "A preposition is a word placed before a noun or pronoun to form a phrase modifying another word in the sentence. Therefore a preposition preposition is always part of a prepositional phrase. The prepositional phrase almost always functions as an adjective or as an adverb.";
    //handleText(text, "file.txt");
    //std::cout << getVectorOfWordsAndWeight().toStdString();
    //std::cout << pods.at(0).fileName;
    //std::cout << pods.at(0).informativeWords.back().first << pods.at(0).informativeWords.back().second;

}

void TextHandler::initializeTextHandler()
{
    addPOStoTaggedWords("nouns.txt", "/NN/");
    addPOStoTaggedWords("adjectives.txt", "/JJ/");
    addPOStoTaggedWords("verbs.txt", "/VB/");
    addPOStoTaggedWords("adverbs.txt", "/RB/");
    addPOStoTaggedWords("pronouns.txt", "/PR/");
    addPOStoTaggedWords("prepositions.txt", "/PRE/");
    addPOStoTaggedWords("conjunctions.txt", "/CC/");
}

void TextHandler::handleText(const QString &text, const QString& fileName)
{
    tagText(text);
    countWordsAndGetWordWeight(text);
    createPOD(fileName.toStdString());
}


void TextHandler::tagText(const QString &text)
{
    QStringList list = text.split(QRegularExpression("\\b"));

    m_taggedText.clear();
    m_taggedText.reserve(text.size() * 2);

    QRegularExpression re("\\W+");

    for(auto str : list) {
        if (m_taggedWords.find(str) != m_taggedWords.end()) {
            str += m_taggedWords.at(str);
        } else {
            QRegularExpressionMatch match = re.match(str);
            if(!match.hasMatch()) {
                str += "/DPS/";
            }
        }

        m_taggedText += str;
    }
}

QString TextHandler::getTaggedText()
{
    return m_taggedText;
}

void TextHandler::countWordsAndGetWordWeight(const QString &text)
{
    QStringList list;
    list = text.split(QRegularExpression("\\s+"));

    m_dictionary.clearDictionary();
    for (auto & str : list) {
        if (m_taggedWords.find(str) != m_taggedWords.end()) {
            if(m_taggedWords.at(str) == "/PRE/" ||
               m_taggedWords.at(str) == "/PR/" ||
               m_taggedWords.at(str) == "/CC/" ) {
                continue;
            }
        }
        m_dictionary.addWord(str.toStdString());
    }

    std::vector<std::pair<std::string, int64_t>> mapCopy(m_dictionary.begin(), m_dictionary.end());
    std::sort(mapCopy.begin(), mapCopy.end(),
              [](const std::pair<std::string, int64_t>& a,
                 const std::pair<std::string, int64_t>& b)
                {
                    return a.second > b.second;
                });
    /*
    for (auto& i : mapCopy) {
        i.second /= mapCopy.at(0).second;
    }
    */

    m_wordsAndFreq = mapCopy;
}

QString TextHandler::getVectorOfWordsAndWeight()
{
    QString result;
    int64_t maxFreq = m_wordsAndFreq.at(0).second;
    for (auto& i : m_wordsAndFreq) {
        result += QString::fromStdString(i.first) + "\t" + QString::number((double)i.second / maxFreq)+ "\n";
    }

    return result;
}

void TextHandler::createPOD(const std::string& fileName)
{
    POD pod{};
    pod.fileName = fileName;
    int64_t maxFreq = m_wordsAndFreq.at(0).second;
    for (auto& i : m_wordsAndFreq) {
        pod.informativeWords.push_back({i.first, (double)i.second / maxFreq});
    }

    pods.push_back(pod);
}

void TextHandler::createPOZ(const QString &text)
{
    QStringList list;
    list = text.split(QRegularExpression("\\s+"));
    poz.informativeWords.clear();

    for (auto & str : list) {
        if (m_taggedWords.find(str) != m_taggedWords.end()) {
            if(m_taggedWords.at(str) == "/PRE/" ||
               m_taggedWords.at(str) == "/PR/" ||
               m_taggedWords.at(str) == "/CC/" ) {
                continue;
            }
        }
        poz.informativeWords.push_back(str);
    }
}

QString TextHandler::getWordsPOZ()
{
    QString result{};

    for (const auto& str : poz.informativeWords) {
        result += str + "\n";
    }

    return result;
}

void TextHandler::findRelevantDocs()
{
    m_docsAndRelevantCoefficient.clear();
    for (const auto& pod : pods) {
        double relevance = 0;
        for(const auto& infWord : pod.informativeWords) {
            for(const auto& word : poz.informativeWords) {
                if (infWord.first == word.toStdString()) {
                    relevance += infWord.second;
                }
            }
        }

        std::sort(m_docsAndRelevantCoefficient.begin(), m_docsAndRelevantCoefficient.end(),
                  [](const std::pair<std::string, double>& a,
                     const std::pair<std::string, double>& b)
                    {
                        return a.second > b.second;
                    });

        m_docsAndRelevantCoefficient.push_back({pod.fileName, relevance});
    }
}

QString TextHandler::getDocsAndRelevantCoeffs()
{
    QString result{};
    //qDebug() << " HERER: "<< m_docsAndRelevantCoefficient.size();
    for (const auto& doc : m_docsAndRelevantCoefficient) {
        result += QString::fromStdString(doc.first) + "\t\t" + QString::number(doc.second) + "\n";
    }

    return result;
}

void TextHandler::addPOStoTaggedWords(const std::string &fileName, const QString &tag)
{
    std::ifstream file;
    file.open(qApp->applicationDirPath().toStdString() + "/" + fileName);
    if (!file.is_open()) {
        qDebug() << "\nFile with " + QString::fromStdString(fileName) + " hasn't been opened.";
        return;
    }

    std::string word;
    while(!file.eof()) {
        file >> word;
        m_taggedWords.insert({QString::fromStdString(word), tag});
    }

    file.close();
}
