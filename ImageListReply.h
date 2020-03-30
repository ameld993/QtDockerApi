#ifndef DOCKERIMAGELISTREPLY_H
#define DOCKERIMAGELISTREPLY_H

#include "DockerReply.h"
#include "Image.h"

#include <QVector>

namespace docker {

    class ImageListReply : public DockerReply
    {
        Q_OBJECT
        QVector<Image> m_images;
    public:
        ImageListReply(QNetworkReply *reply, QObject *parent = nullptr);

        bool hasImages() const;
        QVector<Image> images() const;

        // DockerReply interface
    private:
        void onReplyReceived();
    };

}

#endif // DOCKERIMAGELISTREPLY_H
