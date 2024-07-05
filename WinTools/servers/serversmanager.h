#ifndef SERVERSMANAGER_H
#define SERVERSMANAGER_H
// 集中管理服务，监听服务状态，并通广播改变
#include <QObject>
#include <QMap>
#include "sbase.h"

class ServersManager : public QObject
{
    Q_OBJECT
public:
    explicit ServersManager(QObject *parent = nullptr);
    ~ServersManager();

    //
    void StartServer(const QString& serverName);
    void StopServer(const QString& serverName);

signals:

private:
    QMap<QString, SBase*> _serverlist;
    void AddServer(const QString& name, SBase* server);

};

#endif // SERVERSMANAGER_H
