#ifndef DOCKERREPLY_H
#define DOCKERREPLY_H

#include <QObject>

class QNetworkReply;

namespace docker {

    class DockerReply : public QObject
    {
        Q_OBJECT
    public:
        explicit DockerReply(QNetworkReply *reply, QObject *parent = nullptr);

        QString getErrorStr() const;
        int getStatusCode() const;

        QByteArray data() const;

    signals:
        void replyReceived();
        void errorReceived(const QString &errorStr);

    private:
        /**
         * @brief onReplyReceived - exiting the method emits replyReceived
         */
        virtual void onReplyReceived();

    protected:
        QString m_errorString;
        int m_statusCode {0};

        QByteArray m_data;
    };

}
#endif // DOCKERREPLY_H
