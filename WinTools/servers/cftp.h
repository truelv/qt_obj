#ifndef CFTP_H
#define CFTP_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>

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

private:
    QTcpSocket* _sck;
    void ParseCommond(const QString& cmd);
    void parseCommand(const QString &entireCommand, QString *command, QString *commandParameters);

    //
    bool _logined;
    // data
    QTcpServer* _dataServer;

};

#endif // CFTP_H
