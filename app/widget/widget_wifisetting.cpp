#include "widget_wifisetting.h"
#include "ui_widget_wifisetting.h"
#include "items/buttontype3.h"
#include "DB/dbyt.h"

#ifdef __cplusplus
extern "C" {
#endif
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "network/net_utils/net_utils.h"
#include "network/net_utils/ip_config.h"

#include "net/eth_svc.h"
#include "net/wifi_svc.h"
#include "global.h"

#ifdef __cplusplus
}
#endif

#define LOGTAG "wifi_setting"

Widget_WIfiSetting::Widget_WIfiSetting(Widget_Base *parent, const QString &title) :
    Widget_Base(parent, title),
    ui(new Ui::Widget_WIfiSetting),
    _connected_index(-1),
    _connect_index(-1),
    _dialogPass(0)
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

    _sigSender = SignalSender::getInstance();
    connect(ui->wifi_switch, SIGNAL(clicked()), this, SLOT(slotWifiSwitch()));
    connect(_sigSender, SIGNAL(signalWifiScanFailed()), this, SLOT(slotWifiScanFailed()));
    connect(_sigSender, SIGNAL(signalUpdateListWifi()), this, SLOT(slotListWIFI()));
    connect(_sigSender, SIGNAL(signalWifiConnected()), this, SLOT(slotWifiConnected()));
    connect(_sigSender, SIGNAL(signalWifiConnecting()), this, SLOT(slotWifiConnecting()));
    connect(ui->list_wifi, SIGNAL(clicked(QModelIndex)), this, SLOT(slotWifiSlecet(QModelIndex)));

    connect(this, SIGNAL(signalShowOpen()), this, SLOT(slotShowOpen()));

    // 数据库获取wifi开关状态
    _wifiIsOn = (g_BaseInfo.deviceStatusSwitch&DEVICESTATUS_MASK_WIFION)==0?false:true;
    // 如果wifi开启，设置按钮为开启，提交一个wifi扫描任务
    if (_wifiIsOn)
    {
        ui->wifi_switch->setStyleSheet(QString("#wifi_switch {"
                                               "border-image:url(%1/switch_close.png);"
                                               "}").arg(UI_IMG_DIR));
        ui->wifi_switch->setEnabled(false);
        wifi_svc_scan();
        // 提示正在扫描
#if 1
        WidgetMessage::GetInstance()->ShowMessageKeep(tr("正在扫描"), false, NULL);
#else
        MessageDialog* dialog = MessageDialog::getInsTance();
        dialog->setShowText(tr("正在扫描"));
        dialog->hideButton();
        dialog->show();
#endif
        ui->wifi_switch->setEnabled(true);
    }
    else
    {
        //开用switch_close.png，关用switch_open.png
        ui->wifi_switch->setStyleSheet(QString("#wifi_switch {"
                                               "border-image:url(%1/switch_open.png);"
                                               "}").arg(UI_IMG_DIR));
    }

    this->showMaximized();

}

Widget_WIfiSetting::~Widget_WIfiSetting()
{
    slotClearListWIFI();
    LOG_D("销毁wifi设置界面");
    LOG_D("销毁wifi设置界面123");
    delete _layout;
    delete ui;
}

void Widget_WIfiSetting::autoToBack()
{
    if (0!=_dialogPass)
    {
        _dialogPass->hideKeyBoard();
        _dialogPass->reject();
        _dialogPass->deleteLater();
        _dialogPass = 0;
    }
    Widget_Base::autoToBack();
}

