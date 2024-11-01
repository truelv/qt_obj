#include "cftp.h"
#include <QTimer>
#include <QString>
#include <QHostAddress>
#include <QFileInfo>
#include <QCoreApplication>
#include "stftpd.h"

//#define FTP_ROOT "C:\\Users\\40428\\Desktop\\"
#define FTP_ROOT "\\file\\"

Cftp::Cftp(QTcpSocket* sck, QObject* sftp, QObject* parent) : QObject(parent), _sck(sck),
    _logined(false), _dataSock(nullptr), file(nullptr), _sftp(sftp)
{
    // 客户端连接建立后，监听连接状态和命令
    connect(_sck, SIGNAL(disconnected()), this, SLOT(SlotConnectlost()));
    connect(_sck, SIGNAL(readyRead()), this, SLOT(SlotReadready()));

    // 同时建立，准备数据通道，数据通道将另外建立的tcp服务提供
    _dataServer = new QTcpServer;
    // 等待数据通道真正建立，等到 收到 PASV 命令后才监听 数据通道连接
    connect(_dataServer, &QTcpServer::newConnection, this, &Cftp::SlotDataConnect);
    // 回复ftp服务已经建立好，让客户端知道
    Reply("220 Welcome to QFtpServer.");
}

Cftp::~Cftp()
{
    // 如果已经建立数据通道，需要回收
    if(nullptr != file)
    {
        delete file;
        file = nullptr;
    }
    if(nullptr != _dataSock)
    {
        _dataSock->close();
        _dataSock = nullptr;
    }
    //
    disconnect(_dataServer, &QTcpServer::newConnection, this, &Cftp::SlotDataConnect);
    delete _dataServer;
    //
    disconnect(_sck, SIGNAL(disconnected()), this, SLOT(SlotConnectlost()));
    disconnect(_sck, SIGNAL(readyRead()), this, SLOT(SlotReadready()));

    // sck 是上层传入，但是这里已经由Cftp托管了
    _sck->close();
}

void Cftp::Reply(const QString& replyCode)
{
    _sck->write((replyCode + "\r\n").toUtf8());
}

void Cftp::SlotConnectlost()
{
    qDebug() << "ftp disconnect";
    if(nullptr != _sftp)
    {
        qobject_cast<STftpd*>(_sftp)->CFtpDisConnect();
    }
    deleteLater();
}

void Cftp::SlotReadready()
{
    if(!_sck->canReadLine())
    {
        return ;
    }
    const QByteArray& ba = _sck->readLine().trimmed();
    // 解析命令
    ParseCommond(ba);
    QTimer::singleShot(0, this, &Cftp::SlotReadready);
}

void Cftp::SlotDataConnect()
{
    _dataSock = _dataServer->nextPendingConnection();
    _dataServer->close();

    // 建立新的数据通道，监听数据可读和中断
    connect(_dataSock, &QTcpSocket::bytesWritten, this, &Cftp::SlotSendFrameOK);
    connect(_dataSock, &QTcpSocket::readyRead, this, &Cftp::SlotRecvdata);
    connect(_dataSock, &QTcpSocket::disconnected, this, &Cftp::SlotAborddata);
}

void Cftp::SlotRecvdata()
{
    const QByteArray& bytes = _dataSock->readAll();
    int bytesWritten = file->write(bytes);
    //qDebug() << "recv " << bytes;
}

void Cftp::SlotSendFrameOK(qint64 bytes)
{
    if(!file->atEnd())
    {
        _dataSock->write(file->read(bytes));
    }
    else
    {
        _dataSock->disconnectFromHost();
    }
}

void Cftp::SlotAborddata()
{
    qDebug() << "SlotAborddata";
    // 文件传输结束，清理socket和file
    file->close();
    file = nullptr;

    disconnect(_dataSock, &QTcpSocket::bytesWritten, this, &Cftp::SlotSendFrameOK);
    disconnect(_dataSock, &QTcpSocket::readyRead, this, &Cftp::SlotRecvdata);
    disconnect(_dataSock, &QTcpSocket::disconnected, this, &Cftp::SlotAborddata);
    _dataSock->close();
    _dataSock = nullptr;

    // 回复消息，传输完成
    Reply("226 Closing data connection.");
}

