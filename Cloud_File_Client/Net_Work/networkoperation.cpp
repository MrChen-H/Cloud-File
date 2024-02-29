#include "networkoperation.h"

#include <QEventLoop>
#include <QNetworkReply>
#include "QDebug"

NetWorkOperation::NetWorkOperation()
{
    this->m_netWorkManager = new QNetworkAccessManager;

    connect(this->m_netWorkManager,&QNetworkAccessManager::finished,this,[=](QNetworkReply * reply){
        qDebug()<<QString(reply->readAll()).toUtf8();
        if(reply->error() == QNetworkReply::NoError)
        {
            emit signalRequestEnd(reply->readAll(),reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(),reply->errorString());
        }
        else
        {
            emit signalRequestEnd(reply->readAll(),reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(),"网络异常");
        }

    });
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
    QNetworkRequest request;
    request.setUrl(url);
    request.setHeader(QNetworkRequest::UserAgentHeader,QVariant("application/json;charset=utf-8"));
    m_netWorkManager->get(request);    //get request header
}
