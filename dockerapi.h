#ifndef DOCKERAPI_H
#define DOCKERAPI_H

#include <QByteArray>
#include <QNetworkAccessManager>
#include <QUrlQuery>
#include <QObject>

namespace dockerApi {

class DockerReply;

class DockerApi : public QObject
{
    Q_OBJECT
    QNetworkAccessManager *m_networkManager;

public:
    explicit DockerApi(QObject *parent = nullptr);

    /**
     * @brief getContainerImages - https://docs.docker.com/engine/api/v1.40/#operation/ContainerList
     * @param query: ["all" - boolean, "limit" -  integer , "size" - boolean, "filters" - string]
     * @return DockerReply
     */
    DockerReply *getContainerImages(QUrlQuery query = QUrlQuery());

    /**
     * @brief createContainer - https://docs.docker.com/engine/api/v1.40/#operation/ContainerCreate
     * @param name - Assign the specified name to the container. Must match /?[a-zA-Z0-9][a-zA-Z0-9_.-]+
     * @param bodyReq
     * @return
     */
    DockerReply *createContainer(const QString &name, QByteArray bodyReq = QByteArray());

    /**
     * @brief getDockerImages
     * @return
     */
    DockerReply* getDockerImages(QUrlQuery query = QUrlQuery());

signals:

public slots:


private:
    DockerReply *executeGetReq(const QNetworkRequest &req);
    DockerReply *executePosReq(const QNetworkRequest &req, QByteArray &posBody);
    DockerReply *execureDelReq(const QNetworkRequest &req);
};

}
#endif // DOCKERAPI_H
