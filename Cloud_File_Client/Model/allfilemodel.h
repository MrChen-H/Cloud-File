#ifndef ALLFILEMODEL_H
#define ALLFILEMODEL_H

#include <QObject>
#include "QAbstractListModel"
#include "mutex"

struct FileInfo
{
    int fileSize;
    QString fileUrl;
    QString fileType;
    QString fileName;
    int index;
};

class AllFileModel : public QAbstractListModel
{
    Q_OBJECT
private:
    explicit AllFileModel(QObject *parent = nullptr);
private:
    enum DataRoles{
        FileNameRole = Qt::UserRole + 10,
        FileUrlRole,
        FileSizeRole,
        InfoIndexRole,
        FileTypeRole
    };
public:
    ~AllFileModel();
    Q_INVOKABLE static AllFileModel *getInstance();
    AllFileModel(AllFileModel const&) = delete;

    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QHash<int,QByteArray> roleNames() const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

    void updateInfo(int index,FileInfo& info);
public:
    Q_INVOKABLE void append(FileInfo& info);
    Q_INVOKABLE void remove(int index);
    Q_INVOKABLE void removeAll();

    Q_INVOKABLE void test(){qDebug()<<"Test";}
private:
    static AllFileModel* Instance;
    static std::mutex* thread_lock;
    QList<FileInfo> file_list;
};

#endif // ALLFILEMODEL_H
