#include <iostream>
#include <fstream>
#include <sstream>

#include <QCoreApplication>
#include <QRegularExpression>
#include <QDebug>

#include "backend.h"

BackEnd::BackEnd()
{

}

void BackEnd::addDocument(const QString &doc)
{
    std::ifstream file;
    file.open(qApp->applicationDirPath().toStdString() + "/" + doc.toStdString());
    if (!file.is_open()) {
        qDebug() << "\nFile with " + doc + " hasn't been opened.";
        return;
    }

    std::ostringstream ss;
    ss << file.rdbuf();
    QString text = QString::fromStdString(ss.str());

    m_textHandler.handleText(text, doc);

    file.close();
}

QString BackEnd::getWordsAndWeight()
{
    //std::cout << m_textHandler.getVectorOfWordsAndWeight().toStdString();
    return m_textHandler.getVectorOfWordsAndWeight();
}

QString BackEnd::getTaggedText()
{
    //std::cout << m_textHandler.getTaggedText().toStdString();
    return m_textHandler.getTaggedText();
}

void BackEnd::handleSearch(const QString& text)
{
    m_textHandler.createPOZ(text);
    m_textHandler.findRelevantDocs();
}

QString BackEnd::getInformativeWordsPOZ()
{
    return m_textHandler.getWordsPOZ();
}

QString BackEnd::getResults()
{
    return m_textHandler.getDocsAndRelevantCoeffs();
}

