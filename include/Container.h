#ifndef CONTAINER_H
#define CONTAINER_H

#include <QString>
#include <QStringList>
#include <QMap>

class QJsonObject;

namespace docker {

    typedef struct _Port_ {
        QString m_type {""};
        QString m_ip {""};
        quint32 m_privatePort {0};
        quint32 m_publicPort {0};

        _Port_() {}
        _Port_(const QJsonObject &portObj);
        void operator =(const QJsonObject &portObj);
    } Port;

    typedef struct _MountPoint_ {
        QString m_name {""};
        QString m_source {""};
        QString m_destination {""};
        QString m_mode {""};
        QString m_propagation {""};
        bool m_rw {false};
    } MountPoint;

    typedef struct _Network_Bridge_ {
        QString m_networkID {""};
        QString m_endpointID {""};
        QString m_gateway {""};
        QString m_ipAddress {""};
        QString m_ipPrefixLen {""};
        QString m_ipv6Gateway {""};
        QString m_globalIPv6Address {""};
        QString m_globalIPv6PrefixLen {""};
        QString m_macAddress {""};
    } NetworkBridge;

    typedef struct _Networks_ {
        NetworkBridge *m_bridge {nullptr};

    } Networks;

    class Container
    {
        QString m_id {""};
        QString m_image {""};
        QString m_imageId {""};
        QString m_state {""};
        QString m_status {""};
        QStringList m_names;

        qulonglong m_created {0};
        qulonglong m_sizeRw {0};
        qulonglong m_sizeRootFs {0};

        QList<Port> m_ports;
        QMap<QString, QString> m_labels;

        Networks m_networkSettings;

    public:
        Container();
        Container(const QJsonObject &obj);

        QString id() const;
        QString image() const;
        QString imageId() const;
        QString state() const;
        QString status() const;

        qulonglong created() const;
        qulonglong sizeRw() const;
        qulonglong sizeRootFs() const;

        QList<Port> ports() const;
        QMap<QString, QString> labels() const;
        Networks networkSettings() const;


        bool operator == (const Container &container) const;
    };

}

#endif // CONTAINER_H
