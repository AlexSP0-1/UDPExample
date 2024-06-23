#include "udpexamplemessagecreator.h"

namespace udpexamplemessages
{
UDPExampleMessageCreator::UDPExampleMessageCreator(UdpExampleMessageType type, QString resourceName, QString resource)
{
    QString prefix = "-BEGIN-";
    QString suffix = "-END-";
    QString content;

    if (type == UdpExampleMessageType::ResourceNotFoundError)
        prefix = QString("-ERROR-");

    if (type == UdpExampleMessageType::ResourceNotFoundError)
    {
        content = QString("%1\n%2\n%3\n").arg(prefix, "RESOURCE NOT FOUND", suffix);
    }
    else
    {
        content = QString("%1\n%2\n%3\n").arg(prefix, resource, suffix);
    }

    UdpExampleMessageHeader header;
    header.type               = (uint8_t) type;
    header.resourceNameLength = resourceName.toUtf8().size();
    if (resource == NULL)
    {
        header.resourceLength = 0;
    }
    else
    {
        header.resourceLength = content.toUtf8().size();
    }

    size_t size = sizeof(UdpExampleMessageHeader) + header.resourceNameLength + header.resourceLength;

    m_data.resize(size);

    memset(m_data.data(), 0, size);

    memcpy(m_data.data(), &header, sizeof(header));
    memcpy(m_data.data() + sizeof(header), resourceName.toUtf8(), header.resourceNameLength);
    if (resource != NULL)
        memcpy(m_data.data() + sizeof(header) + header.resourceNameLength, content.toUtf8(), header.resourceLength);
}

QByteArray UDPExampleMessageCreator::getData()
{
    return m_data;
}
} // namespace udpexamplemessages
