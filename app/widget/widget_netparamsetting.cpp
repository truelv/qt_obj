// 网络参数设置界面
#include "widget_netparamsetting.h"
#include "ui_widget_netparamsetting.h"
#include "public/devfile.h"
#include "public/publicfun.h"
#include "DB/dbyt.h"
#include "widgetmessage.h"
#include <QMargins>

#ifdef __cplusplus
extern "C" {
#endif
#include "network/net_utils/net_utils.h"
#include "network/net_utils/ip_config.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "net/eth_svc.h"
#ifdef __cplusplus
}
#endif

#define LOGTAG "widget_netParam"

// 构造函数
Widget_NetParamSetting::Widget_NetParamSetting(Widget_Base *parent, const QString &title) :
    Widget_Base(parent, title),
    ui(new Ui::Widget_NetParamSetting)
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
    ui->confirm_bt->setStyleSheet("font: 45pt'微软雅黑';");

    //IP规则
    QString pattern=QString::fromUtf8("^((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)$");
    QRegExp RegExp(pattern);
    //端口号规则
    //(0-65535)
    QString pattern1=QString::fromUtf8("^(?!0)(?:[0-9]{1,5}|65535)$");
    QRegExp RegExp1(pattern1);

    // 检查设备是否开启以太网dhcp
    _ethIsDhcp = g_LocalNetInfo.IPMode==1?true:false;
    if (_ethIsDhcp)
    {
        // ip输入框设置不可操作
        ipEditDisable();
    }
    // 初始化控件
    ui->eth_is_dhcp->setChecked(_ethIsDhcp);
    // 显示保存的ip等信息
    ui->eth_ip->setValidator(new QRegExpValidator(RegExp, ui->eth_ip));
    ui->eth_ip->setText(QString("%1.%2.%3.%4")
                        .arg(g_LocalNetInfo.LocalIP[0])
            .arg(g_LocalNetInfo.LocalIP[1])
            .arg(g_LocalNetInfo.LocalIP[2])
            .arg(g_LocalNetInfo.LocalIP[3]));

    ui->eth_gateway->setValidator(new QRegExpValidator(RegExp, ui->eth_gateway));
    ui->eth_gateway->setText(QString("%1.%2.%3.%4")
                             .arg(g_LocalNetInfo.GateWay[0])
            .arg(g_LocalNetInfo.GateWay[1])
            .arg(g_LocalNetInfo.GateWay[2])
            .arg(g_LocalNetInfo.GateWay[3]));

    ui->eth_mask->setValidator(new QRegExpValidator(RegExp, ui->eth_mask));
    ui->eth_mask->setText(QString("%1.%2.%3.%4")
                          .arg(g_LocalNetInfo.SubNetMask[0])
            .arg(g_LocalNetInfo.SubNetMask[1])
            .arg(g_LocalNetInfo.SubNetMask[2])
            .arg(g_LocalNetInfo.SubNetMask[3]));

    ui->eth_dns->setValidator(new QRegExpValidator(RegExp, ui->eth_dns));
    ui->eth_dns->setText(QString("%1.%2.%3.%4")
                         .arg(g_LocalNetInfo.MasterDNS[0])
            .arg(g_LocalNetInfo.MasterDNS[1])
            .arg(g_LocalNetInfo.MasterDNS[2])
            .arg(g_LocalNetInfo.MasterDNS[3]));

    // dhcp控件信号绑定槽
    connect(ui->eth_is_dhcp, SIGNAL(stateChanged(int)), this, SLOT(on_eth_is_dhcp_stateChanged(int)));
    connect(ui->confirm_bt, SIGNAL(clicked()), this, SLOT(on_confirm_bt_clicked()));
    // 服务设置显示保存内容
    ui->server_port->setValidator(new QRegExpValidator(RegExp1, ui->server_port));
    ui->server_port->setText(QString("%1").arg(g_LocalNetInfo.ServerPort));

    ui->server_ip->setValidator(new QRegExpValidator(RegExp, ui->server_ip));
    ui->server_ip->setText(QString("%1.%2.%3.%4")
                           .arg(g_LocalNetInfo.ServerIP[0])
            .arg(g_LocalNetInfo.ServerIP[1])
            .arg(g_LocalNetInfo.ServerIP[2])
            .arg(g_LocalNetInfo.ServerIP[3]));
    // 判断是link是否连接，如果是链路断开，这里再次关闭，以太网的所有操作
    int link_state = g_BaseInfo.deviceStatusNet&DEVICESTATUS_MASK_LINK;
    if (0==link_state)
    {
        ui->link_state->setText(tr("链路断开"));
    } else
        ui->link_state->setText(tr("链路连接"));

    // 默认网关，dns获取焦点，上面一半收起，失去，展开
    ui->eth_gateway->installEventFilter(this);
    ui->eth_dns->installEventFilter(this);

    this->showFullScreen();
}

// 析构函数
Widget_NetParamSetting::~Widget_NetParamSetting()
{
    delete _layout;
    delete ui;
}

