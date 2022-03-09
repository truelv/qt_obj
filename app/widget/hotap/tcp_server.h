/**
 * tcp服务，单连接，接收到第一包数据进入工作模式
 * 工作模式有5种模式，
 * 空闲，升级应用，获取日志，添加人脸特征码（图片方式），添加人脸特征码（特征码方式）
 * 一旦服务获取连接并接收到首包，进入相应模式，
 * 在服务空闲之前，接收到其他包，重新进入空闲
*/

#ifndef TCP_SERVER_H
#define TCP_SERVER_H
#ifdef __cplusplus
extern "C" {
#endif
#include "protocol/tcp/hotapSocket.h"
#ifdef __cplusplus
}
#endif

#include <QThread>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>


#define ACK_INVALIDE -1

typedef enum {
    TCPSERVER_BUSY,
    TCPSERVER_IDEL,
    TCPSERVER_UPAPP,
    TCPSERVER_GETLOG,
    TCPSERVER_FEATDN,
    TCPSERVER_IMGDN,
    TCPSERVER_IMGSDN,
    TCPSERVER_FACEDEL,
    TCPSERVER_THREAD_FEATIMGS,
    TCPSERVER_THREAD_FEATIMG,
    TCPSERVER_THREAD_FEAT,
    TCPSERVER_THREAD_FILEUP,
} TCPSERVER_MODE;

class Tcp_Server : public QThread
{
    Q_OBJECT
public:
    explicit Tcp_Server(QThread *parent = 0);
    void startServer();
    void stopServer();

protected:
    // ack根据当前的传输信息发
    void sendAck(const char ackcode);
    void sendReq(unsigned short order);
    // 处理ack
    int recvAck(const PROTOCOL_SOCKET_ACK* ack);
    // 处理首包
    void firstPkg(const PROTOCOL_SOCKET_REQUEST *pkg);
    // 处理首包日志
    void sendFirstLogPkg();
    // 处理数据，写文件
    void storeRequestData(const PROTOCOL_SOCKET_REQUEST *req);
    int storeFileSuccess(const PROTOCOL_SOCKET_REQUEST *req);
    // 复位缓存
    void resetReadBuffer();
    // 复位文件
    void resetSendFile();

    void run();

signals:
    // 服务启动/关闭
    void signalTcpServerStart(bool on);
    // tcp连接/关闭
    void signalTcpConnected(bool on);
    // 开始传输
    void signalTcpReadStart(int type);
    // 结束传输
    void signalTcpReadOver(int type);
    // 传输进度
    void signalTcpReadProgress(int progress);
    //
    void signalWorkDone(int type);
    // 传包失败
    void signalTransFailed();
    // 包校验失败
    void signalCrcCheckFailed();


protected slots:
    void slotNewConnection();
    void slotSocketDisconnect();
    void slotReadyRead();

private:
    QTcpServer _tcpServer;
    QTcpSocket* _socket;
    TCPSERVER_MODE _mode;
    PROTOCOL_SOCKET_TRANSFERINFO _transInfo;
    unsigned short _pkg_crc16;
    // tcp读缓存
    PROTOCOL_SOCKET_REQUEST* _readBuffer;
    // 缓存偏移
    int _bufferOffset;
    // 缓存余量
    int _bufferLeft;
    // 是否在拼包
    bool _isPacket;
    // 传输文件
    QFile* _file;
};

#endif // TCP_SERVICE_H
