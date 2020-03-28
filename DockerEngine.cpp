#include "DockerEngine.h"
#include "DockerReply.h"
#include "DockerImageListReply.h"
#include "DockerRequestGenerator.h"

#include <QNetworkReply>
#include <QAuthenticator>
#include <QByteArray>
#include <QNetworkAccessManager>

namespace docker {
    static DockerEngine* _Static_Docker_Engine_ = nullptr;
}

docker::DockerEngine::DockerEngine(QObject *parent) : QObject(parent)
{
    m_networkManager = new QNetworkAccessManager(this);

    connect(m_networkManager, &QNetworkAccessManager::authenticationRequired, [=](QNetworkReply *repy, QAuthenticator *auth){
        Q_UNUSED(repy)
        Q_UNUSED(auth)
        qDebug() << "authenticationRequired!";
    });
}

docker::DockerEngine *docker::DockerEngine::instance()
{
    if (_Static_Docker_Engine_ == nullptr) {
        _Static_Docker_Engine_ = new DockerEngine;
    }

    return _Static_Docker_Engine_;
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
