#ifndef _UDP_CLIENT_EXAMPLE_H
#define _UDP_CLIENT_EXAMPLE_H

#include <memory>
#include <QCoreApplication>
#include <QNetworkDatagram>

const unsigned int CLIENT_TIMEOUT = 2; //In seconds

namespace udpclient
{
class UDPClientPrivate;

class UDPClientExample : public QObject
{
    Q_OBJECT
public:
    UDPClientExample(QCoreApplication &app);
    ~UDPClientExample();

    int run();

private:
    void sendRequest();

    void readPendingDatagrams();
    void processDatagram(QNetworkDatagram datagram);

private slots:
    void stopOnTimeout();

private:
    std::unique_ptr<UDPClientPrivate> d;

private:
    UDPClientExample(const UDPClientExample &) = delete;
    UDPClientExample(UDPClientExample &&)      = delete;
    UDPClientExample &operator=(const UDPClientExample &) = delete;
    UDPClientExample &operator=(UDPClientExample &&) = delete;
};
} // namespace udpclient

#endif // _UDP_CLIENT_EXAMPLE_H
