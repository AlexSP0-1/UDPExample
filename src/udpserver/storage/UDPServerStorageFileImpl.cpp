#include "UDPServerStorageFileImpl.h"

#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <iostream>
#include <shared_mutex>
#include <QHash>

namespace udpserver
{
class UDPServerStorageFileImplPrivate
{
public:
    UDPServerStorageFileImplPrivate(QString filename)
        : m_isValid(false)
        , m_filename(filename)
        , m_resources{}
        , m_mutex(std::make_unique<std::shared_mutex>())
    {}

    ~UDPServerStorageFileImplPrivate() {}
    bool m_isValid;

    QHash<QString, QString> m_resources;

    QString m_filename;

    std::unique_ptr<std::shared_mutex> m_mutex;
};

UDPServerStorageFileImpl::UDPServerStorageFileImpl(QString filename)
    : d(std::make_unique<UDPServerStorageFileImplPrivate>(filename))
{}

UDPServerStorageFileImpl::~UDPServerStorageFileImpl() {}

QString UDPServerStorageFileImpl::getResource(QString resourceName)
{
    //Try to lock mutex for reading, not for writing
    std::shared_lock<std::shared_mutex>(*d->m_mutex.get());

    auto it = d->m_resources.find(resourceName);
    if (it == d->m_resources.end())
        return NULL;

    return it.value();
}

void UDPServerStorageFileImpl::update()
{
    //Try to lock mutex only for writing
    std::lock_guard<std::shared_mutex>(*d->m_mutex.get());

    d->m_resources.clear();

    std::string line;
    std::ifstream file(d->m_filename.toStdString());

    if (!file)
    {
        d->m_isValid = false;
        return;
    }

    while (getline(file, line))
    {
        parseLine(line);
    }

    //destructor of ifstream can close the file itself, however, for better understanding, it is better to close explicitly
    file.close();

    d->m_isValid = true;
}

bool UDPServerStorageFileImpl::isValid()
{
    return d->m_isValid;
}

void UDPServerStorageFileImpl::parseLine(std::string &line)
{
    QString currentLine(line.c_str());
    QStringList words = currentLine.split(" ", Qt::SkipEmptyParts);

    if (words.size() < 2)
        return;

    QString key(words.at(0));

    QString value(words.at(1));

    //Appends all words to value
    if (words.size() > 2)
    {
        for (int i = 2; i < words.size(); i++)
        {
            value.append(QString(" " + words.at(i)));
        }
    }

    d->m_resources.insert(key, value);
}
} // namespace udpserver
