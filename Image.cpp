#include "Image.h"

#include <QJsonObject>
#include <QJsonArray>


docker::Image::Image()
{

}


docker::Image::Image(const QJsonObject &imageObject)
{
    if (imageObject.contains("Containers")) {
        m_containers = imageObject["Containers"].toInt();
    }

    if (imageObject.contains("Id")) {
        m_id = imageObject["Id"].toString();
    }

    if (imageObject.contains("ParentId")) {
        m_parentId = imageObject["ParentId"].toString();
    }

    if (imageObject.contains("Created")) {
        m_created = imageObject["Created"].toString().toULongLong();
    }

    if (imageObject.contains("Size")) {
        m_size = imageObject["Size"].toString().toULongLong();
    }

    if (imageObject.contains("VirtualSize")) {
        m_virtualSize = imageObject["VirtualSize"].toString().toULongLong();
    }

    if (imageObject.contains("RepoTags")) {
        QJsonArray tags = imageObject["RepoTags"].toArray();

        for (int r = 0; r < tags.size(); r++) {
            m_repoTags << tags.at(r).toString();
        }
    }
}

QString docker::Image::id() const
{
    return m_id;
}

QString docker::Image::parentId() const
{
    return m_parentId;
}

QStringList docker::Image::repoTags() const
{
    return m_repoTags;
}

qulonglong docker::Image::created() const
{
    return m_created;
}

qulonglong docker::Image::size() const
{
    return m_size;
}

qulonglong docker::Image::virtualSize() const
{
    return m_virtualSize;
}

int docker::Image::containers() const
{
    return m_containers;
}

bool docker::Image::operator ==(const docker::Image &dockerImage) const
{
    return m_id.compare(dockerImage.m_id) == 0;
}

QString docker::Image::toString() const
{
    QStringList strl;

    strl << "Id: " + m_id;
    strl << "Size: " + QString::number(m_size);
    strl << "ParentId: " + m_parentId;
    strl << "Created: " + QString::number(m_created);
    strl << "RepoTags: " + m_repoTags.join(", ");

    return strl.join("\n").append("\n");
}


