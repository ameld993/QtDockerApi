#ifndef CONTAINERLISTREPLY_H
#define CONTAINERLISTREPLY_H

#include "DockerReply.h"
#include "Container.h"

namespace docker {

    class ContainerListReply : public DockerReply {
        Q_OBJECT
        QList<Container> m_containers;

    public:
        explicit ContainerListReply(QNetworkReply *reply, QObject *parent = nullptr);

        bool hasContainers() const;
        QList<Container> containers() const;

        // DockerReply interface
    private:
        void onReplyReceived();

    };
}

#endif // CONTAINERLISTREPLY_H
