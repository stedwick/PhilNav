#include "philnavfilter.h"
#include "philnavimageprovider.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>

QImage PhilNavImageProvider::image;

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<PhilNavFilter>("com.philipbrocoum.philnav", 1, 0, "PhilNavFilter");

    QQmlApplicationEngine engine;
    engine.addImageProvider(QLatin1String("philnavimageprovider"), new PhilNavImageProvider);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
