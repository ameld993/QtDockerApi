#include "dockerrequestgenerator.h"


QNetworkRequest dockerApi::dockerRequestUrl(const QString &path, const QUrlQuery &query)
{
    QUrl url(DOCKER_DAEMON_URL);
    url.setPath(path);

    if (!query.isEmpty()) {
        url.setQuery(query);
    }

    return QNetworkRequest(url);
}


QNetworkRequest dockerApi::dockerRequestUrl(const QString &path)
{
    QUrl url(DOCKER_DAEMON_URL);
    url.setPath(path);

    return QNetworkRequest(url);
}


QNetworkRequest dockerApi::getContainterList(QUrlQuery query)
{
    return dockerRequestUrl("/containers/json", query);
}


QNetworkRequest dockerApi::inspectContainer(const QString containerId, QUrlQuery query)
{
    QString pathTmp = "/containers/%1/json";
    QString path = pathTmp.arg(containerId);

    return dockerRequestUrl(path, query);
}


QNetworkRequest dockerApi::listRunningProcessesInContainer(const QString containerId, QUrlQuery query)
{
    QString pathTmp = "/containers/%1/top";
    QString path = pathTmp.arg(containerId);

    return dockerRequestUrl(path, query);
}


QNetworkRequest dockerApi::startContainter(const QString containerId, QUrlQuery query)
{
    QString pathTmp = "/containers/%1/start";
    QString path = pathTmp.arg(containerId);

    return dockerRequestUrl(path, query);
}


QNetworkRequest dockerApi::stopContainer(const QString containerId, QUrlQuery query)
{
    QString pathTmp = "/containers/%1/stop";
    QString path = pathTmp.arg(containerId);

    return dockerRequestUrl(path, query);
}


QNetworkRequest dockerApi::restartContainer(const QString containerId, QUrlQuery query)
{
    QString pathTmp = "/containers/%1/restart";
    QString path = pathTmp.arg(containerId);

    return dockerRequestUrl(path, query);
}


QNetworkRequest dockerApi::killContainter(const QString containerId, QUrlQuery query)
{
    QString pathTmp = "/containers/%1/kill";
    QString path = pathTmp.arg(containerId);

    return dockerRequestUrl(path, query);
}


QNetworkRequest dockerApi::pauseContainer(const QString containerId)
{
    QString pathTmp = "/containers/%1/pause";
    QString path = pathTmp.arg(containerId);

    return dockerRequestUrl(path);
}


QNetworkRequest dockerApi::unpauseContainer(const QString containerId)
{
    QString pathTmp = "/containers/%1/unpause";
    QString path = pathTmp.arg(containerId);

    return dockerRequestUrl(path);
}


QNetworkRequest dockerApi::removeContainer(const QString containerId, QUrlQuery query)
{
    QString pathTmp = "/containers/%1";
    QString path = pathTmp.arg(containerId);

    return dockerRequestUrl(path, query);
}


QNetworkRequest dockerApi::getImageList(QUrlQuery query)
{
    return dockerRequestUrl("/images/json", query);
}

