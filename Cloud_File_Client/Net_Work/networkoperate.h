#ifndef NETWORKOPERATE_H
#define NETWORKOPERATE_H

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
     * @param url 请求的URL
     * @param result 返回的json格式消息
     * @param errorInfo 错误信息
     * @return 状态码
     */
    Q_INVOKABLE void get(QUrl url);
signals:
    void signalRequestStart();
    void signalRequestEnd();
private:
    QNetworkAccessManager* m_netWorkManager;
};

#endif // NETWORKOPERATE_H
