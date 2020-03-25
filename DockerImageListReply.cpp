#include "DockerImageListReply.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>

docker::DockerImageListReply::DockerImageListReply(QNetworkReply *reply, QObject *parent) : DockerReply(reply, parent)
{
}


QVector<docker::DockerImage> docker::DockerImageListReply::getImages() const
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
            continue;
        }

        QJsonObject obj = array.at(i).toObject();
        qDebug() << obj;

        DockerImage image;
        image.m_containers = obj["Containers"].toInt();
        image.m_id = obj["Id"].toString();
        image.m_parentId = obj["ParentId"].toString();
        image.m_created = obj["Created"].toString().toULong();
        image.m_size = obj["Size"].toString().toULong();

        QJsonArray repoTags = obj["RepoTags"].toArray();

        for (int r = 0; r < repoTags.size(); r++) {
            image.m_repoTags.push_back(repoTags.at(r).toString());
        }

        m_images.push_back(image);
    }
}


/*
{
"Id": "sha256:e216a057b1cb1efc11f8a268f37ef62083e70b1b38323ba252e25ac88904a7e8",
"ParentId": "",
"RepoTags": [],
"RepoDigests": [],
"Created": 1474925151,
"Size": 103579269,
"VirtualSize": 103579269,
"SharedSize": 0,
"Labels": { },
"Containers": 2
},
*/
