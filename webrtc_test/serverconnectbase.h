#ifndef SERVERCONNECTBASE_H
#define SERVERCONNECTBASE_H

#include <QObject>
#include <QTcpSocket>
#include <QMutex>
#include "rtppeerconnect.h"

class ServerConnectBase: public QObject
{
    Q_OBJECT
public:
    static ServerConnectBase *getIntent(rtc::scoped_refptr<RtpPeerConnect> rtp);
    static ServerConnectBase *getIntent();
    virtual ~ServerConnectBase();
    //
    void sendData(const char* text, unsigned int len);
    int id() {return _peer_id;}
    void sendSignalSendsocket(const char* text, unsigned int len);

Q_SIGNALS:
    void signalSendsocket(const char* text, unsigned int len, bool run);

private Q_SLOTS:
    void slotConnected();
    void slotDisconnected();
    void slotError(QAbstractSocket::SocketError socketError);
    virtual void slotReadyread();
    // 异步socket发送数据
    void slotSendsocket(const char* text, unsigned int len, bool run);

private:
    QTcpSocket _socket_control;
    QMutex _lock_socket;
    //
    int _peer_id;
    //
    void getSigonMsg(const QByteArray& readtxt);
    void getWaitonMsg(const QByteArray& readtxt);
    //
    static ServerConnectBase* _intent;
    ServerConnectBase(rtc::scoped_refptr<RtpPeerConnect> rtp);

    rtc::scoped_refptr<RtpPeerConnect> _rtppeer;
};

#endif // SERVERCONNECTBASE_H
