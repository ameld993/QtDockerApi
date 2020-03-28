#include "DockerImage.h"

#include <QJsonObject>
#include <QJsonArray>


docker::DockerImage::DockerImage()
{

}


docker::DockerImage::DockerImage(const QJsonObject &imageObject)
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
        m_created = imageObject["Created"].toString().toULong();
    }

    if (imageObject.contains("Size")) {
        m_size = imageObject["Size"].toString().toULong();
    }

    if (imageObject.contains("RepoTags")) {
        QJsonArray tags = imageObject["RepoTags"].toArray();

        for (int r = 0; r < tags.size(); r++) {
            m_repoTags << tags.at(r).toString();
        }
    }
}

QString docker::DockerImage::id() const
{
    return m_id;
}

QString docker::DockerImage::parentId() const
{
    return m_parentId;
}

QStringList docker::DockerImage::repoTags() const
{
    return m_repoTags;
}

ulong docker::DockerImage::created() const
{
    return m_created;
}

ulong docker::DockerImage::size() const
{
    return m_size;
}

ulong docker::DockerImage::virtualSize() const
{
    return m_virtualSize;
}

int docker::DockerImage::containers() const
{
    return m_containers;
}

bool docker::DockerImage::operator ==(const docker::DockerImage &dockerImage) const
{
    return m_id.compare(dockerImage.m_id) == 0;
}

QString docker::DockerImage::toString() const
{
    QStringList strl;

    strl << "Id: " + m_id;
    strl << "Size: " + QString::number(m_size);
    strl << "ParentId: " + m_parentId;
    strl << "Created: " + QString::number(m_created);
    strl << "RepoTags: " + m_repoTags.join(", ");

    return strl.join("\n").append("\n");
}


