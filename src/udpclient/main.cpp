#include "udpclientexample.h"

#include <QCoreApplication>

int main(int argc, char *argv[])
{
    //Created only for the use of the library parser
    QCoreApplication app(argc, argv);

    app.setOrganizationName("Example Corp.");
    app.setOrganizationDomain("examplecorp.com");
    app.setApplicationName("UDPClientExample");
    app.setApplicationVersion("0.0.1");

    udpclient::UDPClientExample client(app);
    client.run();

    return app.exec();
}
