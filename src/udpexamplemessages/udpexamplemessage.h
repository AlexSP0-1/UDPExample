#ifndef _UDP_EXAMPLE_MESSAGE_H
#define _UDP_EXAMPLE_MESSAGE_H

#include <cstdint>

namespace udpexamplemessages
{
enum class UdpExampleMessageType
{
    None                  = 0,
    Request               = 1,
    Answer                = 2,
    ResourceNotFoundError = 3
};

struct UdpExampleMessageHeader
{
    uint8_t type                = 0;
    uint32_t resourceNameLength = 0;
    uint32_t resourceLength     = 0;
};

} // namespace udpexamplemessages

#endif //_UDP_EXAMPLE_MESSAGE_H
