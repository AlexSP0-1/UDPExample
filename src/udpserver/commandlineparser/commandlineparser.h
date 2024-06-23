#ifndef _UDP_SERVER_COMMAND_LINE_PARSER_H
#define _UDP_SERVER_COMMAND_LINE_PARSER_H

#include "commandlineoptions.h"

#include <QCoreApplication>

namespace udpserver
{
class CommandLineParserPrivate;

class CommandLineParser
{
public:
    enum CommandLineParseResult
    {
        CommandLineOk,
        CommandLineError,
        CommandLineVersionRequested,
        CommandLineHelpRequested,
    };

public:
    CommandLineParser(QCoreApplication *application);
    ~CommandLineParser();

    CommandLineParseResult parseCommandLine(CommandLineOptions *options, QString *errorMessage);

    void showHelp(int exitCode);
    void showVersion();

private:
    CommandLineParser(const CommandLineParser &) = delete;
    CommandLineParser(CommandLineParser &&)      = delete;
    CommandLineParser &operator=(const CommandLineParser &) = delete;
    CommandLineParser &operator=(CommandLineParser &&) = delete;

private:
    CommandLineParserPrivate *d;
};

} // namespace udpserver

#endif //_UDP_SERVER_COMMAND_LINE_PARSER_H
