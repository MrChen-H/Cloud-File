#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <qfont.h>
#include <qfontdatabase.h>
#include <Model/downloadstatemodel.h>
#include <Model/allfilemodel.h>
#include "QQmlContext"
#include "Net_Work/networkoperate.h"
int main(int argc, char *argv[])
{

    QGuiApplication app(argc, argv);

    NetWorkOperation NetWork;

    QQmlApplicationEngine engine;
    qmlRegisterSingletonType<DownLoadStateModel>("DownLoadStateModel", 1, 0, "DownLoadStateModel", [](QQmlEngine *engine, QJSEngine *) -> QObject* {
        Q_UNUSED(engine)
        return DownLoadStateModel::getInstance();
    });
    qmlRegisterSingletonType<AllFileModel>("AllFileModel", 1, 0, "AllFileModel", [](QQmlEngine *engine, QJSEngine *) -> QObject* {
        Q_UNUSED(engine)
        return AllFileModel::getInstance();
    });

    engine.rootContext()->setContextProperty("NetWork",&NetWork);

    const QUrl url(u"qrc:/Cloud_File_Client/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);
//    engine.rootContext()->setContextProperty("FontDefault");
    return app.exec();
}
