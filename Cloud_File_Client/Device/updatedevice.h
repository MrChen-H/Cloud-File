#ifndef UPDATEDEVICE_H
#define UPDATEDEVICE_H

#include <QObject>

class UpdateDevice : public QObject
{
    Q_OBJECT
public:
    explicit UpdateDevice(QObject *parent = nullptr);

signals:

};

#endif // UPDATEDEVICE_H
