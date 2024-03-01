#include "networkoperation.h"

#include <QEventLoop>
#include <QNetworkReply>
#include "QDebug"
#include "iostream"
#include "QJsonDocument"
#include "./Model/allfilemodel.h"

NetWorkOperation::NetWorkOperation()
{
    this->m_netWorkManager = new QNetworkAccessManager;


}

NetWorkOperation::~NetWorkOperation()
{

    if(m_netWorkManager != nullptr)
    {
        delete m_netWorkManager;
        m_netWorkManager = nullptr;
    }
}

void NetWorkOperation::get(QUrl url)
{
    emit signalRequestStart();
    AllFileModel::getInstance()->removeAll();
    QNetworkRequest request;
    request.setUrl(url);
    request.setHeader(QNetworkRequest::UserAgentHeader,QVariant("application/json;charset=utf-8"));
    m_netWorkManager->get(request);    //get request header
    connect(this->m_netWorkManager,&QNetworkAccessManager::finished,this,&NetWorkOperation::getFileInfo);
}

void NetWorkOperation::getFileInfo(QNetworkReply *reply)
{

    if(reply->error() == QNetworkReply::NoError)
    {
        QString  getInfo = reply->readAll();
        emit signalRequestEnd(getInfo,reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(),reply->errorString());
        json fileInfoJson = json::parse(getInfo.toStdString());
        for (auto& entry : fileInfoJson.items())
        {
            // 遍历 JSON 对象中的每个键值对
            std::string id = entry.key();  // 获取当前键，即 "6"、"7"、"8"
            json fileData = entry.value(); // 获取对应的值，即每个文件对象
            // 现在我们可以遍历文件对象的属性
            FileInfo info;
            info.fileName = QString::fromStdString(fileData["file_name"]);
            info.fileSize = QString::fromStdString(fileData["file_size"]).toInt();
            info.fileType = QString::fromStdString(fileData["type_name"]);
            info.fileUrl = QString::fromStdString(fileData["file_dir"]);
            info.id = QString::fromStdString(id);
            AllFileModel::getInstance()->append(info);
            // 如果需要进一步处理或存储这些信息，可以在上述提取后添加相应逻辑
        }
    }
    else
    {
        emit signalRequestEnd(reply->readAll(),reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(),"网络异常");
    }
}
