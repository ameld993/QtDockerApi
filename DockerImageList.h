#ifndef DOCKERIMAGELIST_H
#define DOCKERIMAGELIST_H

#include "DockerImage.h"

#include <QObject>
#include <QVector>
#include <QTimer>

namespace docker{

    class DockerImageList : public QObject
    {
        Q_OBJECT

        Q_PROPERTY(uint updateInterval READ updateInterval WRITE setUpdateInterval NOTIFY updateIntervalChanged)

        Q_PROPERTY(bool all READ all WRITE setAll NOTIFY allChanged)
        Q_PROPERTY(bool digest READ digest WRITE setDigest NOTIFY digestChanged)
        Q_PROPERTY(QString filters READ filters WRITE setFilters NOTIFY filtersChanged)


    public:
        explicit DockerImageList(QObject *parent = nullptr);

        uint updateInterval() const;

        bool all() const;
        bool digest() const;
        QString filters() const;

    signals:
        void listUpdated();
        void updateIntervalChanged();

        void allChanged();
        void digestChanged();
        void filtersChanged();

    public slots:
        void setUpdateInterval(const uint &interval);

        void setAll(const bool &all);
        void setDigest(const bool &digest);
        void setFilters(const QString &filters);

    private slots:
        void updateImageList();
        void updateList(const QVector<DockerImage> &list);
    private:
        QTimer m_updateTimer;
        uint m_updateInterval {5000};

        QVector<DockerImage> m_imageList;

        bool m_all {false};
        bool m_digest {false};
        QString m_filters {"{}"};
    };
}
#endif // DOCKERIMAGELIST_H
