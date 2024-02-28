#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <qfont.h>
#include <qfontdatabase.h>
#include <Model/downloadstatemodel.h>
#include "QQmlContext"

int main(int argc, char *argv[])
{

    QGuiApplication app(argc, argv);
    const QString fontPath = "qrc:/Font/Segoe_Fluent_Icons.ttf"; // 资源路径
    if (QFontDatabase::addApplicationFont(fontPath) == -1) {
        qWarning() << "Failed to load custom font";
    }
    QQmlApplicationEngine engine;
    qmlRegisterSingletonType<DownLoadStateModel>("DownLoadStateModel", 1, 0, "DownLoadStateModel", [](QQmlEngine *engine, QJSEngine *) -> QObject* {
        Q_UNUSED(engine)
        return DownLoadStateModel::getInstance();
    });

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
