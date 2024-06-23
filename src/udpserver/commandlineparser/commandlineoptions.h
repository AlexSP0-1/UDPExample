#ifndef _UDP_SERVER_COMMAND_LINE_OPTIONS_H
#define _UDP_SERVER_COMMAND_LINE_OPTIONS_H

#include <QString>

#define UDP_SERVER_EXAMPLE_DEFAULT_PORT 11123

namespace udpserver
{
class CommandLineOptions
{
public:
    enum Action
    {
        listen
    };

    Action action{Action::listen};

    unsigned int port{UDP_SERVER_EXAMPLE_DEFAULT_PORT};
    QString resourcePath{};
};
} // namespace udpserver
#endif //_UDP_SERVER_COMMAND_LINE_OPTIONS_H
