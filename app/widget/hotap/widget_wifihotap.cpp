#include "widget_wifihotap.h"
#include "ui_widget_wifihotap.h"
#include "tcp_server.h"
#include "global.h"
#include "net/wifi_svc.h"

Widget_WifiHotap::Widget_WifiHotap(QWidget *parent, const QString &title) :
    Widget_Base(parent, title),
    ui(new Ui::Widget_WifiHotap),
    _tcpServerIsOn(false)
{
    ui->setupUi(&_w);

    _layout = new QVBoxLayout(this);
    _layout->addWidget(&_backTitle);
    _layout->addWidget(&_w);
    QMargins margins = _layout->contentsMargins();
    margins.setLeft(0);
    margins.setRight(0);
    _layout->setContentsMargins(margins);
    _w.setStyleSheet("border:0px solid black;margin:0px");
    ui->tcp_start->setStyleSheet("font: 45pt'微软雅黑';");

    connect(ui->tcp_start, SIGNAL(clicked()), this, SLOT(on_tcp_start_clicked()));
    //TCP
    connect(&_tcpServer, SIGNAL(signalTcpServerStart(bool)), this, SLOT(slotTcpServerStart(bool)));
    connect(&_tcpServer, SIGNAL(signalTcpConnected(bool)), this, SLOT(slotTcpConnected(bool)));
    connect(&_tcpServer, SIGNAL(signalTcpReadStart(int)), this, SLOT(slotTcpReadStart(int)));
    connect(&_tcpServer, SIGNAL(signalTcpReadOver(int)), this, SLOT(slotTcpReadOver(int)));
    connect(&_tcpServer, SIGNAL(signalTcpReadProgress(int)), this, SLOT(slotTcpReadProgress(int)));
    connect(&_tcpServer, SIGNAL(signalWorkDone(int)), this, SLOT(slotWorkDone(int)));

    connect(&_tcpServer, SIGNAL(signalTransFailed()), this, SLOT(slotTransFailed()));
    connect(&_tcpServer, SIGNAL(signalCrcCheckFailed()), this, SLOT(slotCrcCheckFailed()));

    _sender = SignalSender::getInstance();
    connect(_sender, SIGNAL(signalTofeatFailed(const QString&)), this, SLOT(slotTofeatFailed(const QString&)));

    ui->msg->setFontPointSize(28);

    WidgetMessage::GetInstance()->ShowMessageKeep(tr("正在开启运维助手"), false, NULL);
    QTimer::singleShot(100, this, SLOT(openAp()));
}

Widget_WifiHotap::~Widget_WifiHotap()
{
    // 修改回60s
    // 设置倒计时时间为1h
    SignalSender* send = SignalSender::getInstance();
    send->sendSignalChangeOutTime(BLANK_TIMEOUT_MS_SETTING);
    wifi_closeAp();
    if (g_BaseInfo.deviceStatusSwitch&DEVICESTATUS_MASK_WIFION)
    {
        // 如果wifi状态是开启，那么在离开热点的时候要打开
        wifi_svc_open();
    }
    delete _layout;
    delete ui;
}

void Widget_WifiHotap::openAp()
{
    ui->ap_name->setText(QString("yt328_rd_%1").arg(g_BaseInfo.serialNum));
    // 启动ap，这个函数会自己处理此之前是开启wifi的情况
    if (wifi_open4ap()<0)
    {
        WidgetMessage::GetInstance()->ShowMessageHide(tr("正在开启运维助手"), false, NULL, 1);
        return;
    }

    WidgetMessage::GetInstance()->ShowMessageHide(tr("开启运维助手成功"), false, NULL, 1);
}

void Widget_WifiHotap::slotTofeatFailed(const QString& msg)
{
    //ui->msg->setText(msg);
    ui->msg->append(msg);
}

void Widget_WifiHotap::slotTransFailed()
{
    ui->update_state->setText(tr("文件传输失败"));
    WidgetMessage::GetInstance()->ShowMessageHide(tr("文件传输失败"), false, NULL, 1);
}

void Widget_WifiHotap::slotCrcCheckFailed()
{
    ui->update_state->setText(tr("crc校验包失败"));
    WidgetMessage::GetInstance()->ShowMessageHide(tr("crc校验包失败"), false, NULL, 1);
}