void Cftp::ParseCommond(const QString& cmd)
{
    qDebug() << cmd;
    QString cmdstr;
    QString args;

    parseCommand(cmd, &cmdstr, &args);

    if("USER" == cmdstr)
    {
        Reply("331 User name OK, need password.");
        return ;
    }
    else if("PASS" == cmdstr)
    {
        _logined = true;
        Reply("230 You are logged in.");
        return ;
    }

    if(!_logined)
    {
        qDebug() << "need login first";
        Reply("530 You must log in first.");
        return ;
    }

    if("QUIT" == cmdstr)
    {
        Reply("221 Quitting...");
        #if 0
        if(nullptr != _sftp)
        {
            qobject_cast<STftpd*>(_sftp)->CFtpQuit();
        }
        #endif
    }
    else if("AUTH" == cmdstr && "TLS" == args.toUpper())
    {
        //auth();
    }
    else if("FEAT" == cmdstr)
    {
        //feat();
    }
    else if("PWD" == cmdstr)
    {
    }
    else if("CWD" == cmdstr)
    {
    }
    else if("TYPE" == cmdstr)
    {
        Reply("200 cmdstr okay.");
    }
    else if("PORT" == cmdstr)
    {
    }
    else if("PASV" == cmdstr)
    {
        // 启用数据通道的监听，并且告诉客户端，监听的端口和地址
        _dataServer->close();
        _dataServer->listen();
        int port = _dataServer->serverPort();
        // 告诉客户端，将从这个地址发送数据
        Reply(QString("227 Entering Passive Mode (%1,%2,%3).").arg(_sck->localAddress().toString()).arg(port / 256).arg(port % 256));
    }
    else if("LIST" == cmdstr)
    {
    }
    else if("RETR" == cmdstr)
    {
        // 打开文件
        file = new QFile(QCoreApplication::applicationDirPath() + FTP_ROOT + args);
        file->open(QIODevice::ReadWrite);
        // 告诉客户端，数据已经准备好了
        Reply("150 File status okay; about to open data connection.");
        // 先写一段数据
        SlotSendFrameOK(128 * 1024);
    }
    else if("REST" == cmdstr)
    {
    }
    else if("NLST" == cmdstr)
    {
    }
    else if("SIZE" == cmdstr)
    {
        QFileInfo fi(QCoreApplication::applicationDirPath() + FTP_ROOT + args);
        if(!fi.exists() || fi.isDir())
        {
            Reply("550 Requested action not taken; file unavailable.");
            return ;
        }
        // 告诉客户端，文件大小
        Reply(QString("213 %1").arg(fi.size()));
    }
    else if("SYST" == cmdstr)
    {
    }
    else if("PROT" == cmdstr)
    {
    }
    else if("CDUP" == cmdstr)
    {
    }
    else if("OPTS" == cmdstr && "UTF8 ON" == args.toUpper())
    {
    }
    else if("PBSZ" == cmdstr && "0" == args.toUpper())
    {
    }
    else if("NOOP" == cmdstr)
    {
    }
    else if("STOR" == cmdstr)
    {
        // 上传文件
        // 从socket读取数据保存文件
        // args是文件的名字，可能带路径
        if(args.contains("/"))
        {
            args = args.split("/").last();
        }
        // 打开文件
        qDebug() << QCoreApplication::applicationDirPath() + FTP_ROOT + args;
        file = new QFile(QCoreApplication::applicationDirPath() + FTP_ROOT + args);
        file->open(QIODevice::ReadWrite);
        // 回复文件已经准备好了
        Reply("150 File status okay; about to open data connection.");
    }
    else if("MKD" == cmdstr)
    {
    }
    else if("RMD" == cmdstr)
    {
    }
    else if("DELE" == cmdstr)
    {
    }
    else if("RNFR" == cmdstr)
    {
    }
    else if("RNTO" == cmdstr)
    {
    }
    else if("APPE" == cmdstr)
    {
    }
    else
    {
        Reply("502 cmdstr not implemented.");
    }
}

void Cftp::parseCommand(const QString& entirecmdstr, QString* cmdstr, QString* cmdstrParameters)
{
    // Split parameters and cmdstr.
    int pos = entirecmdstr.indexOf(' ');
    if(-1 != pos)
    {
        *cmdstr = entirecmdstr.left(pos).trimmed().toUpper();
        *cmdstrParameters = entirecmdstr.mid(pos + 1).trimmed();
    }
    else
    {
        *cmdstr = entirecmdstr.trimmed().toUpper();
    }
}
