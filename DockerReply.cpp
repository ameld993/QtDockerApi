#include "DockerReply.h"

#include <QNetworkReply>
#include <QString>

docker::DockerReply::DockerReply(QNetworkReply *reply, QObject *parent) : QObject(parent)
{
    if (reply == nullptr) {
        return;
    }

    reply->setParent(this);

    connect(reply, &QNetworkReply::readyRead, [=](){
        m_data = reply->readAll();
        m_errorString.clear();
        m_statusCode = reply->error();
        onReplyReceived();
        emit replyReceived();
        reply->deleteLater();
    });

    connect(reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error), [=](QNetworkReply::NetworkError code){
        QString errorStrTmp = "DockerReply Code [%1] Description: %2";
        QString errorStr = errorStrTmp.arg(QString::number(code)).arg(reply->errorString());

        m_errorString = errorStr;
        m_statusCode = code;

        emit errorReceived(errorStr);
        reply->deleteLater();
    });
}


QString docker::DockerReply::getErrorStr() const
{
    return m_errorString;
}


int docker::DockerReply::getStatusCode() const
{
    return m_statusCode;
}


QByteArray docker::DockerReply::data() const
{
    return m_data;
}


void docker::DockerReply::onReplyReceived()
{

}



