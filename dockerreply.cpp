#include "dockerreply.h"

#include <QNetworkReply>
#include <QString>

dockerApi::DockerReply::DockerReply(QNetworkReply *reply, QObject *parent) : QObject(parent)
{
    if (reply == nullptr) {
        return;
    }

    reply->setParent(this);

    connect(reply, &QNetworkReply::readyRead, [=](){
        parseReceivedData(reply->readAll());
        reply->deleteLater();
    });

    connect(reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error), [=](QNetworkReply::NetworkError code){
        QString errorStrTmp = "DockerReply Code [%1] Description: %2";
        QString errorStr = errorStrTmp.arg(QString::number(code)).arg(reply->errorString());

        emit errorReceived(errorStr);
        reply->deleteLater();
    });
}


QString dockerApi::DockerReply::getErrorStr() const
{
    return m_errorString;
}


void dockerApi::DockerReply::parseReceivedData(const QByteArray &data)
{
    Q_UNUSED(data)
}

