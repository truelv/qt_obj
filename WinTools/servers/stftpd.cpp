#include "stftpd.h"
#include "cftp.h"
#include "globalsignal.h"

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
        GlobalSignal::GetInstance()->SendSigSftpSta(SFTP_STA_OK);
        return 0;
    }

    // 启动ftp服务失败
    GlobalSignal::GetInstance()->SendSigSftpSta(SFTP_STA_OPEN_FAILE);
    return -1;
}

int STftpd::ServerStop()
{
    _server.close();
    return 0;
}

int STftpd::CFtpQuit()
{
    qDebug() << "a ftp connect quit()";
    return 0;
}

int STftpd::CFtpDisConnect()
{
    qDebug() << "a ftp disconnect";
    GlobalSignal::GetInstance()->SendSigCftpEnd();
    return 0;
}

void STftpd::SlotNewconnect()
{
    // 对于新的连接，获取socket，然后加入监听
    QTcpSocket* sck = _server.nextPendingConnection();
    qDebug() << "a new ftp connect";
    // 对于每个客户端的连接，使用一个Cftp表示
    new Cftp(sck, this);
}

