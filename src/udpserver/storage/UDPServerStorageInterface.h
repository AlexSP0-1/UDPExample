#ifndef _UDP_SERVER_STORAGE_INTERFACE_H
#define _UDP_SERVER_STORAGE_INTERFACE_H

#include <QString>
namespace udpserver
{
class UDPServerStorageInterface
{
public:
    virtual ~UDPServerStorageInterface() = default;

    virtual QString getResource(QString resourceName) = 0;

    virtual void update() = 0;

    virtual bool isValid() = 0;
};
} // namespace udpserver

#endif //_UDP_SERVER_STORAGE_INTERFACE_H
