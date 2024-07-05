#include "serversmanager.h"
#include "stftpd.h"

ServersManager::ServersManager(QObject *parent) : QObject(parent)
{
    AddServer("STftpd", new STftpd);
}

ServersManager::~ServersManager()
{
    // 清理map
    foreach(SBase* item, _serverlist)
        delete  item;
    _serverlist.clear();
}

void ServersManager::StartServer(const QString &serverName)
{
    SBase* server = _serverlist[serverName];
    if (nullptr!=server)
        server->ServerStart();
}

void ServersManager::StopServer(const QString &serverName)
{
    SBase* server = _serverlist[serverName];
    if (nullptr!=server)
        server->ServerStop();
}

void ServersManager::AddServer(const QString &name, SBase *server)
{
    if (_serverlist.contains(name))
        return ;

    _serverlist[name] = server;
}
