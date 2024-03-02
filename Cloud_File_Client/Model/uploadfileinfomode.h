#ifndef UPLOADFILEINFOMODE_H
#define UPLOADFILEINFOMODE_H

#include <QAbstractListModel>
#include <QObject>

struct UpLoadInfo
{
    QString fileName;
    int downLoadSize;
    int countSize;
    int downLoadSpeed;
    QString fileType;
    int infoIndex;
};
class UpLoadfileInfoMode : public QAbstractListModel
{
    Q_OBJECT
public:
    ~UpLoadfileInfoMode();
    static UpLoadfileInfoMode *getInstance();
    UpLoadfileInfoMode(UpLoadfileInfoMode const&) = delete;

    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QHash<int,QByteArray> roleNames() const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

    QList<UpLoadInfo> getInfoList(){return upLoadInfoList;}
public:
    Q_INVOKABLE void append(const UpLoadInfo &info);
    Q_INVOKABLE void remove(int index);
    Q_INVOKABLE void removeAll();

private:
    enum DataRoles{
        FileNameRole = Qt::UserRole + 1,
        DownLoadSizeRole,
        CountSizeRole,
        DownLoadSpeedRole,
        InfoIndexRole,
        FileTypeRole
    };

private:
    UpLoadfileInfoMode(QObject *parent = nullptr);
    static UpLoadfileInfoMode* Instance;
    QList<UpLoadInfo> upLoadInfoList;

signals:
};

#endif // UPLOADFILEINFOMODE_H
