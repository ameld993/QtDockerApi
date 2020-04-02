#include "ContainerListReply.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#ifdef QT_DEBUG
#include <qdebug.h>
#endif


docker::ContainerListReply::ContainerListReply(QNetworkReply *reply, QObject *parent) : DockerReply(reply, parent)
{

}


bool docker::ContainerListReply::hasContainers() const
{
    return !m_containers.isEmpty();
}


QList<docker::Container> docker::ContainerListReply::containers() const
{
    return m_containers;
}


void docker::ContainerListReply::onReplyReceived()
{
    if (m_data.isEmpty()) {
        emit errorReceived("ContainerListReply - Empty data received!");
        return;
    }

    m_containers.clear();

    QJsonDocument doc = QJsonDocument::fromJson(m_data);
    QJsonArray array = doc.array();

    for (int i = 0; i < array.size(); i++) {
        if (!array.at(i).isObject()) {
#ifdef QT_DEBUG
            qDebug() << "ContainerListReply - why is this not an Objet?!!";
#endif
            continue;
        }

        QJsonObject obj = array.at(i).toObject();
        Container container(obj);
        m_containers << container;
    }
}
