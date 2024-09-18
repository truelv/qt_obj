#ifndef TELNETSV_H
#define TELNETSV_H
#include <QtTelnet>
#include <QSemaphore>
#include "../sbase.h"
#include "modTelnet/QtTelnet"

class TelnetSV: public SBase
{
    Q_OBJECT
public:
    TelnetSV(const QString &ip);
    ~TelnetSV();

    int ServerStart() override;
    int ServerStop() override;

    // 执行命令，异步方式
    int ExeCommond(const QString& cmd);
    // 执行命令，同步方式
    // 用这个接口，需要自己控制2个同步命令的时机，以免冲突
    int ExeCommondWait(const QString& cmd, QString *rely, int ms);

signals:
    void RelyMsg(const QString& msg);
    void Logout();

protected slots:
    void SLotLoginreq();
    void SlotLoginFailed();
    void SlotLogin();
    void SLotLogout();
    void SlotConnectErr(QAbstractSocket::SocketError error);
    void SlotRecvMsg(const QString &data);

private:
    bool _logined;
    QtTelnet* _tel;
    //static TelnetSV* _intent;
    // 计数登录次数
    int _loginCount;
    int _passCount;
    // 同步接收数据的信号
    QSemaphore _sem;
    QString _cmdWait;
    QString* _recvMsg;
};

#endif // TELNETSV_H
