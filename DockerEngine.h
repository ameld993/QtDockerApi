#ifndef DOCKEENGINE_H
#define DOCKEENGINE_H

#include "DockerReply.h"

#include <QByteArray>
#include <QNetworkAccessManager>
#include <QUrlQuery>
#include <QObject>

namespace docker {

    class DockerImageListReply;

    class DockerEngine : public QObject
    {
        Q_OBJECT
        QNetworkAccessManager *m_networkManager;

    public:
        static DockerEngine* instance();

        /**
         * @brief getContainerImages - https://docs.docker.com/engine/api/v1.40/#operation/ContainerList
         * @param query: ["all" - boolean, "limit" -  integer , "size" - boolean, "filters" - string]
         * @return DockerReply
         */
        DockerReply *getContainers(QUrlQuery query = QUrlQuery());

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
        DockerImageListReply* getDockerImages(QUrlQuery query = QUrlQuery());

    signals:

    public slots:


    private:
        explicit DockerEngine(QObject *parent = nullptr);

        QNetworkReply *executeGetReq(const QNetworkRequest &req);
        QNetworkReply *executePosReq(const QNetworkRequest &req, QByteArray &posBody);
        QNetworkReply *execureDelReq(const QNetworkRequest &req);
    };

}
#endif // DOCKEENGINE_H
