#include "ImageListReply.h"
#include "Image.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>

#include <iostream>

docker::ImageListReply::ImageListReply(QNetworkReply *reply, QObject *parent) : DockerReply(reply, parent)
{
}


bool docker::ImageListReply::hasImages() const
{
    return !m_images.isEmpty();
}


QVector<docker::Image> docker::ImageListReply::images() const
{
    return m_images;
}


void docker::ImageListReply::onReplyReceived()
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
        Image image(obj);

        m_images.push_back(image);
    }
}
