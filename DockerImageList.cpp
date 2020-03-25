#include "DockerImageList.h"
#include "DockerEngine.h"
#include "DockerImageListReply.h"


docker::DockerImageList::DockerImageList(QObject *parent) : QObject(parent)
{
    m_updateTimer.setInterval(3000);
    connect(&m_updateTimer, &QTimer::timeout, this, &DockerImageList::updateImageList);
    m_updateTimer.start();
}


bool docker::DockerImageList::all() const
{
    return m_all;
}


bool docker::DockerImageList::digest() const
{
    return m_digest;
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


void docker::DockerImageList::updateImageList()
{
     DockerEngine *dockerEngine = DockerEngine::instance();

     QUrlQuery query;

     DockerImageListReply *reply = dockerEngine->getDockerImages(query);

     connect(reply, &DockerImageListReply::replyReceived, [=](){
        QVector<DockerImage> imageList = reply->getImages();

        qDebug() << "Images found" << imageList.size();
     });


}
