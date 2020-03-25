#ifndef DOCKERIMAGE_H
#define DOCKERIMAGE_H

#include <QObject>

namespace docker {
    
    typedef struct _Docker_Image_{
        QString m_id;
        QString m_parentId;
        QStringList m_repoTags;
        ulong m_created;
        ulong m_size;
        ulong m_virtualSize;
        int m_containers;
    } DockerImageS;

    
    class DockerImage : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged)
        Q_PROPERTY(QString parentId READ parentId WRITE setParentId NOTIFY parentIdChanged)
        Q_PROPERTY(QStringList repoTags READ repoTags WRITE setRepoTags NOTIFY repoTagsChanged)
        Q_PROPERTY(ulong created READ created WRITE setCreated NOTIFY createdChanged)
        Q_PROPERTY(ulong size READ size WRITE setSize NOTIFY sizeChanged)
        Q_PROPERTY(ulong virtualSize READ virtualSize WRITE setVirtualSize NOTIFY virtualSizeChanged)
        Q_PROPERTY(int containers READ containers WRITE setContainers NOTIFY containersChanged)
        
    public:
        explicit DockerImage(QObject *parent = nullptr);
        
        QString id() const;
        QString parentId() const;
        
        QStringList repoTags() const;
        ulong created() const;
        ulong size() const;
        ulong virtualSize() const;
        
        int containers() const;
        
        bool operator ==(const DockerImage &dockerImage);
    
    signals:
        void idChanged(); 
        void parentIdChanged();
        void repoTagsChanged();
        void createChanged();
        void sizeChanged();
        void virtualSizeChanged();
        void containersChanged();
        
    public slots:
        void setId(const QString &id);
        void setParentId(const QString &parentId);
        void setRepoTags(const QStringList &repoTags);
        void setCreated(const ulong &created);
        void setSize(const ulong &size);
        void setVirtualSize(const ulong &virtualSize);
        void setContainers(const int &containers);
        
    private:
        QString m_id;
        QString m_parentId;
        QStringList m_repoTags;
        ulong m_created;
        ulong m_size;
        ulong m_virtualSize;
        int m_containers;
    };
}

#endif // DOCKERIMAGE_H
