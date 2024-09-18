#include "telnetsv.h"

//TelnetSV* TelnetSV::_intent = NULL;
TelnetSV::TelnetSV(const QString& ip):
    _logined(false),_loginCount(0),_passCount(0)
{
    _tel = new QtTelnet;
    connect(_tel, &QtTelnet::loginRequired, this, &TelnetSV::SLotLoginreq);
    connect(_tel, &QtTelnet::loginFailed, this, &TelnetSV::SlotLoginFailed);
    connect(_tel, &QtTelnet::loggedIn, this, &TelnetSV::SlotLogin);
    connect(_tel, &QtTelnet::loggedOut, this, &TelnetSV::SLotLogout);
    connect(_tel, &QtTelnet::connectionError, this, &TelnetSV::SlotConnectErr);
    connect(_tel, &QtTelnet::message, this, &TelnetSV::SlotRecvMsg);

    //_tel->setLoginString("root");
    //_tel->setPasswordString("zytk@310012");
    //_tel->login("root", "zytk@310012");
    _tel->connectToHost(ip);
    //_tel->sendData("root");

    // 清空sem
    int n = _sem.available();
    _sem.acquire(n);
    _cmdWait.clear();
    _recvMsg = nullptr;
}

TelnetSV::~TelnetSV()
{
    _tel->logout();
    _tel->close();
    disconnect(_tel, &QtTelnet::message, this, &TelnetSV::SlotRecvMsg);
    delete _tel;
}

int TelnetSV::ServerStart()
{
    return 0;
}

int TelnetSV::ServerStop()
{
    return 0;
}

int TelnetSV::ExeCommond(const QString &cmd)
{
    qDebug() << "exe " << cmd;
    _tel->sendData(cmd+QString("\r\n"));
    return 0;
}

#include <QCoreApplication>
/**
 * @brief TelnetSV::ExeCommondWait
 * @param cmd   执行命令
 * @param rely  返回内容
 * @param ms    超时时间
 * @return
 */
int TelnetSV::ExeCommondWait(const QString &cmd, QString* rely, int ms)
{
    qDebug() << "exe " << cmd;
    if (nullptr==rely || ms<50)
    {
        qDebug() << "rely is null";
        return -1;
    }

    if (!_cmdWait.isEmpty())
    {
        qDebug() << "cmd not null";
        return -2;
    }

    _cmdWait = cmd;
    _recvMsg = rely;
    _tel->sendData(cmd+QString("\r\n"));
    QCoreApplication::processEvents();

#if 1
    // wait
    int n = ms/50;
    while (n>0 && !_sem.tryAcquire(1,50)) {
        n--;
        QCoreApplication::processEvents();
    }

    if (n<=0)
    {
        qDebug() << "wait rely timeout";
        _cmdWait.clear();
        _recvMsg = nullptr;
        return -3;
    }
#endif

    _cmdWait.clear();
    _recvMsg = nullptr;
    return 0;
}

void TelnetSV::SLotLoginreq()
{
    qDebug() << "SLotLoginreq";
}

void TelnetSV::SlotLoginFailed()
{
    qDebug() << "SlotLoginFailed";
}

void TelnetSV::SlotLogin()
{
    qDebug() << "SlotLogin";
}

void TelnetSV::SLotLogout()
{
    qDebug() << "SLotLogout";
}

void TelnetSV::SlotConnectErr(QAbstractSocket::SocketError error)
{
    qDebug() << "SlotConnectErr";
    emit Logout();
}

// 这里同步消息，如果超时后才返回，就当一般消息处理
void TelnetSV::SlotRecvMsg(const QString &data)
{
    if (!_cmdWait.isEmpty())
    {
        qDebug() << "recv sync telnet " << data;
        _recvMsg->append(data);
        _sem.release(1);
        return ;
    }

    qDebug() << "recv telnet " << data;
    if (data.contains("login:"))
    {
        _tel->sendData("root\r\n");
        return ;
    }

    if (data.contains("Password"))
    {
        if (0==_passCount)
            _tel->sendData("zytk@310012\r\n");
        else if (1==_passCount)
            _tel->sendData("zytk\r\n");

        _passCount ++;
        return ;
    }

    //
    emit RelyMsg(data);
}
