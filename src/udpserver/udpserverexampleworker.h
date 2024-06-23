#ifndef _UDP_SERVER_EXAMPLE_WORKER_H
#define _UDP_SERVER_EXAMPLE_WORKER_H

#include <memory>
#include <QRunnable>
#include <QUdpSocket>

#include "storage/UDPServerStorageInterface.h"

namespace udpserver
{
class UDPserverExampleWorkerPrivate;

class UDPserverExampleWorker : public QRunnable
{
public:
    UDPserverExampleWorker(QUdpSocket *socket, UDPServerStorageInterface *storage, QNetworkDatagram datagram);
    ~UDPserverExampleWorker();

    void run() override;

private:
    std::unique_ptr<UDPserverExampleWorkerPrivate> d;

private:
    UDPserverExampleWorker(const UDPserverExampleWorker &) = delete;
    UDPserverExampleWorker(UDPserverExampleWorker &&)      = delete;
    UDPserverExampleWorker &operator=(const UDPserverExampleWorker &) = delete;
    UDPserverExampleWorker &operator=(UDPserverExampleWorker &&) = delete;
};

} // namespace udpserver

#endif // UDPSERVEREXAMPLEWORKER_H
