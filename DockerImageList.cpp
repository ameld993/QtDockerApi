#include "DockerImageList.h"
#include "DockerEngine.h"
#include "DockerImageListReply.h"


docker::DockerImageList::DockerImageList(QObject *parent) : QObject(parent)
{
    m_updateTimer.setInterval(m_updateInterval);

    connect(this, &DockerImageList::updateIntervalChanged, [=](){
       m_updateTimer.stop();
       m_updateTimer.setInterval(m_updateInterval);
       m_updateTimer.start();
    });

    connect(&m_updateTimer, &QTimer::timeout, this, &DockerImageList::updateImageList);
    QTimer::singleShot(0, this, &DockerImageList::updateImageList);

    m_updateTimer.start();
}

uint docker::DockerImageList::updateInterval() const
{
    return m_updateInterval;
}


bool docker::DockerImageList::all() const
{
    return m_all;
}


bool docker::DockerImageList::digest() const
{
    return m_digest;
}

QString docker::DockerImageList::filters() const
{
    return m_filters;
}

void docker::DockerImageList::setUpdateInterval(const uint &interval)
{
    if (m_updateInterval == interval) {
        return;
    }

    m_updateInterval = interval;
    emit updateIntervalChanged();
}


void docker::DockerImageList::setAll(const bool &all)
{
    if (all == m_all) {
        return;
    }

    m_all = all;
    emit allChanged();
}


void docker::DockerImageList::setDigest(const bool &digest)
{
    if (digest == m_digest) {
        return;
    }

    m_digest = digest;
    emit digestChanged();
}


void docker::DockerImageList::setFilters(const QString &filters)
{
    if (filters == m_filters) {
        return;
    }

    m_filters = filters;
    emit filtersChanged();
}


void docker::DockerImageList::updateImageList()
{
     DockerEngine *dockerEngine = DockerEngine::instance();

     QUrlQuery query;
     query.addQueryItem("all", m_all ? "true" : "false");
     query.addQueryItem("digest", m_digest ? "true" : "false");
     query.addQueryItem("filters", m_filters);

     DockerImageListReply *reply = dockerEngine->getDockerImages(query);

     connect(reply, &DockerImageListReply::replyReceived, [=](){
        QVector<DockerImage> imageList = reply->images();
        updateList(imageList);
        reply->deleteLater();
     });
}

void docker::DockerImageList::updateList(const QVector<docker::DockerImage> &list)
{
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

    if (listWasUpdated) {
        emit listUpdated();
    }
}
