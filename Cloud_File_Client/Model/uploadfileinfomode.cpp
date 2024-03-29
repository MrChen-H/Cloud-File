﻿#include "uploadfileinfomode.h"


#include <qfileinfo.h>
#include <qhttpmultipart.h>
#include <qnetworkaccessmanager.h>
#include <qnetworkreply.h>
#include "./SERVER_CONFIG/SERVER_URLS.h"
#include <QtWidgets/qapplication.h>

UpLoadfileInfoMode* UpLoadfileInfoMode::Instance = new UpLoadfileInfoMode();

UpLoadfileInfoMode::~UpLoadfileInfoMode()
{

}

UpLoadfileInfoMode *UpLoadfileInfoMode::getInstance()
{
    return Instance;
}

int UpLoadfileInfoMode::rowCount(const QModelIndex &parent) const
{
    return this->upLoadInfoList.size();
}

QHash<int, QByteArray> UpLoadfileInfoMode::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[FileNameRole] = "fileName";
    roles[FileSuffixRole] = "fileSuffix";
    roles[FileAbsulotePathRole] = "fileAbsulotePath";
    roles[CountSizeRole] = "countSize";
    roles[InfoIndexRole] = "infoIndex";
    roles[UpLoadProessRole] = "upLoadProess";
    roles[UpLoadSpeedRole] = "upLoadSpeed";
    roles[AlreadyUploadRole] = "alreadyUpload";
    roles[IsStopRole] = "isStop";
    return roles;
}

QVariant UpLoadfileInfoMode::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row < 0 || row >= upLoadInfoList.count()) {
        return QVariant();
    }

    const UpLoadInfo &data = upLoadInfoList[row];
    switch (role) {
    case FileNameRole:
        return data.fileName;
    case FileSuffixRole:
        return data.fileSuffix;
    case FileAbsulotePathRole:
        return data.fileAbsulotePath;
    case CountSizeRole:
        return data.countSize;
    case InfoIndexRole:
        return data.infoIndex;
    case UpLoadProessRole:
        return data.upLoadProess;
    case UpLoadSpeedRole:
        return data.upLoadSpeed;
    case AlreadyUploadRole:
        return data.alreadyUpload;
    case IsStopRole:
        return data.isStop;
    default:
        return QVariant();
    }
}
/**
 * @author MrChen-H
 * @date 2024-03-02 21:04:07
 * @brief Add an upload task by absolute path
 * @param file_absolute_path need upload file's absolute path
 * @param
 * @return void
 */
void UpLoadfileInfoMode::appendByOne(QString file_absolute_path)
{
    beginInsertRows(QModelIndex(),upLoadInfoList.size(),upLoadInfoList.size());
    UpLoadInfo newInfo;
    QFileInfo newFileInfo(file_absolute_path);
    newInfo.fileAbsulotePath = file_absolute_path.remove(0,8);
    newInfo.fileName = newFileInfo.fileName(); ///2024-03-02 21:04:32 MrChen-H: get file name
    for(int i=newInfo.fileName.size()-1;i>0;i--) ///2024-03-02 21:04:43 MrChen-H: get file suffix
    {
        if(newInfo.fileName[i] == '.')
        {
            newInfo.fileSuffix = newInfo.fileName.right(newInfo.fileName.size()-i);
            break;
        }
    }
    newInfo.countSize = newFileInfo.size();
    if(upLoadInfoList.isEmpty())
    {
        newInfo.infoIndex = 0;
    }
    else
    {
        newInfo.infoIndex = upLoadInfoList.last().infoIndex+1;
    }


    upLoadInfoList.append(newInfo);
    endInsertRows();
    this->UploadOneFile(upLoadInfoList.last());
}
void UpLoadfileInfoMode::append(QList<QUrl> file_absolute_paths)
{
    for(auto& fileAbsolutePath:file_absolute_paths)
    {
        beginInsertRows(QModelIndex(),upLoadInfoList.size(),upLoadInfoList.size());
        UpLoadInfo newInfo;
        newInfo.fileAbsulotePath = fileAbsolutePath.toString().remove(0,8);
        QFileInfo newFileInfo(newInfo.fileAbsulotePath);
        newInfo.fileName = newFileInfo.fileName(); ///2024-03-02 21:04:32 MrChen-H: get file name
        newInfo.alreadyUpload = "0 Kb/ "+UpLoadInfo::byteToLogger(newFileInfo.size());
        for(int i=newInfo.fileName.size()-1;i>0;i--) ///2024-03-02 21:04:43 MrChen-H: get file suffix
        {
            if(newInfo.fileName[i] == '.')
            {
                newInfo.fileSuffix = newInfo.fileName.right(newInfo.fileName.size()-i);
                break;
            }
        }
        newInfo.countSize = newFileInfo.size();
        if(upLoadInfoList.isEmpty())
        {
            newInfo.infoIndex = 0;
        }
        else
        {
            newInfo.infoIndex = upLoadInfoList.last().infoIndex+1;
        }


        upLoadInfoList.append(newInfo);
        endInsertRows();
    }

}
void UpLoadfileInfoMode::remove(int index)
{
    emit this->upLoadInfoList[index].signalRemoveThisInfo();
    beginRemoveRows(QModelIndex(),index,index);
    this->upLoadInfoList.removeAt(index);
    endRemoveRows();

    for(int i=0;i<this->upLoadInfoList.size();i++)
    {
        upLoadInfoList[i].infoIndex = i;
    }
}

