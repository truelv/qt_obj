#include "widget_wifiqrscansetting.h"
#include "ui_widget_wifiqrscansetting.h"
#include "DB/dbyt.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "net/wifi_svc.h"
#include "global.h"
#ifdef __cplusplus
}
#endif

Widget_WifiQrscanSetting::Widget_WifiQrscanSetting(Widget_Base *parent, const QString &title) :
    Widget_Base(parent, title),
    ui(new Ui::Widget_WifiQrscanSetting),
    isConnected(false)
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

    ui->wifi_state->setText(tr("wifi未开启"));
    ui->wifi_connect->hide();

    _sigSender = SignalSender::getInstance();
    connect(_sigSender, SIGNAL(signalWifiConnected()), this, SLOT(slotWifiConnected()));
    connect(this, SIGNAL(signalShowWifiOpening()), this, SLOT(slotShowWifiOpening()));
    connect(&_timer, SIGNAL(timeout()), this, SLOT(slotWifiOpen()));

    _timer.start(300);
}

Widget_WifiQrscanSetting::~Widget_WifiQrscanSetting()
{
    // 离开这个页面，关闭扫描连接
    g_BaseInfo.deviceStatusSwitch &= ~DEVICESTATUS_MASK_QRWIFI;
    // 如果没有连接wifi，关闭
    if (!isConnected)
    {
        wifi_svc_close();

        g_BaseInfo.deviceStatusSwitch &= ~DEVICESTATUS_MASK_WIFION;
        DBYt::GetInstance()->UpdateKV("BaseInfo", "deviceStatusSwitch",
                                      g_BaseInfo.deviceStatusSwitch&DEVICESTATUS_MASK_SWITCHSAVE);
    }
    delete ui;
    delete _layout;
}

void Widget_WifiQrscanSetting::slotWifiConnected()
{
    CONNECT_INFO connect_info;
    memset(&connect_info, 0, sizeof(connect_info));
    // 获取当前连接的wifi
    if (0==sta_get_connect_info(&connect_info))
    {
        LOG_I("获取连接wifi信息");
        ui->wifi_ssid->setText(connect_info.ssid);
        isConnected = true;
    }
}

void Widget_WifiQrscanSetting::slotWifiOpen()
{
    _timer.stop();
    // 如果wifi没有开，开启wifi
    if (!(g_BaseInfo.deviceStatusSwitch&DEVICESTATUS_MASK_WIFION))
    {
        emit signalShowWifiOpening();
        QCoreApplication::processEvents();

        if (wifi_svc_open()<0) {
            // 开启失败
            WidgetMessage::GetInstance()->ShowMessageHide(tr("打开wifi失败"), false, NULL, 1);
            return;
        }
        WidgetMessage::GetInstance()->ShowMessageHide(tr("打开wifi成功"), false, NULL, 1);

        g_BaseInfo.deviceStatusSwitch |= DEVICESTATUS_MASK_WIFION;
        DBYt::GetInstance()->UpdateKV("", "",
                                      g_BaseInfo.deviceStatusSwitch&DEVICESTATUS_MASK_SWITCHSAVE);
    }

    ui->wifi_state->setText(tr("wifi开启"));

    // 开启扫描标记
    g_BaseInfo.deviceStatusSwitch |= DEVICESTATUS_MASK_QRWIFI;

    // 检查是否已经连接wifi
    CONNECT_INFO connect_info;
    memset(&connect_info, 0, sizeof(connect_info));
    ui->wifi_ssid->setText(tr("未连接"));
    // 获取当前连接的wifi
    if (0==sta_get_connect_info(&connect_info))
    {
        LOG_I("获取连接wifi信息");
        ui->wifi_ssid->setText(connect_info.ssid);
        isConnected = true;
    }
}

void Widget_WifiQrscanSetting::slotShowWifiOpening()
{
    WidgetMessage::GetInstance()->ShowMessageKeep(tr("正在打开wifi"), false, NULL);
}
