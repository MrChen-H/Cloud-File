#ifndef GLOBALSTATUS_H
#define GLOBALSTATUS_H

#include <QObject>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "QQmlEngine"

class GlobalStatus : public QObject
{
    Q_OBJECT
public:
    static GlobalStatus *getInstance();

    // 阻止编译器隐式生成拷贝
    GlobalStatus(GlobalStatus const&) = delete;
    template<class... FuncArgs>
    void callQMLFunction(QString qmlObjectName, QString qmlFuncName, FuncArgs... funcArg)
    {
        QObject *myScreenObject = m_engine->rootObjects().first()->findChild<QObject*>(qmlObjectName);

        if (myScreenObject) {
            // 调用QML对象的方法
            QMetaObject::invokeMethod(myScreenObject, qmlFuncName.toUtf8(),
                                      Qt::DirectConnection,
                                      Q_ARG(QVariant, funcArg)...);
        } else {
            qWarning() << "Failed to find "<<qmlObjectName;
        }
    }
    void setEngine(QQmlApplicationEngine *engine){m_engine = engine;}
    QString getPwd(){return pwd;}
    QString cd();
private:
    explicit GlobalStatus(QObject *parent = nullptr);

signals:

private:
    static GlobalStatus* Instance;
    QQmlApplicationEngine *m_engine;
    QString pwd="/";
};

#endif // GLOBALSTATUS_H
