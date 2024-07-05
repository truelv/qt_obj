#include "serverconnectbase.h"
#include "rtppeerconnect.h"

ServerConnectBase* ServerConnectBase::_intent = NULL;
ServerConnectBase::ServerConnectBase(rtc::scoped_refptr<RtpPeerConnect> rtp):
    _rtppeer(rtp)
{
    connect(this, SIGNAL(signalSendsocket(const char*,unsigned int,bool)),
            this, SLOT(slotSendsocket(const char*, unsigned int,bool)));
    //
    connect(&_socket_control, SIGNAL(connected()), this, SLOT(slotConnected()));
    connect(&_socket_control, SIGNAL(disconnected()), this, SLOT(slotDisconnected()));
    connect(&_socket_control, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotError(QAbstractSocket::SocketError)));
    connect(&_socket_control, SIGNAL(readyRead()), this, SLOT(slotReadyread()));
    //取消原有连接
    _socket_control.abort();
    _socket_control.connectToHost("172.16.70.183", 8888);
    _socket_control.waitForConnected();
}

ServerConnectBase *ServerConnectBase::getIntent(rtc::scoped_refptr<RtpPeerConnect> rtp)
{
    if (NULL==_intent)
        _intent = new ServerConnectBase(rtp);
    return _intent;
}

ServerConnectBase *ServerConnectBase::getIntent()
{
    return _intent;
}

ServerConnectBase::~ServerConnectBase()
{
    _intent = NULL;
}

void ServerConnectBase::slotConnected()
{
    qDebug() << "socket connect";
    const char* sendtext = "GET /sign_in?cp@ubuntu11 HTTP/1.0\r\n\r\n";
    sendData(sendtext, strlen(sendtext));
}

void ServerConnectBase::slotDisconnected()
{

}

void ServerConnectBase::slotError(QAbstractSocket::SocketError socketError)
{

}

void ServerConnectBase::slotReadyread()
{
    const QByteArray& readtxt = _socket_control.readAll();
    unsigned int len = readtxt.length();
    qDebug() << "recv:" << readtxt;
    getSigonMsg(readtxt);
    getWaitonMsg(readtxt);
}

void ServerConnectBase::slotSendsocket(const char *text, unsigned int len, bool run)
{
    if (!_lock_socket.tryLock(100)) {
        qDebug() << "lock socket error";
        return ;
    }
    _socket_control.write(text, len);
    _lock_socket.unlock();
    free((void*)text);
    text = NULL;
    _socket_control.waitForBytesWritten(1000);
    //
    if (run)
        _rtppeer->connectPeer();
}

void ServerConnectBase::sendData(const char *text, unsigned int len)
{
    if (!_lock_socket.tryLock(100)) {
        qDebug() << "lock socket error";
        return ;
    }
    qDebug() << "send by socket";
    _socket_control.write(text, len);
    _lock_socket.unlock();
    _socket_control.waitForBytesWritten(1000);
}

void ServerConnectBase::sendSignalSendsocket(const char *text, unsigned int len)
{
    Q_EMIT signalSendsocket(text, len, false);
}

void ServerConnectBase::getSigonMsg(const QByteArray &readtxt)
{
    int pos_h = readtxt.indexOf(" ");
    if (-1==pos_h) {
        qDebug() << "http resp status not fond";
        return ;
    }

    int pos_t = readtxt.indexOf(" ", pos_h+1);
    int status = atoi(readtxt.mid(pos_h+1, pos_t-pos_h-1).data());
    //qDebug() << "http resp status:" << status;
    if (200!=status) {
        qDebug() << "http resp status not 200";
        return ;
    }

    //
    pos_h = pos_t;
    pos_t = readtxt.indexOf("\r\n", pos_h+1);
    //qDebug() << pos_h << pos_t;
    const QByteArray& method = readtxt.mid(pos_h+1, pos_t-pos_h-1);
    //qDebug() << "method:" << method;
    if (strncmp(method, "Added", method.size())) {
        return ;
    }

    pos_h = readtxt.indexOf("\r\nPragma: ");
    if (-1==pos_h) {
        qDebug() << "http resp Pragma not fond";
        return ;
    }

    pos_t = readtxt.indexOf("\r\n", pos_h+10);
    _peer_id = atoi(readtxt.mid(pos_h+10, pos_t-pos_h-1).data());
    qDebug() << "http resp _peer_id:" << _peer_id;

    //
    char* sendbuff = (char*)calloc(1,64);
    snprintf(sendbuff, 64, "GET /wait?peer_id=%i HTTP/1.0\r\n\r\n", _peer_id);
    Q_EMIT signalSendsocket(sendbuff, strlen(sendbuff), true);
}

void ServerConnectBase::getWaitonMsg(const QByteArray &readtxt)
{
    int pos_h = readtxt.indexOf(" ");
    if (-1==pos_h) {
        qDebug() << "http resp status not fond";
        return ;
    }

    int pos_t = readtxt.indexOf(" ", pos_h+1);
    int status = atoi(readtxt.mid(pos_h+1, pos_t-pos_h-1).data());
    //qDebug() << "http resp status:" << status;
    if (200!=status) {
        qDebug() << "http resp status not 200";
        return ;
    }
}
