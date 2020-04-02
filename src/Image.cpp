#include "Image.h"

#include <QJsonObject>
#include <QJsonArray>


docker::Image::Image()
{

}


docker::Image::Image(const QJsonObject &imageObject)
{
    m_containers = imageObject["Containers"].toInt(0);
    m_id = imageObject["Id"].toString("");
    m_parentId = imageObject["ParentId"].toString("");
    m_created = imageObject["Created"].toString("0").toULongLong();
    m_size = imageObject["Size"].toString("0").toULongLong();
    m_virtualSize = imageObject["VirtualSize"].toString("0").toULongLong();

    QJsonArray tags = imageObject["RepoTags"].toArray(QJsonArray());

    for (int r = 0; r < tags.size(); r++) {
        m_repoTags << tags.at(r).toString("");
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


