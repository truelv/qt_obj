#include "stftpd.h"
#include "cftp.h"

STftpd::STftpd()
{
    qDebug() << "create STftpd";
    // ftp默认端口是21
    _port = 21;
    // 监听服务状态
    connect(&_server, SIGNAL(newConnection()), this, SLOT(SlotNewconnect()));
}

STftpd::~STftpd()
{
    disconnect(&_server, SIGNAL(newConnection()), this, SLOT(SlotNewconnect()));
}

int STftpd::ServerStart()
{
    if (_server.listen(QHostAddress::AnyIPv4, _port))
    {
        return 0;
    }

    return -1;
}

int STftpd::ServerStop()
{
    _server.close();
}

void STftpd::SlotNewconnect()
{
    // 对于新的连接，获取socket，然后加入监听
    QTcpSocket* sck = _server.nextPendingConnection();
    qDebug() << "a new ftp connect";
    // 对于每个客户端的连接，使用一个Cftp表示
    new Cftp(sck);
}

