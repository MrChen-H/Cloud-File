#ifndef DOWNLOADTHREAD_H
#define DOWNLOADTHREAD_H

#include <QObject>

class DownLoadThread : public QObject
{
    Q_OBJECT
public:
    explicit DownLoadThread(QObject *parent = nullptr);

signals:

};

#endif // DOWNLOADTHREAD_H
