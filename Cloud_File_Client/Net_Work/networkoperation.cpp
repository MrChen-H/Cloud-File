#include "networkoperation.h"

#include <QEventLoop>
#include <QFile>
#include <QFileInfo>
#include <QHttpPart>
#include <QNetworkReply>
#include "QDebug"
#include "QJsonDocument"
#include "./Model/allfilemodel.h"
#include "./Model/downloadstatemodel.h"

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

void NetWorkOperation::upLoadFile(QString filePathArray)
{

    filePathArray.remove(0,8);
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QHttpPart file_Part;
    QFile *file = new QFile(filePathArray);
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
    request.setUrl(QUrl("http://111.229.83.106/UploadFile"));//设置请求URL
    request.setHeader(QNetworkRequest::ContentTypeHeader, "multipart/form-data");
    DownLoadInfo info;
    info.fileName = file_info.fileName().toUtf8();
    info.downLoadSize = 0;
    info.fileType = "text";
    info.downLoadSpeed = 0;
    info.countSize = file_info.size();

    DownLoadStateModel::getInstance()->append(info);

    QNetworkReply *reply = Upload_manager->post(request, multiPart);
    multiPart->setParent(reply);
    connect(reply, &QNetworkReply::uploadProgress, [=](qint64 bytesRead, qint64 totalBytes){
        auto& info = DownLoadStateModel::getInstance()->getInfoList().first();

    });
    connect(reply,&QNetworkReply::finished,[=]{//当服务器确定文件收到并在服务器创建资源时完成进度条并弹出提示框
        auto get_server_message = reply->readAll();

    });
}

void NetWorkOperation::getFileInfo(QNetworkReply *reply)
{

    if(reply->error() == QNetworkReply::NoError)
    {
        QString  getInfo = reply->readAll();
        emit signalRequestEnd(getInfo,reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(),reply->errorString());
        json fileInfoJson;
        try {
            fileInfoJson = json::parse(getInfo.toStdString());
        } catch (const nlohmann::json::exception& e) {
            // 未能成功解析，可能是格式错误或其他问题
            return;
        }
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
