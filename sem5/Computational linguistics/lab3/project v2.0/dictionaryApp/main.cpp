#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QQuickStyle>
#include <QQmlContext>
#include <QIcon>
#include <backend.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    //
    app.setOrganizationName("verchikLab");
    app.setOrganizationDomain("verchikLabDomain");
    app.setAttribute(Qt::ApplicationAttribute::AA_UseOpenGLES, true);
    qmlRegisterType<BackEnd>( "BackEnd",1,0, "BackEnd");
    //QQuickStyle::setStyle("Material");
    QQuickStyle::setStyle("Fusion");
    app.setWindowIcon(QIcon(QCoreApplication::applicationDirPath() + "/applicationIcon.png"));
    //


    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
