#ifndef _UDP_SERVER_COMMAND_LINE_OPTIONS_H
#define _UDP_SERVER_COMMAND_LINE_OPTIONS_H

#include <QString>

#include <QtNetwork/qhostaddress.h>

#define UDP_CLIENT_EXAMPLE_DEFAULT_PORT 11123
const char *const UDP_CLIENT_EXAMPLE_DEFAULT_ADDRESS = "127.0.0.1";

namespace udpclient
{
class CommandLineOptions
{
public:
    enum Action
    {
        send
    };

    Action action{Action::send};

    QHostAddress address = QHostAddress(QString(UDP_CLIENT_EXAMPLE_DEFAULT_ADDRESS));
    unsigned int port{UDP_CLIENT_EXAMPLE_DEFAULT_PORT};

    QString resourceName{};
};
} // namespace udpclient
#endif //_UDP_SERVER_COMMAND_LINE_OPTIONS_H
