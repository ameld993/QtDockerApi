#ifndef DOCKERIMAGELISTREPLY_H
#define DOCKERIMAGELISTREPLY_H

#include "DockerReply.h"
#include "DockerImage.h"

#include <QVector>

namespace docker {

    class DockerImageListReply : public DockerReply
    {
        Q_OBJECT
        QVector<DockerImage> m_images;
    public:
        DockerImageListReply(QNetworkReply *reply, QObject *parent = nullptr);

        bool hasImages() const;
        QVector<DockerImage> images() const;

        // DockerReply interface
    private:
        void onReplyReceived();
    };

}

#endif // DOCKERIMAGELISTREPLY_H
