#include "serverconnect.h"
#include <QDebug>

ServerConnect::ServerConnect(const char *ip, unsigned int port)
{
    _isallowcall = false;
    _iscalling = false;

    connect(&_socket_control, SIGNAL(connected()), this, SLOT(slotConnected()));
    connect(&_socket_control, SIGNAL(disconnected()), this, SLOT(slotDisconnected()));
    connect(&_socket_control, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotError(QAbstractSocket::SocketError)));
    connect(&_socket_control, SIGNAL(readyRead()), this, SLOT(slotReadyread()));
    //
    connect(&_timer_heart, SIGNAL(timeout()), this, SLOT(slotTimeout()));

    //取消原有连接
    _socket_control.abort();
    _socket_control.connectToHost("172.16.70.133", 45450);
    //_socket_control.connectToHost("172.16.70.13", 20000);
    _socket_control.waitForConnected();
    //
    _timer_heart.start(6000);
}

ServerConnect::~ServerConnect()
{

}

void ServerConnect::slotConnected()
{
    qDebug() << "socket connect";
    const char* sendtext = "{\"type\":\"REGISTER\",\"sn\":\"chenp_YT327L\"}@";
    sendData(sendtext, strlen(sendtext));
}

void ServerConnect::slotDisconnected()
{

}

void ServerConnect::slotError(QAbstractSocket::SocketError socketError)
{
    qDebug() << "socket error " << _socket_control.errorString();
}

void ServerConnect::slotReadyread()
{
    QByteArray readtxt = _socket_control.readAll();
    unsigned int len = readtxt.length();

    if (1==len)
        return ;

    for (unsigned int i=0;i<len;i++) {
        if ('@'==readtxt[i]) {
            readtxt.remove(i, 1);
            len--;
            i--;
        }
    }

    qDebug() << "recv:" << readtxt;

    cJSON* root = cJSON_Parse(readtxt.data());
    if (NULL==root) {
        qDebug() << "read json format error";
        return ;
    }

    doServerMsg(cJSON_GetObjectItem(root, "type")->valuestring, root);

    cJSON_Delete(root);
    root = NULL;
}

void ServerConnect::slotTimeout()
{
    char sendtext[64] = {0};
    snprintf(sendtext, sizeof(sendtext), "{\"type\":\"HEART\",\"token\":\"%d\"}@", _peer_id);
    sendData(sendtext, strlen(sendtext));

    if (!_iscalling && _isallowcall) {
        snprintf(sendtext, sizeof(sendtext), "{\"type\":\"CALL\",\"token\":\"%d\"}@", _peer_id);
        sendData(sendtext, strlen(sendtext));
    }
}

void ServerConnect::sendData(const char *text, unsigned int len)
{
    if (!_lock_socket.tryLock(100))
            return ;
    _socket_control.write(text, len);
    _lock_socket.unlock();
}

void ServerConnect::doServerMsg(const char* type, cJSON* root)
{
    //qDebug() << "type " << type;
    if (!strncmp(type, "RE_HEART", strlen(type)+1)) {
        // 心跳返回
    } else if (!strncmp(type, "RE_REGISTER", strlen(type)+1)) {
        // 注册返回
        const char* token = cJSON_GetObjectItem(root, "token")->valuestring;
        qDebug() << "token:" << token;
        memset(_peer_id, 0, sizeof(_peer_id));
        memcpy(_peer_id, token, strlen(token));
        // 呼叫
        _isallowcall = true;
    } else if (!strncmp(type, "RE_CALL", strlen(type)+1)) {
        // 呼叫命令
        const char* state = cJSON_GetObjectItem(root, "state")->valuestring;
        qDebug() << "state:" << state;
    } else if (!strncmp(type, "RE_BASICS_SETTING", strlen(type)+1)) {
        // 服务下发一些配置
    } else if (!strncmp(type, "RE_GET_OFFER", strlen(type)+1)) {
        // 服务下发offer
    } else if (!strncmp(type, "RE_ANSWER", strlen(type)+1)) {
        // 服务下发answer
    } else if (!strncmp(type, "OPEN_DOOR", strlen(type)+1)) {
        // 挂断，开门
        _isallowcall = false;
        char sendtext[64] = {0};
        snprintf(sendtext, sizeof(sendtext), "{\"type\":\"RE_OPEN_DOOR\",\"token\":\"%d\"}@", _peer_id);
        sendData(sendtext, strlen(sendtext));
    } else if (!strncmp(type, "HANGUP", strlen(type)+1)) {
        // 挂断，开门
        _isallowcall = false;
        char sendtext[64] = {0};
        snprintf(sendtext, sizeof(sendtext), "{\"type\":\"RE_HANGUP\",\"token\":\"%d\"}@", _peer_id);
        sendData(sendtext, strlen(sendtext));
    } else
        qDebug() << "type invalid:" << type;
}
