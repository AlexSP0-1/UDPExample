#ifndef UDPEXAMPLEMESSAGEPARSERINTERFACE_H
#define UDPEXAMPLEMESSAGEPARSERINTERFACE_H

#include "udpexamplemessage.h"
#include <QString>

namespace udpexamplemessages
{
class UDPExampleMessageParserInterface
{
public:
    virtual ~UDPExampleMessageParserInterface() = default;

    virtual UdpExampleMessageType getType() = 0;
    virtual QString getResourceName()       = 0;
    virtual QString getResourceValue()      = 0;
};
} // namespace udpexamplemessages

#endif // UDPEXAMPLEMESSAGEPARSERINTERFACE_H
