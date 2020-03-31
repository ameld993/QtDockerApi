#ifndef IMAGELISTMODEL_H
#define IMAGELISTMODEL_H

#include "Image.h"

#include <QAbstractListModel>
#include <QTimer>

namespace docker {

    class ImageListModel : public QAbstractListModel
    {
        Q_OBJECT

        Q_PROPERTY(quint32 updateInterval READ updateInterval WRITE setUpdateInterval NOTIFY updateIntervalChanged)

        Q_PROPERTY(bool all READ all WRITE setAll NOTIFY allChanged)
        Q_PROPERTY(bool digest READ digest WRITE setDigest NOTIFY digestChanged)
        Q_PROPERTY(QString filters READ filters WRITE setFilters NOTIFY filtersChanged)

    public:
        explicit ImageListModel(QObject *parent = nullptr);

        quint32 updateInterval() const;

        bool all() const;
        bool digest() const;
        QString filters() const;

        // Basic functionality:
        int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

        /**
         * @brief roleNames "imageId", "parentId", "imageSize", "virtualSize", "repoTags", "containers"
         * @return
         */
        QHash<int, QByteArray> roleNames() const override;

        static void registerQml();

    signals:
        void updateIntervalChanged();
        void listUpdated();

        void allChanged();
        void digestChanged();
        void filtersChanged();

    public slots:
        void setUpdateInterval(const quint32 &interval);

        void setAll(const bool &all);
        void setDigest(const bool &digest);
        void setFilters(const QString &filters);

        void updateImageList();

    private slots:
        void updateList(const QVector<Image> &list);

    private:
        QTimer m_updateTimer;
        quint32 m_updateInterval {0};

        QVector<Image> m_imageList;

        bool m_all {false};
        bool m_digest {false};
        QString m_filters {"{}"};
    };

}
#endif // IMAGELISTMODEL_H
