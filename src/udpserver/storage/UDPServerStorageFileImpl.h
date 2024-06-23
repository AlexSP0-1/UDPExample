#ifndef _UDP_SERVER_STORAGE_FILE_IMPL_H
#define _UDP_SERVER_STORAGE_FILE_IMPL_H

#include "storage/UDPServerStorageInterface.h"

#include <memory>

namespace udpserver
{
class UDPServerStorageFileImplPrivate;

class UDPServerStorageFileImpl : public UDPServerStorageInterface
{
public:
    UDPServerStorageFileImpl(QString filename);
    ~UDPServerStorageFileImpl() override;

    QString getResource(QString resourceName) override;

    void update() override;

    bool isValid() override;

private:
    std::unique_ptr<UDPServerStorageFileImplPrivate> d;

private:
    void parseLine(std::string &line);

private:
    UDPServerStorageFileImpl(const UDPServerStorageFileImpl &) = delete;
    UDPServerStorageFileImpl(UDPServerStorageFileImpl &&)      = delete;
    UDPServerStorageFileImpl &operator=(const UDPServerStorageFileImpl &) = delete;
    UDPServerStorageFileImpl &operator=(UDPServerStorageFileImpl &&) = delete;
};
} // namespace udpserver

#endif //_UDP_SERVER_STORAGE_FILE_IMPL_H
