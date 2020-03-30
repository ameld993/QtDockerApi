#include "Engine.h"
#include "DockerReply.h"
#include "ImageListReply.h"
#include "DockerRequestGenerator.h"

#include <QNetworkReply>
#include <QAuthenticator>
#include <QByteArray>
#include <QNetworkAccessManager>

namespace docker {
    static Engine* _Static_Docker_Engine_ = nullptr;
}

docker::Engine::Engine(QObject *parent) : QObject(parent)
{
    m_networkManager = new QNetworkAccessManager(this);

    connect(m_networkManager, &QNetworkAccessManager::authenticationRequired, [=](QNetworkReply *repy, QAuthenticator *auth){
        Q_UNUSED(repy)
        Q_UNUSED(auth)
        qDebug() << "authenticationRequired!";
    });
}

docker::Engine *docker::Engine::instance()
{
    if (_Static_Docker_Engine_ == nullptr) {
        _Static_Docker_Engine_ = new Engine;
    }

    return _Static_Docker_Engine_;
}


docker::DockerReply* docker::Engine::getContainers(QUrlQuery query)
{

    return new DockerReply(executeGetReq(docker::getContainterList(query)));
}


docker::DockerReply *docker::Engine::createContainer(const QString &name, QByteArray bodyReq)
{
    QUrlQuery query;
    query.addQueryItem("name", name);

    return new DockerReply(executePosReq(docker::createContainer(query), bodyReq));
}


docker::ImageListReply* docker::Engine::getDockerImages(QUrlQuery query)
{
    return new ImageListReply(executeGetReq(docker::getImageList(query)));
}


QNetworkReply* docker::Engine::executeGetReq(const QNetworkRequest &req)
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


QNetworkReply *docker::Engine::executePosReq(const QNetworkRequest &req, QByteArray &posBody)
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


QNetworkReply *docker::Engine::execureDelReq(const QNetworkRequest &req)
{
    return m_networkManager->deleteResource(req);
}
