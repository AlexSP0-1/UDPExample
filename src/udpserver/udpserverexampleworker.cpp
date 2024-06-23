#include "udpserverexampleworker.h"

#include <QNetworkDatagram>

namespace udpserver
{
class UDPserverExampleWorkerPrivate
{
public:
    UDPserverExampleWorkerPrivate(QUdpSocket *socket, UDPServerStorageInterface *storage, QNetworkDatagram datagram)
        : m_socket{socket}
        , m_storage{storage}
        , m_datagram(datagram)
    {}
    QUdpSocket *m_socket{nullptr};
    UDPServerStorageInterface *m_storage{nullptr};
    QNetworkDatagram m_datagram;
};

UDPserverExampleWorker::UDPserverExampleWorker(QUdpSocket *socket,
                                               UDPServerStorageInterface *storage,
                                               QNetworkDatagram datagram)
    : d(std::make_unique<UDPserverExampleWorkerPrivate>(socket, storage, datagram))
{}

UDPserverExampleWorker::~UDPserverExampleWorker() {}

void UDPserverExampleWorker::run()
{
    QByteArray incoming_data = d->m_datagram.data();

    QString resource(incoming_data);

    QString answer = d->m_storage->getResource(resource);

    QByteArray outcoming_data = answer.toLatin1();

    d->m_socket->writeDatagram(d->m_datagram.makeReply(outcoming_data));
}

} // namespace udpserver
