#ifndef DOCKERIMAGELISTREPLY_H
#define DOCKERIMAGELISTREPLY_H

#include "DockerReply.h"

#include <QVector>


namespace docker {

    typedef struct _Docker_Image_{
        QString m_id;
        QString m_parentId;
        QStringList m_repoTags;
        ulong m_created;
        ulong m_size;
        ulong m_virtualSize;
        int m_containers;
    } DockerImage;


    class DockerImageListReply : public DockerReply
    {
        Q_OBJECT
        QVector<DockerImage> m_images;
    public:
        DockerImageListReply(QNetworkReply *reply, QObject *parent = nullptr);

        QVector<DockerImage> getImages() const;

        // DockerReply interface
    private:
        void onReplyReceived();
    };

}

#endif // DOCKERIMAGELISTREPLY_H
