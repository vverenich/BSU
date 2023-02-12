#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>

#include "texthandler.h"


class BackEnd : public QObject {

    Q_OBJECT

  public:
    BackEnd();

  public slots:
    void addDocument(const QString& doc);
    QString getWordsAndWeight();
    QString getTaggedText();
    void handleSearch(const QString& text);
    QString getInformativeWordsPOZ();
    QString getResults();

  private:
    TextHandler m_textHandler{};
};

#endif // BACKEND_H
