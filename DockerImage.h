#ifndef DOCKERIMAGE_H
#define DOCKERIMAGE_H

#include <QString>
#include <QStringList>

class QJsonObject;

namespace docker {
        
    class DockerImage
    {
        QString m_id {"none"};
        QString m_parentId {"none"};
        QStringList m_repoTags;
        ulong m_created {0};
        ulong m_size {0};
        ulong m_virtualSize {0};
        int m_containers {0};
        
    public:
        DockerImage();
        DockerImage(const QJsonObject &imageObject);

        QString id() const;
        QString parentId() const;
        
        QStringList repoTags() const;
        ulong created() const;
        ulong size() const;
        ulong virtualSize() const;
        
        int containers() const;
        
        bool operator ==(const DockerImage &dockerImage) const;

        QString toString() const;
    };
}

#endif // DOCKERIMAGE_H
