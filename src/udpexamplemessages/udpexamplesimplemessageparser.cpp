#include "udpexamplesimplemessageparser.h"

namespace udpexamplemessages
{
class UDPExampleSimpleMessageParserPrivate
{
public:
    UDPExampleSimpleMessageParserPrivate(QByteArray &message)
        : m_bytes(std::make_unique<QByteArray>(message))
    {}

    std::unique_ptr<QByteArray> m_bytes;
    UdpExampleMessageHeader m_header;
};

UDPExampleSimpleMessageParser::UDPExampleSimpleMessageParser(QByteArray message)
    : d(std::make_unique<UDPExampleSimpleMessageParserPrivate>(message))
{
    if (message.size() < sizeof(d->m_header))
    {
        return;
    }

    memcpy(&d->m_header, message.data(), sizeof(d->m_header));
}

UDPExampleSimpleMessageParser::~UDPExampleSimpleMessageParser() {}

UdpExampleMessageType UDPExampleSimpleMessageParser::getType()
{
    return UdpExampleMessageType{d->m_header.type};
}

QString UDPExampleSimpleMessageParser::getResourceName()
{
    QByteArray resNameData;

    size_t resNameIndex    = sizeof(d->m_header);
    size_t resNameEndIndex = resNameIndex + d->m_header.resourceNameLength;
    size_t fieldSize       = resNameEndIndex - sizeof(d->m_header);

    resNameData.resize(fieldSize);

    memcpy(resNameData.data(), d->m_bytes->data() + resNameIndex, fieldSize);

    return QString::fromUtf8(resNameData);
}

QString UDPExampleSimpleMessageParser::getResourceValue()
{
    QByteArray resData;

    size_t resIndex    = sizeof(d->m_header) + d->m_header.resourceNameLength;
    size_t resEndIndex = resIndex + d->m_header.resourceLength;
    size_t fieldSize   = resEndIndex - resIndex;

    resData.resize(fieldSize);

    memcpy(resData.data(), d->m_bytes->data() + resIndex, fieldSize);

    return QString::fromUtf8(resData);
}
} // namespace udpexamplemessages