void UpLoadfileInfoMode::removeAll()
{
    beginResetModel();
    upLoadInfoList.clear();
    endResetModel();
}

void UpLoadfileInfoMode::startUploadAll()
{
    for(auto &uploadInfo : this->upLoadInfoList)
    {
        UploadOneFile(uploadInfo,1024*1024*60);
    }
}

void UpLoadfileInfoMode::UploadOneFile(UpLoadInfo &be_up_info,qint64 chunkSize, qint64 offset)
{
    be_up_info.oneSecondReadSize = 0;
    be_up_info.previousSecendUploadBytes = 0;

    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QHttpPart file_Part;
    QFile *file = new QFile(be_up_info.fileAbsulotePath);
    QFileInfo file_info(*file);
    file->open(QIODevice::ReadOnly);

    QNetworkAccessManager *Upload_manager = new QNetworkAccessManager(this);

    //    QByteArray bytes = file->readAll();//读取文件内容
    QString arg = QString("form-data;filename=\"%1\";file_size=\"%2\";")\
                      .arg(file_info.fileName().toUtf8())\
                      .arg(file_info.size());
    file_Part.setHeader(QNetworkRequest::ContentDispositionHeader,QVariant(arg));
    file_Part.setBodyDevice(file);//设置传输数据
    file->setParent(multiPart);//文件指针在multiPart析构时关闭文件同时析构
    multiPart->append(file_Part);

    QNetworkRequest request;
    request.setUrl(QUrl(REQUEST_UP_LOAD_FILE));//设置请求URL
    request.setHeader(QNetworkRequest::ContentTypeHeader, "multipart/form-data");
    QNetworkReply *reply = Upload_manager->post(request, multiPart);
    be_up_info.isStop = false;
    emit dataChanged(createIndex(be_up_info.infoIndex, 0), createIndex(be_up_info.infoIndex, 0));
    multiPart->setParent(reply);
    connect(&be_up_info,&UpLoadInfo::signalRemoveThisInfo,this,[=,&be_up_info]{
        be_up_info.processTimer.stop();
        reply->abort();
    });

    be_up_info.processTimer.start(1000);
    connect(&be_up_info.processTimer,&QTimer::timeout,this,[=,&be_up_info](){
        if(be_up_info.oneSecondReadSize!=0)
        {
            be_up_info.upLoadSpeed = UpLoadInfo::getSpeedString(be_up_info.oneSecondReadSize);
        }
        emit dataChanged(createIndex(be_up_info.infoIndex, 0), createIndex(be_up_info.infoIndex, 0));
        be_up_info.oneSecondReadSize = 0;
    });
    connect(reply, &QNetworkReply::uploadProgress,this,[=,&be_up_info](qint64 bytesRead, qint64 totalBytes){
        if(be_up_info.isStop == true)
        {
            be_up_info.processTimer.stop();
            reply->abort();
        }
        if(std::isnan(double(bytesRead)/double(totalBytes)) == true)
        {
            be_up_info.upLoadSpeed = "0 Kb/s";
            emit dataChanged(createIndex(be_up_info.infoIndex, 0), createIndex(be_up_info.infoIndex, 0));
            return;
        }
        be_up_info.upLoadProess = double(bytesRead)/double(totalBytes);
        if(bytesRead<0 || bytesRead - be_up_info.previousSecendUploadBytes < 0)
        {
            return;
        }

        be_up_info.oneSecondReadSize = be_up_info.oneSecondReadSize + bytesRead - be_up_info.previousSecendUploadBytes;
        be_up_info.previousSecendUploadBytes = bytesRead;
        be_up_info.alreadyUpload = UpLoadInfo::byteToLogger(bytesRead)+"/"+UpLoadInfo::byteToLogger(totalBytes);

        emit dataChanged(createIndex(be_up_info.infoIndex, 0), createIndex(be_up_info.infoIndex, 0));
    });

    connect(reply,&QNetworkReply::finished,[=]{//当服务器确定文件收到并在服务器创建资源时完成进度条并弹出提示框
        if(reply->error() != QNetworkReply::OperationCanceledError)
        {
            qDebug()<<reply->readAll();
        }
    });
}

