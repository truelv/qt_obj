#include "cftp.h"
#include <QTimer>
#include <QString>
#include <QHostAddress>

Cftp::Cftp(QTcpSocket *sck, QObject *parent) : QObject(parent), _sck(sck),
    _logined(false)
{
    connect(_sck, SIGNAL(disconnected()), this, SLOT(SlotConnectlost()));
    connect(_sck, SIGNAL(readyRead()), this, SLOT(SlotReadready()));

    _dataServer = new QTcpServer;
    Reply("220 Welcome to QFtpServer.");
}

Cftp::~Cftp()
{
    delete _dataServer;
    //
    disconnect(_sck, SIGNAL(disconnected()), this, SLOT(SlotConnectlost()));
    disconnect(_sck, SIGNAL(readyRead()), this, SLOT(SlotReadready()));
}

void Cftp::Reply(const QString &replyCode)
{
    _sck->write((replyCode+"\r\n").toUtf8());
}

void Cftp::SlotConnectlost()
{
    qDebug() << "ftp disconnect";
    this->deleteLater();
}

void Cftp::SlotReadready()
{
    if (!_sck->canReadLine())
        return ;
    const QByteArray& ba = _sck->readLine().trimmed();
    // 解析命令
    ParseCommond(ba);
    QTimer::singleShot(0, this, &Cftp::SlotReadready);
}

