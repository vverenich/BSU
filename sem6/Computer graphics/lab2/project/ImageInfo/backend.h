#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>

class Backend : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString scrollViewText READ getScrollViewText WRITE setScrollViewText NOTIFY scrollViewTextChanged)

  signals:
    void scrollViewTextChanged();

  public slots:
    void getInfo(const QString& name);

  public:
    Backend();

    QString getScrollViewText() const;

    void setScrollViewText(const QString& value);

  private:
    QString getInfoAboutSingleFile(const QString& name);
    void removeFilePredicateFromUrl(QString& file);

  private:
    QString       m_ScrollViewText{};
    const QString mc_FileProperties = "pixel size: \t\t dot/meterX: \t\t dot/meterY: \t\t depth: \t\t file name: \n";
};

#endif // BACKEND_H
