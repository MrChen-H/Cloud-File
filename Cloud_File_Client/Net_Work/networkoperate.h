#ifndef NETWORKOPERATE_H
#define NETWORKOPERATE_H

#include <QObject>
#include <qnetworkaccessmanager.h>

class NetWorkOperate : public QObject
{
    Q_OBJECT
public:
    explicit NetWorkOperate(QObject *parent = nullptr);


signals:

private:
    QNetworkAccessManager qnam;
};

#endif // NETWORKOPERATE_H
