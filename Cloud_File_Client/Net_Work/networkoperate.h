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
     * @param url �����URL
     * @param result ���ص�json��ʽ��Ϣ
     * @param errorInfo ������Ϣ
     * @return ״̬��
     */
    Q_INVOKABLE void get(QUrl url);
signals:
    void signalRequestStart();
    void signalRequestEnd();
private:
    QNetworkAccessManager* m_netWorkManager;
};

#endif // NETWORKOPERATE_H
