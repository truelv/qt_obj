#ifndef STFTPD_H
#define STFTPD_H
#include "sbase.h"
#include <QTcpServer>
#include <QTcpSocket>

class STftpd: public SBase
{
    Q_OBJECT
public:
    STftpd();
    ~STftpd();

    int ServerStart() override;
    int ServerStop() override;

    // 客户端退出回调
    int CFtpQuit();
    int CFtpDisConnect();

protected slots:
    void SlotNewconnect();

private:
    // ftp参数
    QString _ip;
    quint16 _port;
    // ftp服务，长期存在
    QTcpServer _server;
};
#endif // STFTPD_H
