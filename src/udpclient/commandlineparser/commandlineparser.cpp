#include "commandlineparser/commandlineparser.h"

#include <memory>
#include <QCommandLineParser>
#include <QtNetwork/qhostaddress.h>

namespace udpclient
{
class CommandLineParserPrivate
{
public:
    QCoreApplication *application = nullptr;
    std::unique_ptr<QCommandLineParser> parser;

    CommandLineParserPrivate(QCoreApplication *currentApplication)
        : application(currentApplication)
        , parser(std::make_unique<QCommandLineParser>())
    {}

private:
    CommandLineParserPrivate(const CommandLineParserPrivate &) = delete;
    CommandLineParserPrivate(CommandLineParserPrivate &&)      = delete;
    CommandLineParserPrivate &operator=(const CommandLineParserPrivate &) = delete;
    CommandLineParserPrivate &operator=(CommandLineParserPrivate &&) = delete;
};

CommandLineParser::CommandLineParser(QCoreApplication *application)
    : d(new CommandLineParserPrivate(application))
{}

CommandLineParser::~CommandLineParser()
{
    delete d;
}

CommandLineParser::CommandLineParseResult CommandLineParser::parseCommandLine(CommandLineOptions *options,
                                                                              QString *errorMessage)
{
    const QCommandLineOption helpOption = d->parser->addHelpOption();

    const QCommandLineOption versionOption = d->parser->addVersionOption();

    const QCommandLineOption port(QStringList() << "p"
                                                << "port",
                                  "Specifies the port for the request. If not specified, 11123 will be used.",
                                  "port");

    const QCommandLineOption address(
        QStringList() << "a"
                      << "address",
        "Specifies the ip4 address for the request [address]. If not specified, address of localhost will be used.",
        "address");

    const QCommandLineOption resourceName(QStringList() << "r"
                                                        << "resource",
                                          "Specifies the resource name for the request [address].",
                                          "address");

    d->parser->setSingleDashWordOptionMode(QCommandLineParser::ParseAsLongOptions);
    d->parser->addOption(port);
    d->parser->addOption(address);
    d->parser->addOption(resourceName);

    if (!d->parser->parse(d->application->arguments()))
    {
        *errorMessage = d->parser->errorText();
        return CommandLineError;
    }

    if (d->parser->isSet(versionOption))
    {
        return CommandLineVersionRequested;
    }

    if (d->parser->isSet(helpOption))
    {
        return CommandLineHelpRequested;
    }

    if (d->parser->isSet(port))
    {
        QString sPort = d->parser->value(port);
        if (sPort.isNull() || sPort.isEmpty())
        {
            return CommandLineError;
        }

        bool ok_flag  = false;
        options->port = sPort.toUInt(&ok_flag);
        if (!ok_flag)
        {
            options->port = 0;
            *errorMessage = "Port is invalid. See help.";
            return CommandLineError;
        }
    }

    if (d->parser->isSet(address))
    {
        const QString sendAddress = d->parser->value(address);
        if (sendAddress.isNull() || sendAddress.isEmpty())
        {
            return CommandLineError;
        }

        if (!options->address.setAddress(sendAddress))
        {
            *errorMessage = "Port is invalid. See help.";
            return CommandLineError;
        }
    }

    if (d->parser->isSet(resourceName))
    {
        options->resourceName = d->parser->value(resourceName);
        QString sendAddress   = d->parser->value(address);
        if (options->resourceName.isNull() || options->resourceName.isEmpty())
        {
            *errorMessage = "Resource name is invalid.";
            return CommandLineError;
        }

        return CommandLineOk;
    }

    *errorMessage = "No resource name is specified! See help.";
    return CommandLineError;
}

void CommandLineParser::showHelp(int exitCode)
{
    d->parser->showHelp(exitCode);
}

void CommandLineParser::showVersion()
{
    d->parser->showVersion();
}

} // namespace udpclient
