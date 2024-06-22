#include "commandlineparser/commandlineparser.h"

#include <memory>
#include <QCommandLineParser>

namespace udpserver
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

    const QCommandLineOption listenPort(QStringList() << "p"
                                                      << "port",
                                        "Specify port to listen.",
                                        "port");

    const QCommandLineOption resourceFile(QStringList() << "f"
                                                        << "file",
                                          "Gets resourcves from <file>",
                                          "file");

    d->parser->setSingleDashWordOptionMode(QCommandLineParser::ParseAsLongOptions);
    d->parser->addOption(listenPort);
    d->parser->addOption(resourceFile);

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

    if (d->parser->isSet(resourceFile))
    {
        const QString filename = d->parser->value(resourceFile);

        if (filename.isNull() || filename.isEmpty())
        {
            *errorMessage = "Specify the resource file! See help!";
            return CommandLineError;
        }
        options->resourcePath = filename;

        if (d->parser->isSet(listenPort))
        {
            QString port = d->parser->value(listenPort);
            if (port.isNull() || port.isEmpty())
            {
                return CommandLineError;
            }

            bool ok_flag  = false;
            options->port = port.toUInt(&ok_flag);
            if (!ok_flag)
            {
                options->port = 0;
                *errorMessage = "Port is invalid. See help.";
                return CommandLineError;
            }
        }

        return CommandLineOk;
    }

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

} // namespace udpserver
