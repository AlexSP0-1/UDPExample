#include "udpclientexample.h"

#include <commandlineparser/commandlineoptions.h>
#include <commandlineparser/commandlineparser.h>

#include <QDataStream>
#include <QTimer>
#include <QUdpSocket>

namespace udpclient
{
class UDPClientPrivate
{
public:
    UDPClientPrivate(QCoreApplication &app)
        : m_ret{-1}
        , m_application(&app)
        , m_options()
        , m_parser(std::make_unique<CommandLineParser>(&app))
        , m_socket(nullptr)
        , m_timeoutTimer(std::make_unique<QTimer>())
    {}

    int m_ret;

    QCoreApplication *m_application;
    CommandLineOptions m_options;

    std::unique_ptr<CommandLineParser> m_parser;
    std::unique_ptr<QUdpSocket> m_socket;
    std::unique_ptr<QTimer> m_timeoutTimer;
};

UDPClientExample::UDPClientExample(QCoreApplication &app)
    : d(std::make_unique<UDPClientPrivate>(app))
{
    connect(d->m_timeoutTimer.get(), &QTimer::timeout, this, &UDPClientExample::stopOnTimeout);
}

UDPClientExample::~UDPClientExample() {}

int UDPClientExample::run()
{
    QString error;

    CommandLineParser::CommandLineParseResult result = d->m_parser->parseCommandLine(&d->m_options, &error);

    if (result == CommandLineParser::CommandLineHelpRequested)
    {
        //returns with specified exit code
        d->m_parser->showHelp(0);
        //return 0;
    }

    if (result == CommandLineParser::CommandLineVersionRequested)
    {
        //returns with specified exit code
        d->m_parser->showVersion();
        //return 0;
    }
    if (result != CommandLineParser::CommandLineOk)
    {
        printf("%s\n", error.toStdString().c_str());
        //returns with specified exit code
        d->m_parser->showHelp(-1);
        //return -1;
    }
    d->m_socket = std::make_unique<QUdpSocket>(new QUdpSocket());
    d->m_socket->bind(d->m_options.address, d->m_options.port);

    connect(d->m_socket.get(), &QUdpSocket::readyRead, this, &UDPClientExample::readPendingDatagrams);

    d->m_timeoutTimer->start(CLIENT_TIMEOUT * 1000);

    sendRequest();

    return d->m_ret;
}

void UDPClientExample::sendRequest()
{
    QByteArray data = d->m_options.resourceName.toLatin1();
    QDataStream out(&data, QIODevice::WriteOnly);

    size_t bytes = d->m_socket->writeDatagram(data, d->m_options.address, d->m_options.port);
    if (!bytes)
    {
        printf("Can't send request!\n");

        d->m_ret = -1;

        d->m_application->quit();
    }
}

void UDPClientExample::readPendingDatagrams()
{
    while (d->m_socket->hasPendingDatagrams())
    {
        QNetworkDatagram datagram = d->m_socket->receiveDatagram();

        processDatagram(datagram);
    }
}

void UDPClientExample::processDatagram(QNetworkDatagram datagram)
{
    QNetworkDatagram datt(datagram);
    unsigned int destPort = datagram.destinationPort();
    if (destPort == d->m_options.port)
    {
        //Server is not avaliable on localhost
        d->m_ret = -1;

        return;
    }

    QByteArray incoming_data = datagram.data();

    QString answer(incoming_data);

    printf("%s\n", answer.toStdString().c_str());

    d->m_application->quit();
}

void UDPClientExample::stopOnTimeout()
{
    printf("Can't get answer from server!\n");

    d->m_ret = -1;

    d->m_application->quit();
}
} // namespace udpclient