void Cftp::ParseCommond(const QString &cmd)
{
    qDebug() << cmd;
    QString cmdstr;
    QString args;

    parseCommand(cmd, &cmdstr, &args);

    if ("USER" == cmdstr) {
        Reply("331 User name OK, need password.");
        return ;
    } else if ("PASS" == cmdstr) {
        _logined = true;
        Reply("230 You are logged in.");
        return ;
    }

    if (!_logined)
    {
        qDebug() << "need login first";
        Reply("530 You must log in first.");
        return ;
    }

    if ("QUIT" == cmdstr) {
        //quit();
    } else if ("AUTH" == cmdstr && "TLS" == args.toUpper()) {
        //auth();
    } else if ("FEAT" == cmdstr) {
        //feat();
    } else if ("PWD" == cmdstr) {
#if 0
        if (!isLoggedIn) {
            reply("530 You must log in first.");
        } else {
            reply(QString("257 \"%1\"").arg(currentDirectory));
        }
#endif
    } else if ("CWD" == cmdstr) {
#if 0
        if (!isLoggedIn) {
            reply("530 You must log in first.");
        } else {
            cwd(cmdstrParameters);
        }
#endif
    } else if ("TYPE" == cmdstr) {
        Reply("200 cmdstr okay.");
    } else if ("PORT" == cmdstr) {
#if 0
        if (!isLoggedIn) {
            reply("530 You must log in first.");
        } else {
            port(cmdstrParameters);
        }
#endif
    } else if ("PASV" == cmdstr) {
        int port = 10000;
       Reply(QString("227 Entering Passive Mode (%1,%2,%3).").arg(_sck->localAddress().toString()).arg(port/256).arg(port%256));
    } else if ("LIST" == cmdstr) {
#if 0
        if (!isLoggedIn) {
            reply("530 You must log in first.");
        } else {
            list(toLocalPath(stripFlagL(cmdstrParameters)), false);
        }
#endif
    } else if ("RETR" == cmdstr) {
#if 0
        if (!isLoggedIn) {
            reply("530 You must log in first.");
        }
        else if(writeOnly)
        {
            reply("550 Can't do that in write-only mode.");
        }
        else {
            retr(toLocalPath(cmdstrParameters));
        }
#endif
    } else if ("REST" == cmdstr) {
#if 0
        if (!isLoggedIn) {
            reply("530 You must log in first.");
        } else {
            reply("350 Requested file action pending further information.");
        }
#endif
    } else if ("NLST" == cmdstr) {
#if 0
        if (!isLoggedIn) {
            reply("530 You must log in first.");
        } else {
            list(toLocalPath(stripFlagL(cmdstrParameters)), true);
        }
#endif
    } else if ("SIZE" == cmdstr) {
#if 0
        if (!isLoggedIn) {
            reply("530 You must log in first.");
        } else {
            size(toLocalPath(cmdstrParameters));
        }
#endif
    } else if ("SYST" == cmdstr) {
#if 0
        if (!isLoggedIn) {
            reply("530 You must log in first.");
        } else {
            reply("215 UNIX");
        }
#endif
    } else if ("PROT" == cmdstr) {
#if 0
        if (!isLoggedIn) {
            reply("530 You must log in first.");
        } else {
            prot(cmdstrParameters.toUpper());
        }
#endif
    } else if ("CDUP" == cmdstr) {
#if 0
        if (!isLoggedIn) {
            reply("530 You must log in first.");
        } else {
            cdup();
        }
#endif
    } else if ("OPTS" == cmdstr && "UTF8 ON" == args.toUpper()) {
#if 0
        if (!isLoggedIn) {
            reply("530 You must log in first.");
        } else {
            reply("200 cmdstr okay.");
        }
#endif
    } else if ("PBSZ" == cmdstr && "0" == args.toUpper()) {
#if 0
        if (!isLoggedIn) {
            reply("530 You must log in first.");
        } else {
            reply("200 cmdstr okay.");
        }
#endif
    } else if ("NOOP" == cmdstr) {
#if 0
        if (!isLoggedIn) {
            reply("530 You must log in first.");
        } else {
            reply("200 cmdstr okay.");
        }
#endif
    } else if ("STOR" == cmdstr) {
#if 0
        if (!isLoggedIn) {
            reply("530 You must log in first.");
        } else if (readOnly) {
            reply("550 Can't do that in read-only mode.");
        } else {
            stor(toLocalPath(cmdstrParameters));
        }
#endif
    } else if ("MKD" == cmdstr) {
#if 0
        if (!isLoggedIn) {
            reply("530 You must log in first.");
        } else if (readOnly) {
            reply("550 Can't do that in read-only mode.");
        } else {
            mkd(toLocalPath(cmdstrParameters));
        }
#endif
    } else if ("RMD" == cmdstr) {
#if 0
        if (!isLoggedIn) {
            reply("530 You must log in first.");
        } else if (readOnly) {
            reply("550 Can't do that in read-only mode.");
        } else {
            rmd(toLocalPath(cmdstrParameters));
        }
#endif
    } else if ("DELE" == cmdstr) {
#if 0
        if (!isLoggedIn) {
            reply("530 You must log in first.");
        } else if (readOnly) {
            reply("550 Can't do that in read-only mode.");
        } else {
            dele(toLocalPath(cmdstrParameters));
        }
#endif
    } else if ("RNFR" == cmdstr) {
#if 0
        if (!isLoggedIn) {
            reply("530 You must log in first.");
        } else if (readOnly) {
            reply("550 Can't do that in read-only mode.");
        } else {
            reply("350 Requested file action pending further information.");
        }
#endif
    } else if ("RNTO" == cmdstr) {
#if 0
        if (!isLoggedIn) {
            reply("530 You must log in first.");
        } else if (readOnly) {
            reply("550 Can't do that in read-only mode.");
        } else {
            rnto(toLocalPath(cmdstrParameters));
        }
#endif
    } else if ("APPE" == cmdstr) {
#if 0
        if (!isLoggedIn) {
            reply("530 You must log in first.");
        } else if (readOnly) {
            reply("550 Can't do that in read-only mode.");
        } else {
            stor(toLocalPath(cmdstrParameters), true);
        }
#endif
    } else {
        Reply("502 cmdstr not implemented.");
    }
}

void Cftp::parseCommand(const QString &entirecmdstr, QString *cmdstr, QString *cmdstrParameters)
{
    // Split parameters and cmdstr.
    int pos = entirecmdstr.indexOf(' ');
    if (-1 != pos) {
        *cmdstr = entirecmdstr.left(pos).trimmed().toUpper();
        *cmdstrParameters = entirecmdstr.mid(pos+1).trimmed();
    } else {
        *cmdstr = entirecmdstr.trimmed().toUpper();
    }
}
