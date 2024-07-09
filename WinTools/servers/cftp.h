#ifndef CFTP_H
#define CFTP_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QFile>

// 客户端，命令通道
// 这个客户端将定义为，一个命令建立一个对象，
// 命令执行完成，不管是成功或者失败，都清理所有的资源
class Cftp : public QObject
{
    Q_OBJECT
public:
    explicit Cftp(QTcpSocket* sck = 0, QObject *parent = nullptr);
    ~Cftp();

    void Reply(const QString &replyCode);

signals:

protected slots:
    // Cftp slot
    void SlotConnectlost();
    void SlotReadready();
    //*****************************
    // 新的数据通断请求
    void SlotDataConnect();
    // 数据可读处理
    void SlotRecvdata();
    // 数据写完成处理
    void SlotSendFrameOK(qint64 bytes);
    // 数据传输中断
    void SlotAborddata();

private:
    QTcpSocket* _sck;
    void ParseCommond(const QString& cmd);
    void parseCommand(const QString &entireCommand, QString *command, QString *commandParameters);
    // 标记客户端是否登录了
    bool _logined;
    // data
    QTcpServer* _dataServer;
    QTcpSocket* _dataSock;
    // 数据通道，上传或者下发的文件
    QFile* file;

};

#endif // CFTP_H
