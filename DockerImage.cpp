#include "DockerImage.h"

docker::DockerImage::DockerImage(QObject *parent) : QObject(parent)
{

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

bool docker::DockerImage::operator ==(const docker::DockerImage &dockerImage)
{
    return m_id.compare(dockerImage.m_id) == 0;
}

void docker::DockerImage::setId(const QString &id)
{
    if (m_id == id) {
        return;
    }
    
    m_id = id;
    emit idChanged();
}

void docker::DockerImage::setParentId(const QString &parentId)
{
    if (m_parentId == parentId) {
        return;
    }
    
    m_parentId = parentId;
    emit parentIdChanged();
}

void docker::DockerImage::setRepoTags(const QStringList &repoTags)
{
    m_repoTags = repoTags;
    emit repoTagsChanged();
}
