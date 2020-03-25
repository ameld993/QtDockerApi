#include "DockerEngine.h"
#include "DockerReply.h"
#include "DockerRequestGenerator.h"

#include "DockerImageListReply.h"

#include <QNetworkReply>
#include <QAuthenticator>

static docker::DockerEngine *static_docker_engine_ = nullptr;

docker::DockerEngine::DockerEngine(QObject *parent) : QObject(parent)
{
    m_networkManager = new QNetworkAccessManager(this);

    connect(m_networkManager, &QNetworkAccessManager::authenticationRequired, [=](QNetworkReply *repy, QAuthenticator *auth){
        qDebug() << "authenticationRequired!";
    });
}

docker::DockerEngine *docker::DockerEngine::instance()
{
    if (static_docker_engine_ == nullptr) {
        static_docker_engine_ = new DockerEngine;
    }

    return static_docker_engine_;
}


docker::DockerReply* docker::DockerEngine::getContainers(QUrlQuery query)
{

    return new DockerReply(executeGetReq(docker::getContainterList(query)));
}


docker::DockerReply *docker::DockerEngine::createContainer(const QString &name, QByteArray bodyReq)
{
    QUrlQuery query;
    query.addQueryItem("name", name);

    return new DockerReply(executePosReq(docker::createContainer(query), bodyReq));
}


docker::DockerImageListReply* docker::DockerEngine::getDockerImages(QUrlQuery query)
{
    return new DockerImageListReply(executeGetReq(docker::getImageList(query)));
}


QNetworkReply* docker::DockerEngine::executeGetReq(const QNetworkRequest &req)
{
    if (m_networkManager == nullptr) {
        qDebug() << "[ERROR] - DockerEngine::executeGetReq NetworkAccessManager is NULL \n Initializing new NetowrkAccessManager";
        m_networkManager = new QNetworkAccessManager(this);
        if (m_networkManager == nullptr) {
            qDebug() << "[ERROR] - DockerEngine::executeGetReq can't initialize new NetworkAccessManager";
            return nullptr;
        }
    }

    return m_networkManager->get(req);
}


QNetworkReply *docker::DockerEngine::executePosReq(const QNetworkRequest &req, QByteArray &posBody)
{
    if (m_networkManager == nullptr) {
        qDebug() << "[ERROR] - DockerEngine::executePosReq NetworkAccessManager is NULL \n Initializing new NetowrkAccessManager";
        m_networkManager = new QNetworkAccessManager(this);
        if (m_networkManager == nullptr) {
            qDebug() << "[ERROR] - DockerEngine::executePosReq can't initialize new NetworkAccessManager";
            return nullptr;
        }
    }

    return m_networkManager->put(req, posBody);
}


QNetworkReply *docker::DockerEngine::execureDelReq(const QNetworkRequest &req)
{
    return m_networkManager->deleteResource(req);
}
