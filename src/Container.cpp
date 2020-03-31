#include "Container.h"

#include <QJsonObject>
#include <QJsonArray>


docker::_Port_::_Port_(const QJsonObject &portObj)
{
    this->m_type = portObj["Type"].toString("");
    this->m_privatePort = portObj["PrivatePort"].toInt(0);
    this->m_publicPort = portObj["PublicPort"].toInt(0);
}


void docker::_Port_::operator =(const QJsonObject &portObj)
{
    this->m_type = portObj["Type"].toString("");
    this->m_privatePort = portObj["PrivatePort"].toInt(0);
    this->m_publicPort = portObj["PublicPort"].toInt(0);
}


docker::Container::Container()
{

}

docker::Container::Container(const QJsonObject &obj)
{
    m_id = obj["Id"].toString("");
    m_image = obj["Image"].toString("");
    m_imageId = obj["ImageID"].toString("");
    m_created = obj["Created"].toString("0").toULongLong();
    m_state = obj["State"].toString("");
    m_status = obj["Status"].toString("");
    
    QJsonArray ports = obj["Ports"].toArray(QJsonArray());
    for (int i = 0; i < ports.size(); i++) {
        QJsonObject portObj = ports.at(i).toObject(QJsonObject());
        Port port = portObj;
        m_ports.push_back(port);
    }
    
    m_sizeRw = obj["SizeRw"].toInt(0);
    m_sizeRootFs = obj["SizeRootFs"].toInt(0);
    
    obj["NetworkSettings"].toObject(QJsonObject());
}

QString docker::Container::id() const
{
    return m_id;
}

QString docker::Container::image() const
{
    return m_image;
}

QString docker::Container::imageId() const
{
    return m_imageId;
}

QString docker::Container::state() const
{
    return m_state;
}

QString docker::Container::status() const
{
    return m_status;
}

qulonglong docker::Container::created() const
{
    return m_created;
}

qulonglong docker::Container::sizeRw() const
{
    return m_sizeRw;
}

qulonglong docker::Container::sizeRootFs() const
{
    return m_sizeRootFs;
}

QList<docker::Port> docker::Container::ports() const
{
    return m_ports;
}

QMap<QString, QString> docker::Container::labels() const
{
    return m_labels;
}

docker::Networks docker::Container::networkSettings() const
{
    return m_networkSettings;
}


bool docker::Container::operator ==(const docker::Container &container) const
{
    return m_id == container.m_id && m_imageId == container.m_imageId;
}


