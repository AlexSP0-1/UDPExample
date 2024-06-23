#ifndef _UDP_SERVER_EXAMPLE_H
#define _UDP_SERVER_EXAMPLE_H

#include <memory>
#include <QCoreApplication>
#include <QNetworkDatagram>
#include <QObject>

#include "udpserverexampleworker.h"

namespace udpserver
{
class UDPServerExamplePrivate;

class UDPServerExample : public QObject
{
    Q_OBJECT
public:
    UDPServerExample(QCoreApplication &app);
    ~UDPServerExample();

    int run();

private:
    std::unique_ptr<UDPServerExamplePrivate> d;

private:
    int parseArguments();
    int readPendingDatagrams();

private:
    UDPServerExample(const UDPServerExample &) = delete;
    UDPServerExample(UDPServerExample &&)      = delete;
    UDPServerExample &operator=(const UDPServerExample &) = delete;
    UDPServerExample &operator=(UDPServerExample &&) = delete;
};

} // namespace udpserver
#endif //_UDP_SERVER_EXAMPLE_H
