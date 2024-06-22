#ifndef _UDP_SERVER_STORAGE_FILE_IMPL_H
#define _UDP_SERVER_STORAGE_FILE_IMPL_H

#include "storage/UDPServerStorageInterface.h"

namespace udpserver
{
class UDPServerStorageFileImpl : public UDPServerStorageInterface
{
    QString getResource(QString resourceName) override;
};
} // namespace udpserver

#endif //_UDP_SERVER_STORAGE_FILE_IMPL_H
