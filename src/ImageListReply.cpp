#include "ImageListReply.h"
#include "Image.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#ifdef QT_DEBUG
#include <QDebug>
#endif

docker::ImageListReply::ImageListReply(QNetworkReply *reply, QObject *parent) : DockerReply(reply, parent)
{
}


bool docker::ImageListReply::hasImages() const
{
    return !m_images.isEmpty();
}


QList<docker::Image> docker::ImageListReply::images() const
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
#ifdef QT_DEBUG
            qDebug() << "DockerImageListReply - why is this not an Objet?!!";
#endif
            continue;
        }

        QJsonObject obj = array.at(i).toObject();
        Image image(obj);

        m_images << image;
    }
}
