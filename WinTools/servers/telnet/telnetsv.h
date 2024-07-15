#ifndef TELNETSV_H
#define TELNETSV_H
#include <QtTelnet>

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

    int ExeCommond(const QString& cmd);

signals:
    void RelyMsg(const QString& msg);

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
};

#endif // TELNETSV_H
