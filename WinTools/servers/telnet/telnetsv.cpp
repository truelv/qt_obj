#include "telnetsv.h"

//TelnetSV* TelnetSV::_intent = NULL;
TelnetSV::TelnetSV(const QString& ip):
    _logined(false)
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
}

void TelnetSV::SlotRecvMsg(const QString &data)
{
    qDebug() << "recv telnet " << data;
    if (data.contains("login:"))
    {
        _tel->sendData("root\r\n");
        return ;
    }
    else if (data.contains("Password"))
    {
        _tel->sendData("zytk@310012\r\n");
        return ;
    }

    //
    emit RelyMsg(data);
}