void Widget_NetParamSetting::autoToBack()
{
    ui->confirm_bt->setFocus();
    Widget_Base::autoToBack();
}

// 禁止编辑以太网信息
void Widget_NetParamSetting::ipEditDisable()
{
    ui->eth_ip->setEnabled(false);
    ui->eth_ip->setStyleSheet("background-color: rgb(131, 131, 131);color: rgb(0, 0, 0);");
    ui->eth_gateway->setEnabled(false);
    ui->eth_gateway->setStyleSheet("background-color: rgb(131, 131, 131);color: rgb(0, 0, 0);");
    ui->eth_mask->setEnabled(false);
    ui->eth_mask->setStyleSheet("background-color: rgb(131, 131, 131);color: rgb(0, 0, 0);");
    ui->eth_dns->setEnabled(false);
    ui->eth_dns->setStyleSheet("background-color: rgb(131, 131, 131);color: rgb(0, 0, 0);");
}

// 允许设置ip信息
void Widget_NetParamSetting::ipEditEnable()
{
    ui->eth_ip->setEnabled(true);
    ui->eth_ip->setStyleSheet("background-color: rgb(255, 255, 255);color: rgb(0, 0, 0);");
    ui->eth_gateway->setEnabled(true);
    ui->eth_gateway->setStyleSheet("background-color: rgb(255, 255, 255);color: rgb(0, 0, 0);");
    ui->eth_mask->setEnabled(true);
    ui->eth_mask->setStyleSheet("background-color: rgb(255, 255, 255);color: rgb(0, 0, 0);");
    ui->eth_dns->setEnabled(true);
    ui->eth_dns->setStyleSheet("background-color: rgb(255, 255, 255);color: rgb(0, 0, 0);");
}

// 禁止操作dhcp
void Widget_NetParamSetting::dhcpEditDisable()
{
    ui->eth_is_dhcp->setEnabled(false);
}

// 允许操作dhcp开关
void Widget_NetParamSetting::dhcpEditEnable()
{
    ui->eth_is_dhcp->setEnabled(true);
}

bool Widget_NetParamSetting::eventFilter(QObject *obj, QEvent *e)
{
    //LOG_D("获取事件 %d ", e->type());
    if (e->type()==QEvent::FocusIn)
    {
        //LOG_D("获取焦点");
        if (obj==ui->eth_gateway || obj==ui->eth_dns)
        {
            LOG_D("网关获取焦点");
            ui->fold_frame->hide();
        }
    }
    else if (e->type()==QEvent::FocusOut)
    {
        //LOG_D("失去焦点");
        if (obj==ui->eth_gateway || obj==ui->eth_dns)
        {
            LOG_D("网关失去焦点");
            ui->fold_frame->show();
        }
    }
    return QWidget::eventFilter(obj, e);
}

