#include "udpserverexample.h"
#include "commandlineparser/commandlineoptions.h"

#include <commandlineparser/commandlineparser.h>

namespace udpserver
{
class UDPServerExamplePrivate
{
public:
    UDPServerExamplePrivate(QCoreApplication &application)
        : m_options(std::make_unique<CommandLineOptions>())
    {
        m_application = &application;
    }

public:
    std::unique_ptr<CommandLineOptions> m_options;
    QCoreApplication *m_application = nullptr;
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

    return 0;
}

UDPServerExample::~UDPServerExample() {}
} // namespace udpserver