void Widget_WIfiSetting::slotWifiSwitch()
{
    if (_wifiIsOn)
    {   // 关闭wifi
        // 开用switch_close.png，关用switch_open.png
        ui->wifi_switch->setStyleSheet(QString("#wifi_switch {"
                                               "border-image: url(%1/switch_open.png);"
                                               "}").arg(UI_IMG_DIR));
        ui->wifi_switch->setEnabled(false);
        wifi_svc_close();
        g_BaseInfo.deviceStatusSwitch &= ~DEVICESTATUS_MASK_WIFION;
        DBYt::GetInstance()->UpdateKV("BaseInfo", "deviceStatusSwitch",
                                      g_BaseInfo.deviceStatusSwitch&DEVICESTATUS_MASK_SWITCHSAVE);
        // 清列表
        slotClearListWIFI();
        _wifiIsOn = false;
        ui->wifi_switch->setEnabled(true);
    }
    else
    {
        // 开启wifi
        emit signalShowOpen();
        QCoreApplication::processEvents();
        ui->wifi_switch->setEnabled(false);

        if (wifi_svc_open()<0)
        {
            WidgetMessage::GetInstance()->ShowMessageHide(tr("打开失败"), false, NULL, 1);
            ui->wifi_switch->setEnabled(true);
            return;
        }

        // 开用switch_close.png，关用switch_open.png
        ui->wifi_switch->setStyleSheet(QString("#wifi_switch {"
                                       "border-image: url(%1/switch_close.png);"
                                       "}").arg(UI_IMG_DIR));
        g_BaseInfo.deviceStatusSwitch |= DEVICESTATUS_MASK_WIFION;
        DBYt::GetInstance()->UpdateKV("BaseInfo", "deviceStatusSwitch",
                                      g_BaseInfo.deviceStatusSwitch&DEVICESTATUS_MASK_SWITCHSAVE);

        _wifiIsOn = true;
        wifi_svc_scan();
        // 提示正在扫描
        WidgetMessage::GetInstance()->ShowMessageKeep(tr("正在扫描"), false, NULL);
        ui->wifi_switch->setEnabled(true);
    }
}

void Widget_WIfiSetting::slotWifiScanFailed()
{
    // 扫描失败
    WidgetMessage::GetInstance()->ShowMessageHide(tr("扫描失败"), false, NULL, 1);
}

void Widget_WIfiSetting::slotListWIFI()
{
    // 扫描成功
    WidgetMessage::GetInstance()->ShowMessageHide(tr("扫描成功"), false, NULL, 1);

    SCAN_INFO* scan_info = wifi_svc_get_list_p();
    HOTSPOT_INFO* wifi = NULL;
    CONNECT_INFO connect_info;
    memset(&connect_info, 0, sizeof(connect_info));
    // 获取当前连接的wifi
    sta_get_connect_info(&connect_info);

    LOG_D("连接wifi的id %d, ssid %s", connect_info.id, connect_info.ssid);

    if (scan_info->num <= 0)
    {
        LOG_E("wifi服务中的wifi列表为空的");
        return ;
    }
    HOTSPOT_INFO *info = scan_info->info;

    // 遍历wifi列表，展示
    for (int i=0;i<scan_info->num;i++)
    {
        wifi = info+i;
        QListWidgetItem* item = new QListWidgetItem(ui->list_wifi);
        item->setSizeHint(QSize(620, 100));
        ButtonType3* w =  new ButtonType3;
        w->setSSIDName(wifi->ssid);
        w->setFocusPolicy(Qt::NoFocus);
        // signal
        if (wifi->rssi<=-100)
        {
            // 0
            w->setSignalIcon(QString("border-image:url(%1/wifi_1.png);")
                             .arg(UI_IMG_DIR));
        }
        else if (-100<wifi->rssi && wifi->rssi<=-88)
        {
            // 1格
            w->setSignalIcon(QString("border-image:url(%1/wifi_1.png);")
                             .arg(UI_IMG_DIR));
        }
        else if (-88<wifi->rssi&& wifi->rssi<=-77)
        {
            // 2
            w->setSignalIcon(QString("border-image:url(%1/wifi_2.png);")
                             .arg(UI_IMG_DIR));
        }
        else if (-77<wifi->rssi && wifi->rssi<=-55)
        {
            // 3
            w->setSignalIcon(QString("border-image:url(%1/wifi_3.png);")
                             .arg(UI_IMG_DIR));
        }
        else
        {
            // 4
            w->setSignalIcon(QString("border-image:url(%1/wifi_4.png);")
                             .arg(UI_IMG_DIR));
        }
        // 如果是已连接的wifi，设置为已连接
        if (!strncmp(wifi->ssid, connect_info.ssid, strlen(wifi->ssid))
                && strlen(wifi->ssid)==strlen(connect_info.ssid)) {
            w->setConnected(tr("已连接"));

            _connected_index = i;
        }
        ui->list_wifi->setItemWidget(item, w);
    }
}