// 点击确认按键槽
void Widget_NetParamSetting::on_confirm_bt_clicked()
{
    char* str;
    QString StrTemp;
    unsigned char btempIP[4]={0};
    if (!_ethIsDhcp)
    {
        g_LocalNetInfo.IPMode=0;
        //写本机IP
        StrTemp=ui->eth_ip->text();
        if(Publicfun::NetParamCheck(StrTemp))
        {
            ui->eth_ip->setFocus();
            WidgetMessage::GetInstance()->ShowMessageHide(tr("IP格式异常"), false, NULL, 1);
            return;
        }
        str = ui->eth_ip->text().toAscii().data();
        sscanf(str, "%d.%d.%d.%d", &btempIP[0], &btempIP[1], &btempIP[2], &btempIP[3]);
        g_LocalNetInfo.LocalIP[0] = btempIP[0];
        g_LocalNetInfo.LocalIP[1] = btempIP[1];
        g_LocalNetInfo.LocalIP[2] = btempIP[2];
        g_LocalNetInfo.LocalIP[3] = btempIP[3];
        //写网关
        StrTemp=ui->eth_gateway->text();
        if(Publicfun::NetParamCheck(StrTemp))
        {
            ui->eth_gateway->setFocus();
            WidgetMessage::GetInstance()->ShowMessageHide(tr("IP格式异常"), false, NULL, 1);
            return;
        }
        str = ui->eth_gateway->text().toAscii().data();
        sscanf(str, "%d.%d.%d.%d", &btempIP[0], &btempIP[1], &btempIP[2], &btempIP[3]);
        g_LocalNetInfo.GateWay[0] = btempIP[0];
        g_LocalNetInfo.GateWay[1] = btempIP[1];
        g_LocalNetInfo.GateWay[2] = btempIP[2];
        g_LocalNetInfo.GateWay[3] = btempIP[3];
        //写子网掩码
        StrTemp=ui->eth_mask->text();
        if(Publicfun::NetParamCheck(StrTemp))
        {
            ui->eth_mask->setFocus();
            WidgetMessage::GetInstance()->ShowMessageHide(tr("IP格式异常"), false, NULL, 1);
            return;
        }
        str = ui->eth_mask->text().toAscii().data();
        sscanf(str, "%d.%d.%d.%d", &btempIP[0], &btempIP[1], &btempIP[2], &btempIP[3]);
        g_LocalNetInfo.SubNetMask[0] = btempIP[0];
        g_LocalNetInfo.SubNetMask[1] = btempIP[1];
        g_LocalNetInfo.SubNetMask[2] = btempIP[2];
        g_LocalNetInfo.SubNetMask[3] = btempIP[3];
        //写DNS
        StrTemp=ui->eth_dns->text();
        if(Publicfun::NetParamCheck(StrTemp))
        {
            ui->eth_dns->setFocus();
            WidgetMessage::GetInstance()->ShowMessageHide(tr("IP格式异常"), false, NULL, 1);
            return;
        }
        str = ui->eth_dns->text().toAscii().data();
        sscanf(str, "%d.%d.%d.%d", &btempIP[0], &btempIP[1], &btempIP[2], &btempIP[3]);
        g_LocalNetInfo.MasterDNS[0] = btempIP[0];
        g_LocalNetInfo.MasterDNS[1] = btempIP[1];
        g_LocalNetInfo.MasterDNS[2] = btempIP[2];
        g_LocalNetInfo.MasterDNS[3] = btempIP[3];

    }
    else
    {
        g_LocalNetInfo.IPMode=1;
    }
    // 保存服务器信息
    //写服务IP
    StrTemp=ui->server_ip->text();
    if(Publicfun::NetParamCheck(StrTemp))
    {
        ui->server_ip->setFocus();
        WidgetMessage::GetInstance()->ShowMessageHide(tr("IP格式异常"), false, NULL, 1);
        return;
    }
    str = ui->server_ip->text().toAscii().data();
    sscanf(str, "%d.%d.%d.%d", &btempIP[0], &btempIP[1], &btempIP[2], &btempIP[3]);
    g_LocalNetInfo.ServerIP[0] = btempIP[0];
    g_LocalNetInfo.ServerIP[1] = btempIP[1];
    g_LocalNetInfo.ServerIP[2] = btempIP[2];
    g_LocalNetInfo.ServerIP[3] = btempIP[3];
    g_LocalNetInfo.ServerPort = ui->server_port->text().toInt();

    //写网络参数
    DevFile::CheckWriteType(NETPARADATA,0, &g_LocalNetInfo, sizeof(ST_LOCALNETINFO));
    //写网络配置文件ini
    DevFile::WriteNetParaFileInfo(NETPARAFILE ,&g_LocalNetInfo);

    if (g_LocalNetInfo.IPMode==1)
    {
        // 启动dhcp
        eth_svc_StartDhcp();
    }
    else
    {
        eth_svc_StopDhcpIfExists();
        // 设置ip
        eth_svc_SetIp();
    }

    // 修改权限下载地址
#if (DEVICE_USE_TYPE==DCTR_YT)
    // http://172.16.6.108:8083/easytong_app/faceAccess
    const QString& url = QString("http://%1:%2/easytong_app/faceAccess")
            .arg(ui->server_ip->text()).arg(ui->server_port->text());
#elif (DEVICE_USE_TYPE==DCTR_40)
    const QString& url = QString("http://%1:%2")
            .arg(ui->server_ip->text()).arg(ui->server_port->text());
#elif (DEVICE_USE_TYPE==READER)
    const QString& url = QString("http://%1:%2")
            .arg(ui->server_ip->text()).arg(ui->server_port->text());
#endif
    int len = URL_BUFF_LEN;
    int slen = url.length();
    len = (slen<len?slen:len-1);
    const QByteArray& urlBy = url.toAscii();
    // 写入内存
    memcpy(g_platParam.authInfoUrl, urlBy.data(), len);
    g_platParam.authInfoUrl[len] = 0;
    // 写入数据库
    DBYt::GetInstance()->UpdateKV("PlatParamModule", "authInfoUrl",
                                  g_platParam.authInfoUrl);
#if 0
    sprintf(g_platParam.authInfoUrl, "http://%d.%d.%d.%d:%d",
            g_LocalNetInfo.ServerIP[0],g_LocalNetInfo.ServerIP[1],
            g_LocalNetInfo.ServerIP[2],g_LocalNetInfo.ServerIP[3],
            g_LocalNetInfo.ServerPort);
    DBYt::GetInstance()->UpdateKV("PlatParamModule", "authInfoUrl",
                                  g_platParam.authInfoUrl);
#endif
    // 弹框提示
    WidgetMessage::GetInstance()->ShowMessageHide(tr("设置成功"), false, NULL, 1);

}

// 点击dhcp槽
void Widget_NetParamSetting::on_eth_is_dhcp_stateChanged(int state)
{
    bool check = 0==state?false:true;;
    LOG_D("dhcp state change %d ", state);
    if (_ethIsDhcp && !check)
    {
        // 从dhcp到取消
        ipEditEnable();
        _ethIsDhcp = false;
    }
    else if (!_ethIsDhcp && check)
    {
        // 从static到取消
        ipEditDisable();
        _ethIsDhcp = true;
    }

}
