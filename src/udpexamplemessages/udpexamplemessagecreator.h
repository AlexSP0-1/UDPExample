#ifndef _UDP_EXAMPLE_MESSAGE_CREATOR_H
#define _UDP_EXAMPLE_MESSAGE_CREATOR_H

#include "udpexamplemessage.h"

#include <QByteArray>
#include <QString>

namespace udpexamplemessages
{
class UDPExampleMessageCreator
{
public:
    UDPExampleMessageCreator(UdpExampleMessageType type, QString resourceName, QString resource);

    QByteArray getData();

private:
    QByteArray m_data;
};
} // namespace udpexamplemessages
#endif // _UDP_EXAMPLE_MESSAGE_CREATOR_H
