#ifndef NETWORKOPERATION_H
#define NETWORKOPERATION_H

#include <QObject>
#include <qnetworkaccessmanager.h>
#include "json.hpp"
#include "QTHread"

using json = nlohmann::json;

class NetWorkOperation : public QObject
{
    Q_OBJECT
public:
    NetWorkOperation();
    ~NetWorkOperation();

    /**
     * @brief get
     * @param url
     */
    Q_INVOKABLE void get(QUrl url);
private:
    void getFileInfo(QNetworkReply* reply);
signals:
    void signalRequestStart();
    void signalRequestEnd(QString getData,int statuCode,QString errorString);


private:
    QNetworkAccessManager* m_netWorkManager;
};

#endif // NETWORKOPERATION_H
