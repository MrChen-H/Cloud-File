#include "networkoperate.h"

#include <QEventLoop>
#include <QNetworkReply>
#include "QDebug"

NetWorkOperation::NetWorkOperation()
{
    this->m_netWorkManager = new QNetworkAccessManager;

    connect(this->m_netWorkManager,&QNetworkAccessManager::finished,this,[=](QNetworkReply * reply){
        qDebug()<<reply->readAll();
        emit signalRequestEnd(reply);
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
    request.setUrl(QUrl("http://111.229.83.106:80/Test"));
    request.setHeader(QNetworkRequest::UserAgentHeader,QVariant("text/plain;charset=utf-8"));
    m_netWorkManager->get(request);    //getÇëÇóÍ·
}
