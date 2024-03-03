#ifndef UPLOADFILEINFOMODE_H
#define UPLOADFILEINFOMODE_H

#include <QAbstractListModel>
#include <QObject>
#include <QUrl>
#include "QTimer"

class UpLoadInfo
{
public:
    static QString getSpeedString(qint64 intSpeed);
    static QString byteToLagger(qint64 btyeSize);
public:
    QString fileName;
    int countSize;
    QString fileSuffix;
    int infoIndex;
    QString fileAbsulotePath;

    ///2024-03-02 21:07:14 MrChen-H: These three members have default values at the time of creation
    float upLoadProess=0.0;
    int upLoadSize=0;
    QString upLoadSpeed="0 kb/s";
    QString alreadyUpload = "0 Kb/ 0 Kb";
    qint64 previousSecendUploadBytes=0;
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
    Q_INVOKABLE void appendByOne(QString file_absolute_path);
    Q_INVOKABLE void append(QList<QUrl> file_absolute_paths);
    Q_INVOKABLE void remove(int index);
    Q_INVOKABLE void removeAll();
    Q_INVOKABLE void startUploadAll();
    Q_INVOKABLE void UploadOneFile(UpLoadInfo &be_up_info,qint64 chunkSize = 1024 * 1024 * 60,qint64 offset = 0);
    Q_INVOKABLE void startUpLoadByIndex(int index);
    Q_INVOKABLE void jumpToTransportPage();
    Q_INVOKABLE void jumpToUploadStatusPage();

private:


    enum DataRoles{
        FileNameRole = Qt::UserRole + 50,
        FileSuffixRole,
        CountSizeRole,
        FileAbsulotePathRole,
        InfoIndexRole,
        UpLoadProessRole,
        UpLoadSpeedRole,
        AlreadyUploadRole
    };

    enum UP_LOAD_ERROR_TYPE
    {
        UP_ERROR_OPEN_FILE_FAILED,
        UP_ERROR_NET_WORK_ERROR
    };

    int getNewInfoIndex();
signals:
    void signalUpLoadFailed(UP_LOAD_ERROR_TYPE errorType,int Http_Code = 404,QString errorInfo="UnKnow Error");
    void signalJumpToTransportPage();
    void signalJumpToUploadStatusPage();
private:
    UpLoadfileInfoMode(QObject *parent = nullptr);
    static UpLoadfileInfoMode* Instance;
    QList<UpLoadInfo> upLoadInfoList;
};

#endif // UPLOADFILEINFOMODE_H
