#ifndef _UDP_SERVER_EXAMPLE_H
#define _UDP_SERVER_EXAMPLE_H

#include <memory>
#include <QCoreApplication>

namespace udpserver
{
class UDPServerExamplePrivate;

class UDPServerExample
{
public:
    UDPServerExample(QCoreApplication &app);
    ~UDPServerExample();

    int run();

private:
    std::unique_ptr<UDPServerExamplePrivate> d;

private:
    int parseArguments();

private:
    UDPServerExample(const UDPServerExample &) = delete;
    UDPServerExample(UDPServerExample &&)      = delete;
    UDPServerExample &operator=(const UDPServerExample &) = delete;
    UDPServerExample &operator=(UDPServerExample &&) = delete;
};

} // namespace udpserver
#endif //_UDP_SERVER_EXAMPLE_H
