#include <QCoreApplication>

#include "commandlineparser/commandlineparser.h"
#include "udpserverexample.h"

int main(int argc, char *argv[])
{
    //Created just to parse arguments with the built-in parser
    QCoreApplication app(argc, argv);

    app.setOrganizationName("Example Corp.");
    app.setOrganizationDomain("examplecorp.com");
    app.setApplicationName("UDPServerExample");
    app.setApplicationVersion("0.0.1");

    udpserver::UDPServerExample server(app);

    return server.run();
}
