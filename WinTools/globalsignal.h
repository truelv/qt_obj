#ifndef GLOBALSIGNAL_H
#define GLOBALSIGNAL_H

#include <QObject>

typedef enum {
    SFTP_STA_OK = 0,
    SFTP_STA_OPEN_FAILE,
    SFTP_STA_OTHRE,
} SFTP_STA;

class GlobalSignal : public QObject
{
    Q_OBJECT
public:
    static GlobalSignal* GetInstance();
    ~GlobalSignal();

    //
    void SendSigSftpSta(SFTP_STA sta);
    void SendSigCftpEnd();

signals:
    // ftp信号
    // 服务状态
    void SigSftpSta(SFTP_STA sta);
    // 客户端接入，断开
    void SigCftpEnd();

private:
    static GlobalSignal* _Itent;
    explicit GlobalSignal(QObject *parent = nullptr);

};

#endif // GLOBALSIGNAL_H
