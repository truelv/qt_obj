#ifndef SERVERCONNECT_H
#define SERVERCONNECT_H

#include <QObject>
#include <QTcpSocket>
#include <QMutex>
#include <QTimer>

#include "cJSON.h"

class ServerConnect: public QObject
{
    Q_OBJECT
public:
    ServerConnect(const char* ip = NULL, unsigned int port = 0);
    ~ServerConnect();

private Q_SLOTS:
    void slotConnected();
    void slotDisconnected();
    void slotError(QAbstractSocket::SocketError socketError);
    void slotReadyread();
    //
    void slotTimeout();


private:
    QTcpSocket _socket_control;
    QMutex _lock_socket;
    QTimer _timer_heart;
    // d4495645-dd75-4c4c-811e-6c1fa3e97966 36byte
    unsigned char _peer_id[40];
    //
    bool _isallowcall;
    bool _iscalling;

    void sendData(const char* text, unsigned int len);
    void doServerMsg(const char *type, cJSON *root);
};

#endif // SERVERCONNECT_H
