#ifndef DOWNLOADSTATEMODEL_H
#define DOWNLOADSTATEMODEL_H

#include <QObject>
#include "QAbstractListModel"

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
    Q_INVOKABLE static DownLoadStateModel *getInstance();
    DownLoadStateModel(DownLoadStateModel const&) = delete;

    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QHash<int,QByteArray> roleNames() const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

    void updateInfo(int index,DownLoadInfo& info);
    QList<DownLoadInfo> getInfoList(){return downLoadInfo;}
public:
    Q_INVOKABLE void append(const DownLoadInfo &info);
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
    DownLoadStateModel(QObject *parent = nullptr);
    static DownLoadStateModel* Instance;
    QList<DownLoadInfo> downLoadInfo;

signals:
};

#endif // DOWNLOADSTATEMODEL_H
