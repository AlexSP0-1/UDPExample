#include "udpserverexampleworker.h"
#include "../udpexamplemessages/udpexamplemessage.h"
#include "../udpexamplemessages/udpexamplemessagecreator.h"
#include "../udpexamplemessages/udpexamplesimplemessageparser.h"

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
    //Parse request message
    udpexamplemessages::UDPExampleSimpleMessageParser parser(d->m_datagram.data());

    if (parser.getType() != udpexamplemessages::UdpExampleMessageType::Request)
    {
        return;
    }

    //Get resource value from storage
    QString answer = d->m_storage->getResource(parser.getResourceName());

    //Create and send answer
    udpexamplemessages::UdpExampleMessageType answerType = udpexamplemessages::UdpExampleMessageType::Answer;

    if (answer.isEmpty())
        answerType = udpexamplemessages::UdpExampleMessageType::ResourceNotFoundError;

    udpexamplemessages::UDPExampleMessageCreator creator(answerType, parser.getResourceName(), answer);

    d->m_socket->writeDatagram(d->m_datagram.makeReply(creator.getData()));
}

} // namespace udpserver
