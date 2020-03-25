#include "DockerRequestGenerator.h"


QNetworkRequest docker::dockerRequestUrl(const QString &path, const QUrlQuery &query)
{
    QUrl url(DOCKER_DAEMON_URL);
    url.setPath(path);

    if (!query.isEmpty()) {
        url.setQuery(query);
    }

    return QNetworkRequest(url);
}



QNetworkRequest docker::getContainterList(QUrlQuery query)
{
    return dockerRequestUrl("/containers/json", query);
}


QNetworkRequest docker::createContainer(QUrlQuery query)
{
    return dockerRequestUrl("/containers/create", query);
}


QNetworkRequest docker::inspectContainer(const QString containerId, QUrlQuery query)
{
    QString pathTmp = "/containers/%1/json";
    QString path = pathTmp.arg(containerId);

    return dockerRequestUrl(path, query);
}


QNetworkRequest docker::listRunningProcessesInContainer(const QString containerId, QUrlQuery query)
{
    QString pathTmp = "/containers/%1/top";
    QString path = pathTmp.arg(containerId);

    return dockerRequestUrl(path, query);
}


QNetworkRequest docker::startContainter(const QString containerId, QUrlQuery query)
{
    QString pathTmp = "/containers/%1/start";
    QString path = pathTmp.arg(containerId);

    return dockerRequestUrl(path, query);
}


QNetworkRequest docker::stopContainer(const QString containerId, QUrlQuery query)
{
    QString pathTmp = "/containers/%1/stop";
    QString path = pathTmp.arg(containerId);

    return dockerRequestUrl(path, query);
}


QNetworkRequest docker::restartContainer(const QString containerId, QUrlQuery query)
{
    QString pathTmp = "/containers/%1/restart";
    QString path = pathTmp.arg(containerId);

    return dockerRequestUrl(path, query);
}


QNetworkRequest docker::killContainter(const QString containerId, QUrlQuery query)
{
    QString pathTmp = "/containers/%1/kill";
    QString path = pathTmp.arg(containerId);

    return dockerRequestUrl(path, query);
}


QNetworkRequest docker::pauseContainer(const QString containerId)
{
    QString pathTmp = "/containers/%1/pause";
    QString path = pathTmp.arg(containerId);

    return dockerRequestUrl(path);
}


QNetworkRequest docker::unpauseContainer(const QString containerId)
{
    QString pathTmp = "/containers/%1/unpause";
    QString path = pathTmp.arg(containerId);

    return dockerRequestUrl(path);
}


QNetworkRequest docker::removeContainer(const QString containerId, QUrlQuery query)
{
    QString pathTmp = "/containers/%1";
    QString path = pathTmp.arg(containerId);

    return dockerRequestUrl(path, query);
}


QNetworkRequest docker::getImageList(QUrlQuery query)
{
    return dockerRequestUrl("/images/json", query);
}


QNetworkRequest docker::builImage(QUrlQuery query)
{
    return dockerRequestUrl("/build", query);
}
