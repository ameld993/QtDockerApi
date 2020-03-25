#ifndef DOCKERIMAGELIST_H
#define DOCKERIMAGELIST_H

#include <QObject>
#include <QTimer>

namespace docker{

    class DockerImageList : public QObject
    {
        Q_OBJECT

        Q_PROPERTY(bool all READ all WRITE setAll NOTIFY allChanged)
        Q_PROPERTY(bool digest READ digest WRITE setDigest NOTIFY digestChanged)

    public:
        explicit DockerImageList(QObject *parent = nullptr);
        bool all() const;
        bool digest() const;

    signals:
        void listUpdated();
        void allChanged();
        void digestChanged();

    public slots:
        void setAll(const bool &all);
        void setDigest(const bool &digest);

    private slots:
        void updateImageList();

    private:
        QTimer m_updateTimer;

        bool m_all;
        bool m_digest;
    };
}
#endif // DOCKERIMAGELIST_H
