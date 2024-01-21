#include "backend.h"

#include <QImage>
#include <QDebug>

Backend::Backend()
{

}

void Backend::getInfo(const QString &name)
{
    auto files = name.split(',');
    QString result{};
    for (auto& file : files) {
        file.remove(0, 8);
        QString info = getInfoAboutSingleFile(file);
        result += info + "\n";
    }

    setScrollViewText(result);
}

QString Backend::getScrollViewText() const
{
    return m_ScrollViewText;
}

void Backend::setScrollViewText(const QString &value)
{
    if (m_ScrollViewText == value) {
        return;
    }

    m_ScrollViewText = value;
    emit scrollViewTextChanged();
}

QString Backend::getInfoAboutSingleFile(const QString &name)
{
    QImage image{};
    image.load(name);

    QString pixelSize{QString::number(image.width()) + "x" + QString::number(image.height())};
    QString dotsPerMeterX{QString::number(image.dotsPerMeterX())};
    QString dotsPerMeterY{QString::number(image.dotsPerMeterY())};
    QString depth{QString::number(image.depth())};

    return pixelSize + "\t\t"
           + dotsPerMeterX + "\t\t"
           + dotsPerMeterY + "\t\t"
           + depth + "\t\t"
           + name;
}

void Backend::removeFilePredicateFromUrl(QString &file)
{
    file.remove(0, 8);
}
