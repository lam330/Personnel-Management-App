#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "client.h"
#include "databasemanager.h"


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QSharedPointer<SimpleSwitchReplica> ptr; // shared pointer to hold source replica
    QRemoteObjectNode repNode; // create remote object node
    repNode.connectToNode(QUrl(QStringLiteral("local:switch"))); // connect with remote host node
    ptr.reset(repNode.acquire<SimpleSwitchReplica>()); // acquire replica of source from host node
    Client rswitch(ptr); // create client switch object and pass reference of replica to it

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("myModel", &rswitch);
    engine.rootContext()->setContextProperty("myDatabase", &DatabaseManager::instance());

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