void UpLoadfileInfoMode::startUpLoadByIndex(int index)
{
    for(auto& uploadInfo : this->upLoadInfoList)
    {
        if(uploadInfo.infoIndex == index)
        {
            this->UploadOneFile(uploadInfo);

            return;
        }
    }
}

void UpLoadfileInfoMode::jumpToTransportPage()
{
    emit signalJumpToTransportPage();
}

void UpLoadfileInfoMode::jumpToUploadStatusPage()
{
    emit signalJumpToUploadStatusPage();
}

void UpLoadfileInfoMode::stopUploadByIndex(int index)
{
    for(auto& uploadInfo : upLoadInfoList)
    {
        if(uploadInfo.infoIndex == index)
        {
            uploadInfo.isStop = true;
            emit dataChanged(createIndex(uploadInfo.infoIndex, 0), createIndex(uploadInfo.infoIndex, 0));
            break;
        }
    }
}

int UpLoadfileInfoMode::getExistingTaskSize()
{
    return this->upLoadInfoList.size();
}

void UpLoadfileInfoMode::pauseAllTask()
{
    for(auto& info : this->upLoadInfoList)
    {
        info.isStop = true;
        emit dataChanged(createIndex(info.infoIndex, 0), createIndex(info.infoIndex, 0));
    }
}



int UpLoadfileInfoMode::getNewInfoIndex()
{
    int maxIndex = 0;
    for(auto& info: this->upLoadInfoList)
    {
        if(info.infoIndex > maxIndex)
        {
            maxIndex = info.infoIndex;
        }
    }
    if(upLoadInfoList.size() != 0)
    {
        return maxIndex +1;
    }
    return maxIndex;
}

UpLoadfileInfoMode::UpLoadfileInfoMode(QObject *parent)
{

}

QString UpLoadInfo::getSpeedString(qint64 intSpeed)
{
    if(intSpeed<1024)
    {
        return QString("%1 byte/s").arg(intSpeed);
    }
    double kb_s = (double)intSpeed/1024.0;

    if(kb_s>1024)
    {
        double mb_s = (double)kb_s/1024.0;
        return QString("%1 Mb/s").arg(mb_s, 0, 'f', 1);
    }
    else
    {
        return QString("%1 Kb/s").arg(kb_s, 0, 'f', 1);
    }
}

QString UpLoadInfo::byteToLogger(qint64 byteSize)
{
    if(byteSize<1024)
    {
        return QString("%1 byte").arg(byteSize);
    }
    double kb_m = (double)byteSize/1024.0;
    if(kb_m > 1024)
    {
        double mb_m = (double)kb_m/1024.0;
        if(mb_m>1024)
        {
            double gb_m = (double)mb_m/1024.0;
            return QString("%1 Gb").arg(gb_m, 0, 'f', 1);
        }
        else
        {
            return QString("%1 Mb").arg(mb_m, 0, 'f', 1);
        }
    }
    else
    {
        return QString("%1 Kb").arg(kb_m, 0, 'f', 1);
    }
}

UpLoadInfo::UpLoadInfo(const UpLoadInfo &beCopy)
{
    this->fileName = beCopy.fileName;
    this->countSize =beCopy.countSize;
    this->fileSuffix =beCopy.fileSuffix;
    this->infoIndex =beCopy.infoIndex;
    this->fileAbsulotePath =beCopy.fileAbsulotePath;
    this->isStop =beCopy.isStop;

    this->upLoadProess =beCopy.upLoadProess;
    this->upLoadSize =beCopy.upLoadSize;
    this->upLoadSpeed =beCopy.upLoadSpeed;
    this->alreadyUpload =beCopy.alreadyUpload;
    this->previousSecendUploadBytes =beCopy.previousSecendUploadBytes;

}

UpLoadInfo::~UpLoadInfo()
{

}

UpLoadInfo &UpLoadInfo::operator=(const UpLoadInfo &beCopy)
{
    this->fileName = beCopy.fileName;
    this->countSize =beCopy.countSize;
    this->fileSuffix =beCopy.fileSuffix;
    this->infoIndex =beCopy.infoIndex;
    this->fileAbsulotePath =beCopy.fileAbsulotePath;
    this->isStop =beCopy.isStop;

    this->upLoadProess =beCopy.upLoadProess;
    this->upLoadSize =beCopy.upLoadSize;
    this->upLoadSpeed =beCopy.upLoadSpeed;
    this->alreadyUpload =beCopy.alreadyUpload;
    this->previousSecendUploadBytes =beCopy.previousSecendUploadBytes;
    return *this;
}
