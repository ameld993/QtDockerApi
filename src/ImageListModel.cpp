#include "ImageListModel.h"
#include "Image.h"
#include "Engine.h"
#include "ImageListReply.h"

#include <qqmlapplicationengine.h>

#ifdef QT_DEBUG
#include <QDebug>
#endif

docker::ImageListModel::ImageListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    connect(&m_updateTimer, &QTimer::timeout, this, &ImageListModel::updateImageList);

    connect(this, &ImageListModel::updateIntervalChanged, [=](){
        m_updateTimer.stop();

        if (m_updateInterval > 0) {
            m_updateTimer.setInterval(m_updateInterval);
            m_updateTimer.start();
        }
    });

    QTimer::singleShot(0, this, &ImageListModel::updateImageList);
}


quint32 docker::ImageListModel::updateInterval() const
{
    return m_updateInterval;
}


bool docker::ImageListModel::all() const
{
    return m_all;
}


bool docker::ImageListModel::digest() const
{
    return m_digest;
}


QString docker::ImageListModel::filters() const
{
    return m_filters;
}


int docker::ImageListModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return m_imageList.size();
}


QVariant docker::ImageListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    Image image = m_imageList.at(index.row());
    QVariant val;

    switch (Image::Info(role)) {
        case Image::IMAGE_ID:
            val = image.id();
            break;
        case Image::IMAGE_PARENT_ID:
            val = image.parentId();
            break;
        case Image::IMAGE_REPO_TAGS:
            val = image.repoTags();
            break;
        case Image::IMAGE_CREATED:
            val = image.created();
            break;
        case Image::IMAGE_SIZE:
            val = image.size();
            break;
        case Image::IMAGE_VIRTUAL_SIZE:
            val = image.virtualSize();
            break;
        case Image::IMAGE_CONTAINERS:
            val = image.containers();
            break;
    }

    return val;
}


void docker::ImageListModel::setUpdateInterval(const quint32 &interval)
{
    if (interval == m_updateInterval) {
        return;
    }

    m_updateInterval = interval;
    emit updateIntervalChanged();
}


void docker::ImageListModel::setAll(const bool &all)
{
    if (all == m_all) {
        return;
    }

    m_all = all;
    emit allChanged();
}


void docker::ImageListModel::setDigest(const bool &digest)
{
    if (digest == m_digest) {
        return;
    }

    m_digest = digest;
    emit digestChanged();
}


void docker::ImageListModel::setFilters(const QString &filters)
{
    if (filters == m_filters) {
        return;
    }

    m_filters = filters;
    emit filtersChanged();
}


void docker::ImageListModel::updateImageList()
{
    Engine *dockerEngine = Engine::instance();

    QUrlQuery query = getUrlQuery();
    ImageListReply *reply = dockerEngine->getDockerImages(query);

    connect(reply, &ImageListReply::replyReceived, [=](){
       QList<Image> imageList = reply->images();
       updateList(imageList);
       reply->deleteLater();
    });

    connect(reply, &ImageListReply::errorReceived, [=](const QString &errMsg){
#ifdef QT_DEBUG
        qDebug() << "Error ImageListModel::updateImageList :" << errMsg;
#endif
        reply->deleteLater();
    });
}


void docker::ImageListModel::updateList(const QList<docker::Image> &list)
{
    beginResetModel();

    bool listWasUpdated {false};

    for (int i = 0; i < m_imageList.size(); ) {
        if (list.contains(m_imageList.at(i))) {
            i++;
        }
        else {
            m_imageList.removeAt(i);
            listWasUpdated = true;
        }
    }

    for (int i = 0; i < list.size(); i++) {
        if (!m_imageList.contains(list.at(i))) {
            m_imageList.push_back(list.at(i));
            listWasUpdated = true;
        }
    }

    endResetModel();

    if (listWasUpdated) {
        emit listUpdated();
    }
}


QUrlQuery docker::ImageListModel::getUrlQuery() const
{
    QUrlQuery query;
    query.addQueryItem("all", m_all ? "true" : "false");
    query.addQueryItem("digest", m_digest ? "true" : "false");

    if (!m_filters.isEmpty()) {
        query.addQueryItem("filters", m_filters);
    }

    return query;
}


QHash<int, QByteArray> docker::ImageListModel::roleNames() const
{
    QHash<int, QByteArray> roleNames;

    roleNames[Image::IMAGE_ID] = "imageId";
    roleNames[Image::IMAGE_PARENT_ID] = "parentID";
    roleNames[Image::IMAGE_SIZE] = "imageSize";
    roleNames[Image::IMAGE_VIRTUAL_SIZE] = "virtualSize";
    roleNames[Image::IMAGE_REPO_TAGS] = "repoTags";
    roleNames[Image::IMAGE_CONTAINERS] = "containers";

    return roleNames;
}


void docker::ImageListModel::registerQml()
{
    qmlRegisterType<ImageListModel>("Docker", 1, 0, "ImageListModel");
}
