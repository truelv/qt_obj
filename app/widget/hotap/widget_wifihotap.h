// wifi热点开启界面，开启热点后，可以开启tcp服务监听客户端连接，
// 接受3个任务，1、更新应用，2、注册特征码，3、获取日志
#ifndef WIDGET_WIFIHOTAP_H
#define WIDGET_WIFIHOTAP_H

#include <QWidget>
#include <QVBoxLayout>

#include "widget/widget_base.h"
#include "tcp_server.h"
#include "signalsender.h"
#include "widget/widgetmessage.h"

namespace Ui {
class Widget_WifiHotap;
}

class Widget_WifiHotap : public Widget_Base
{
    Q_OBJECT

public:
    explicit Widget_WifiHotap(QWidget *parent = 0, const QString& title="");
    ~Widget_WifiHotap();

protected slots:
    void on_tcp_start_clicked();
    // 服务启动/关闭
    void slotTcpServerStart(bool on);
    // tcp连接/关闭
    void slotTcpConnected(bool on);
    // 开始传输
    void slotTcpReadStart(int type);
    // 结束传输
    void slotTcpReadOver(int type);
    // 传输进度
    void slotTcpReadProgress(int progress);
    // 结束二阶段执行任务
    void slotWorkDone(int type);
    //
    void openAp();
    //
    void slotTofeatFailed(const QString&);
    //
    void slotTransFailed();
    //
    void slotCrcCheckFailed();

    //void slotOpenApDialog();

private:
    QVBoxLayout* _layout;
    QWidget _w;

    Ui::Widget_WifiHotap *ui;

    bool _tcpServerIsOn;
    Tcp_Server _tcpServer;
    SignalSender* _sender;
};

#endif // WIDGET_WIFIHOTAP_H
