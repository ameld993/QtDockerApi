#include "dockerapi.h"
#include "dockerreply.h"
#include "dockerrequestgenerator.h"


#include <QNetworkReply>

dockerApi::DockerApi::DockerApi(QObject *parent) : QObject(parent)
{
    m_networkManager = new QNetworkAccessManager(this);
}


dockerApi::DockerReply* dockerApi::DockerApi::getContainerImages(QUrlQuery query)
{

    return executeGetReq(dockerApi::getContainterList(query));
}


dockerApi::DockerReply *dockerApi::DockerApi::createContainer(const QString &name, QByteArray bodyReq)
{
    QUrlQuery query;
    query.addQueryItem("name", name);

//    return executeGetReq(dockerApi::)
    Q_UNUSED(bodyReq)
    return nullptr;
}


dockerApi::DockerReply* dockerApi::DockerApi::getDockerImages(QUrlQuery query)
{
    return executeGetReq(dockerApi::getImageList(query));
}


dockerApi::DockerReply* dockerApi::DockerApi::executeGetReq(const QNetworkRequest &req)
{
    if (m_networkManager == nullptr) {
        qDebug() << "[ERROR] - DockerApi::executeGetReq NetworkAccessManager is NULL \n Initializing new NetowrkAccessManager";
        m_networkManager = new QNetworkAccessManager(this);
        if (m_networkManager == nullptr) {
            qDebug() << "[ERROR] - DockerApi::executeGetReq can't initialize new NetworkAccessManager";
            return nullptr;
        }
    }

    QNetworkReply *reply = m_networkManager->get(req);
    return new DockerReply(reply);
}


dockerApi::DockerReply *dockerApi::DockerApi::executePosReq(const QNetworkRequest &req, QByteArray &posBody)
{
    if (m_networkManager == nullptr) {
        qDebug() << "[ERROR] - DockerApi::executePosReq NetworkAccessManager is NULL \n Initializing new NetowrkAccessManager";
        m_networkManager = new QNetworkAccessManager(this);
        if (m_networkManager == nullptr) {
            qDebug() << "[ERROR] - DockerApi::executePosReq can't initialize new NetworkAccessManager";
            return nullptr;
        }
    }

    QNetworkReply *reply = m_networkManager->put(req, posBody);
    return new DockerReply(reply);
}


dockerApi::DockerReply *dockerApi::DockerApi::execureDelReq(const QNetworkRequest &req)
{
    QNetworkReply *reply = m_networkManager->deleteResource(req);
    return new DockerReply(reply);
}
