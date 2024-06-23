#ifndef _UDP_EXAMPLE_SIMPLE_MESSAGE_PARSER_H
#define _UDP_EXAMPLE_SIMPLE_MESSAGE_PARSER_H

#include "udpexamplemessageparserinterface.h"

#include <memory>
#include <QByteArray>

namespace udpexamplemessages
{
class UDPExampleSimpleMessageParserPrivate;

class UDPExampleSimpleMessageParser : public UDPExampleMessageParserInterface
{
public:
    UDPExampleSimpleMessageParser(QByteArray message);
    ~UDPExampleSimpleMessageParser() override;

    UdpExampleMessageType getType() override;
    QString getResourceName() override;
    QString getResourceValue() override;

private:
    std::unique_ptr<UDPExampleSimpleMessageParserPrivate> d;

private:
    UDPExampleSimpleMessageParser(const UDPExampleSimpleMessageParser &) = delete;
    UDPExampleSimpleMessageParser(UDPExampleSimpleMessageParser &&)      = delete;
    UDPExampleSimpleMessageParser &operator=(const UDPExampleSimpleMessageParser &) = delete;
    UDPExampleSimpleMessageParser &operator=(UDPExampleSimpleMessageParser &&) = delete;
};
} // namespace udpexamplemessages
#endif // _UDP_EXAMPLE_SIMPLE_MESSAGE_PARSER_H
