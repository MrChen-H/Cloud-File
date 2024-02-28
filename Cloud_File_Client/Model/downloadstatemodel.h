#ifndef DOWNLOADSTATEMODEL_H
#define DOWNLOADSTATEMODEL_H

#include <QObject>
#include "QAbstractListModel"
#include "mutex"

struct DownLoadInfo
{
    QString fileName;
    int downLoadSize;
    int countSize;
    int downLoadSpeed;
    QString fileType;
    int infoIndex;
};
class DownLoadStateModel : public QAbstractListModel
{
    Q_OBJECT
public:
    ~DownLoadStateModel();
    static DownLoadStateModel *getInstance();
    DownLoadStateModel(DownLoadStateModel const&) = delete;

    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QHash<int,QByteArray> roleNames() const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

    void updateInfo(int index,DownLoadInfo& info);
public:
    Q_INVOKABLE void append(DownLoadInfo& info);
    Q_INVOKABLE void remove(int index);

private:
    enum DataRoles{
        FileNameRole = Qt::UserRole + 1,
        DownLoadSizeRole,
        CountSizeRole,
        DownLoadSpeedRole,
        InfoIndexRole
    };

private:
    DownLoadStateModel(QObject *parent = nullptr);
    static DownLoadStateModel* Instance;
    static std::mutex *threadLock;
    QList<DownLoadInfo> downLoadInfo;

signals:

};

#endif // DOWNLOADSTATEMODEL_H
