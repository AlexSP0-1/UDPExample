#include "udpserverexample.h"
#include "commandlineparser/commandlineoptions.h"
#include "commandlineparser/commandlineparser.h"

#include <storage/UDPServerStorageFileImpl.h>
#include <storage/UDPServerStorageInterface.h>
#include <QThreadPool>
#include <QUdpSocket>

namespace udpserver
{
class UDPServerExamplePrivate
{
public:
    UDPServerExamplePrivate(QCoreApplication &application)
        : m_application(nullptr)
        , m_options(std::make_unique<CommandLineOptions>())
        , m_storage(nullptr)
        , m_socket(nullptr)
    {
        m_application = &application;
    }

public:
    QCoreApplication *m_application;
    std::unique_ptr<CommandLineOptions> m_options;

    std::unique_ptr<UDPServerStorageInterface> m_storage;

    std::unique_ptr<QUdpSocket> m_socket;
};

UDPServerExample::UDPServerExample(QCoreApplication &app)
    : d(std::make_unique<UDPServerExamplePrivate>(app))
{}

int UDPServerExample::run()
{
    QString error;

    udpserver::CommandLineParser parser(d->m_application);

    udpserver::CommandLineParser::CommandLineParseResult result = parser.parseCommandLine(d->m_options.get(), &error);

    if (result == CommandLineParser::CommandLineHelpRequested)
    {
        //returns with specified exit code
        parser.showHelp(0);
        //return 0;
    }

    if (result == CommandLineParser::CommandLineVersionRequested)
    {
        //returns with specified exit code
        parser.showVersion();
        //return 0;
    }

    if (result != CommandLineParser::CommandLineOk)
    {
        printf("%s\n", error.toStdString().c_str());
        //returns with specified exit code
        parser.showHelp(-1);
        //return -1;
    }

    //TODO validate port

    d->m_storage = std::make_unique<UDPServerStorageFileImpl>(d->m_options->resourcePath);
    d->m_storage->update();

    if (!d->m_storage->isValid())
    {
        printf("Can't open file: %s\n", d->m_options->resourcePath.toStdString().c_str());
        //returns with specified exit code
        parser.showHelp(-1);
        //return -1;
    }

    d->m_socket = std::make_unique<QUdpSocket>(new QUdpSocket());
    d->m_socket->bind(QHostAddress::LocalHost, d->m_options->port);

    connect(d->m_socket.get(), &QUdpSocket::readyRead, this, &UDPServerExample::readPendingDatagrams);

    return 0;
}

int UDPServerExample::readPendingDatagrams()
{
    while (d->m_socket->hasPendingDatagrams())
    {
        QNetworkDatagram datagram = d->m_socket->receiveDatagram();

        UDPserverExampleWorker *worker = new UDPserverExampleWorker(d->m_socket.get(), d->m_storage.get(), datagram);

        //QThreadPool takes ownership of worker and automatically deletes it.
        QThreadPool::globalInstance()->start(worker);
    }
    return 0;
}

UDPServerExample::~UDPServerExample() {}
} // namespace udpserver
