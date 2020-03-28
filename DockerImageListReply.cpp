#include "DockerImageListReply.h"
#include "DockerImage.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>

#include <iostream>

docker::DockerImageListReply::DockerImageListReply(QNetworkReply *reply, QObject *parent) : DockerReply(reply, parent)
{
}


bool docker::DockerImageListReply::hasImages() const
{
    return !m_images.isEmpty();
}


QVector<docker::DockerImage> docker::DockerImageListReply::images() const
{
    return m_images;
}


void docker::DockerImageListReply::onReplyReceived()
{
    if (m_data.isEmpty()) {
        emit errorReceived("DockerImageListReply - Empty data received!");
        return;
    }

    m_images.clear();

    QJsonDocument doc = QJsonDocument::fromJson(m_data);
    QJsonArray array = doc.array();

    for (int i = 0; i < array.size(); i++) {
        if (!array.at(i).isObject()) {
            qDebug() << "DockerImageListReply - why is this not an Objet?!!";
            continue;
        }

        QJsonObject obj = array.at(i).toObject();
        DockerImage image(obj);

        m_images.push_back(image);
    }
}