void Widget_WifiHotap::on_tcp_start_clicked()
{
    LOG_I("tcp按键");
    if (_tcpServerIsOn)
    {
        _tcpServer.stopServer();
        ui->tcp_start->setText(tr("启动tcp服务"));
        _tcpServerIsOn = false;
        LOG_I("停止tcp");
    }
    else
    {
        // 启动tcp scoket（单连接模式）
        _tcpServer.startServer();
        ui->tcp_start->setText(tr("停止tcp服务"));
        _tcpServerIsOn = true;
        LOG_D("启动tcp");
    }
}

void Widget_WifiHotap::slotTcpServerStart(bool on)
{
    if (on)
        ui->tcp_server->setText(tr("tcp服务启动"));
    else
        ui->tcp_server->setText(tr("tcp服务关闭"));
}

void Widget_WifiHotap::slotTcpConnected(bool on)
{
    if (on)
        ui->connect_state->setText(tr("tcp服务连接"));
    else
        ui->connect_state->setText(tr("tcp服务断开"));
}

void Widget_WifiHotap::slotTcpReadStart(int type)
{
    switch (type)
    {
    case PROTOCOL_TCPCMD_APPUPDATE:
        ui->update_state->setText(tr("开始更新应用程序..."));
        break;
    case PROTOCOL_TCPCMD_SENDLOG:
        ui->update_state->setText(tr("开始下发日志文件..."));
        break;
    case PROTOCOL_TCPCMD_FACEFEAT:
        ui->update_state->setText(tr("开始添加人特征值..."));
        ui->msg->clear();
        break;
    case PROTOCOL_TCPCMD_FACEIMGS:
    case PROTOCOL_TCPCMD_FACEIMG:
        ui->update_state->setText(tr("开始添加人脸图片..."));
        ui->msg->clear();
        break;
    default:
        break;
    }
    ui->progress->setValue(0);
}

void Widget_WifiHotap::slotTcpReadOver(int type)
{
    LOG_I("传输文件结束");
    switch (type)
    {
    case PROTOCOL_TCPCMD_APPUPDATE:
    {
        ui->update_state->setText(tr("更新应用程序完成"));
        WidgetMessage::GetInstance()->ShowMessageReboot(tr("更新应用完成，即将重启"), false, NULL, 5);
        break;
    }
    case PROTOCOL_TCPCMD_SENDLOG:
    {
        ui->update_state->setText(tr("日志文件发送完成"));
        WidgetMessage::GetInstance()->ShowMessageHide(tr("日志文件发送完成"), false, NULL, 1);
        break;
    }
    case PROTOCOL_TCPCMD_FACEFEAT:
        ui->update_state->setText(tr("特征值压缩包接收完成"));
        // 开始添加特征码，起线程添加
        ui->update_state->setText(tr("开始转特征码..."));
        break;
    case PROTOCOL_TCPCMD_FACEIMGS:
    case PROTOCOL_TCPCMD_FACEIMG:
        ui->update_state->setText(tr("图片压缩包接收完成"));
        // 开始添加特征码，起线程添加
        ui->update_state->setText(tr("开始转特征码..."));
        break;
    case PROTOCOL_TCPCMD_DELFACE:
        ui->update_state->setText(tr("开始删除特征码..."));
        break;
    default:
        break;
    }
    ui->progress->setValue(100);
}

void Widget_WifiHotap::slotTcpReadProgress(int progress)
{
    ui->progress->setValue(progress);
}

void Widget_WifiHotap::slotWorkDone(int type)
{
    switch (type)
    {
    case PROTOCOL_TCPCMD_FACEFEAT:
    case PROTOCOL_TCPCMD_FACEIMGS:
    case PROTOCOL_TCPCMD_FACEIMG:
    {

        ui->update_state->setText(tr("转特征码完成"));
        WidgetMessage::GetInstance()->ShowMessageHide(tr("转特征码完成"), false, NULL, 1);
        break;
    }
    case PROTOCOL_TCPCMD_DELFACE:
    {
        ui->update_state->setText(tr("删除特征码操作完成"));
        WidgetMessage::GetInstance()->ShowMessageHide(tr("删除特征码操作完成"), false, NULL, 1);
        break;
    }
    default:
        break;
    }
}
