#ifndef DOCKEENGINE_H
#define DOCKEENGINE_H

#include <QObject>
#include <QUrlQuery>

class QNetworkReply;
class QNetworkRequest;
class QNetworkAccessManager;

namespace docker {

    class ImageListReply;
    class DockerReply;

    /**
     * @brief The DockerEngine class is a singelton
     */
    class Engine : public QObject
    {
        Q_OBJECT
        QNetworkAccessManager *m_networkManager {nullptr};

    public:
        static Engine* instance();

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
        ImageListReply* getDockerImages(QUrlQuery query = QUrlQuery());

        /**
         * @brief executeGetReq
         * @param req
         * @return
         */
        QNetworkReply *executeGetReq(const QNetworkRequest &req);

        /**
         * @brief executePosReq
         * @param req
         * @param posBody
         * @return
         */
        QNetworkReply *executePosReq(const QNetworkRequest &req, QByteArray &posBody);
        QNetworkReply *execureDelReq(const QNetworkRequest &req);

    private:
        explicit Engine(QObject *parent = nullptr);

    };

}
#endif // DOCKEENGINE_H
