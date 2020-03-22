#ifndef DOCKERREPLY_H
#define DOCKERREPLY_H

#include <QObject>

class QNetworkReply;

namespace dockerApi {

class DockerReply : public QObject
{
    Q_OBJECT

    QString m_errorString;

public:
    explicit DockerReply(QNetworkReply *reply, QObject *parent = nullptr);

    QString getErrorStr() const;

signals:
    void replyReceived();
    void errorReceived(const QString &errorStr);

private slots:
    virtual void parseReceivedData(const QByteArray &data);
};

}
#endif // DOCKERREPLY_H
