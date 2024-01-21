#include <QCoreApplication>

#include "Application.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Application* app = new Application(&a);

    QObject::connect(app, SIGNAL(finished()), &a, SLOT(quit()));
    QTimer::singleShot(1000, app, SLOT(run()));

    return a.exec();
}