void Widget_WIfiSetting::slotClearListWIFI()
{
    QListWidgetItem* item = NULL;
    QWidget* w = NULL;
    // 如果有连接，需要断开连接
    // 删除所有的 QListWidgetItem和 QWidget
    // 这里包扩查询那2个界面是否会存在内存泄漏
    int count = ui->list_wifi->count();
    for (int i=0;i<count;i++)
    {
        item = ui->list_wifi->item(0);
        w = ui->list_wifi->itemWidget(item);
        delete w;
        ui->list_wifi->removeItemWidget(item);
        delete item;
    }
}

void Widget_WIfiSetting::slotWifiSlecet(QModelIndex index)
{
    // 尝试连接这个wifi，没有连接，直接去连接，有连接，修改
    // 获取wifi列表
    HOTSPOT_INFO* info = wifi_svc_get_list_p()->info;
    // 获取点击的item序号
    int item_index = index.row();
    QString retv;
    // 如果选择wifi是加密的，弹出密码输入框
    if (0!=info[item_index].security)
    {
        _dialogPass = new WidgetMessage;
        // 这里需要用exec来阻塞进程
        if (_dialogPass->ExecPasswordInput(retv)==QDialog::Rejected)
        {
            delete _dialogPass;
            _dialogPass = NULL;
            return;
        }

        LOG_D("输入密码 %s ", retv.toAscii().data());
        delete _dialogPass;
        _dialogPass = NULL;
    }
    // 点击确定，连接
    _sigSender->sendSignalWifiConnecting();
    QCoreApplication::processEvents();

    _connect_index = item_index;
    if (wifi_svc_connect_passw(item_index, retv.toAscii().constData())<0)
    {
        // 连接失败
        WidgetMessage::GetInstance()->ShowMessageHide(tr("连接失败"), false, NULL, 1);
        LOG_E("wifi连接操作失败");
    }

}

void Widget_WIfiSetting::slotWifiConnecting()
{
    //LOG_I("wifi正在连接");
    WidgetMessage::GetInstance()->ShowMessageKeep(tr("正在连接"), false, NULL);
}

void Widget_WIfiSetting::slotWifiConnected()
{
    //
    LOG_D("已连接序号%d，连接序号%d", _connected_index, _connect_index);
    if (_connected_index == _connect_index) {
        return;
    }

    // 连接成功
    WidgetMessage::GetInstance()->ShowMessageHide(tr("连接成功"), false, NULL, 1);

    if (_connect_index>=0)
    {
        // 修改连接显示位置
        // 获取这次点击的item
        QListWidgetItem* item = ui->list_wifi->item(_connect_index);
        // 获取item里面的控件
        ButtonType3* bt = (ButtonType3*)ui->list_wifi->itemWidget(item);
        // 该控件设置成已连接
        bt->setConnected(tr("已连接"));
    }
    // 清除原连接显示
    if (_connect_index>=0 && _connected_index>=0)
    {
        // _curren_index保存了原来的连接wifi
        QListWidgetItem *item = ui->list_wifi->item(_connected_index);
        // 原来的已连接清除
        ButtonType3* bt = (ButtonType3*)ui->list_wifi->itemWidget(item);
        bt->setConnected(tr(""));
    }
    // 保存当前连接wifi的index
    _connected_index = _connect_index;

}

void Widget_WIfiSetting::slotShowOpen()
{
    WidgetMessage::GetInstance()->ShowMessageKeep(tr("正在打开"), false, NULL);
}
