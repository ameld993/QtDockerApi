#ifndef DOCKERIMAGE_H
#define DOCKERIMAGE_H

#include <QString>
#include <QStringList>

class QJsonObject;

namespace docker {
        
    class Image
    {
        QString m_id {"none"};
        QString m_parentId {"none"};
        QStringList m_repoTags;
        ulong m_created {0};
        ulong m_size {0};
        ulong m_virtualSize {0};
        int m_containers {0};
        
    public:
        enum Info {
            IMAGE_ID = Qt::UserRole + 100,
            IMAGE_PARENT_ID,
            IMAGE_REPO_TAGS,
            IMAGE_CREATED,
            IMAGE_SIZE,
            IMAGE_VIRTUAL_SIZE,
            IMAGE_CONTAINERS
        };

        Image();
        Image(const QJsonObject &imageObject);

        QString id() const;
        QString parentId() const;
        
        QStringList repoTags() const;
        qulonglong created() const;
        qulonglong size() const;
        qulonglong virtualSize() const;
        
        int containers() const;
        
        bool operator ==(const Image &dockerImage) const;

        QString toString() const;
    };
}

#endif // DOCKERIMAGE_H
