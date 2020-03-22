#ifndef DOCKERREQUESTGENERATOR_H
#define DOCKERREQUESTGENERATOR_H

#include <QNetworkRequest>
#include <QUrlQuery>
#include <QVariant>
#include <QMap>

namespace dockerApi
{

#ifndef DOCKER_DAEMON_URL
#define DOCKER_DAEMON_URL "http://127.0.0.1:2375"
#endif

typedef QMap<QString, QVariant> QueryParameters ;

QNetworkRequest dockerRequestUrl(const QString &path, const QUrlQuery &query);
QNetworkRequest dockerRequestUrl(const QString &path);


/**
 * @brief getContainterList - Returns a list of containers.
 *      Note that it uses a different, smaller representation of a container
 *      than inspecting a single container. For example, the list of linked
 *      containers is not propagated.
 * @ref https://docs.docker.com/engine/api/v1.40/#operation/ContainerList
 * @return
 */
QNetworkRequest getContainterList(QUrlQuery query = QUrlQuery());

/**
 * @brief inspectContainer - Return low-level information about a container.
 * @ref https://docs.docker.com/engine/api/v1.40/#operation/ContainerInspect
 * @param containderId - Container to inspect
 * @param query
 * @return
 */
QNetworkRequest inspectContainer(const QString containerId, QUrlQuery query = QUrlQuery());


/**
 * @brief listRunningProcessesInContainer
 * @param containerId
 * @param query
 * @return
 */
QNetworkRequest listRunningProcessesInContainer(const QString containerId, QUrlQuery query = QUrlQuery());

/**
 * @brief startContainter
 * @param containerId
 * @param query
 * @return
 */
QNetworkRequest startContainter(const QString containerId, QUrlQuery query = QUrlQuery());

/**
 * @brief stopContainer
 * @param containerId
 * @param query
 * @return
 */
QNetworkRequest stopContainer(const QString containerId, QUrlQuery query = QUrlQuery());

/**
 * @brief restartContainer
 * @param containerId
 * @param query
 * @return
 */
QNetworkRequest restartContainer(const QString containerId, QUrlQuery query = QUrlQuery());

/**
 * @brief killContainter - Send a POSIX signal to a container, defaulting to killing to the container
 * @param containerId
 * @param query
 * @return
 */
QNetworkRequest killContainter(const QString containerId, QUrlQuery query = QUrlQuery());

/**
 * @brief pauseContainer - Use the freezer cgroup to suspend all processes in a container.
 *      Traditionally, when suspending a process the SIGSTOP signal is used, which is observable
 *      by the process being suspended. With the freezer cgroup the process is unaware, and unable
 *      to capture, that it is being suspended, and subsequently resumed.
 * @param containerId
 * @return
 */
QNetworkRequest pauseContainer(const QString containerId);

/**
 * @brief unpauseContainer
 * @param containerId
 * @return
 */
QNetworkRequest unpauseContainer(const QString containerId);

/**
 * @brief removeContainer
 * @param containerId
 * @param query
 * @return
 */
QNetworkRequest removeContainer(const QString containerId, QUrlQuery query = QUrlQuery());


/**
 * @brief getImageList - Returns a list of images on the server. Note that it uses a different,
 *      smaller representation of an image than inspecting a single image.
 * @ref
 * @return
 */
QNetworkRequest getImageList(QUrlQuery query = QUrlQuery());


QNetworkRequest builImage(QUrlQuery query = QUrlQuery());

};

 #endif // DOCKERREQUESTGENERATOR_H
