#include "widgetRun.h"
#include "ui_widgetRun.h"
#include "widget_base.h"
#include "managerbkview.h"
#include "widget_mainmenu.h"
#include "task/face/taskface.h"
#include "global.h"
#include "task_exe.h"
#include "net/eth_svc.h"
#include "net/wifi_svc.h"
#include "file_ops.h"
#include "base/utils/mixShell.h"
#include "widgetmessage.h"
#include <QProcess>
#include <QWSServer>
#include <QPainter>

#define PRESS_AREA_Y    300
#define KERNEL_V_FILE   "/proc/macaddr"

widgetRun::widgetRun(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widgetRun),
    _welcomText(tr("设备脱机")),
    _qrTimerIsRun(true)
{
    // 初始化属性
#if (DEVICE_USE_TYPE==READER)
    if(g_contrljoint.transferMode==SENDMODE_WG)
    {
        _welcomText = tr("欢迎使用");
    }
#elif (DEVICE_USE_TYPE==DCTR_40 || DEVICE_USE_TYPE==DCTR_YT)
    _welcomText = tr("欢迎使用");
#endif
    // 获取信号发送器实例
    _sender = SignalSender::getInstance();
    _net_status = 0;

    ui->setupUi(this);
    // 设置窗口属性
    this->setWindowFlags(Qt::FramelessWindowHint);
    // 设置窗体透明后显示绿色
    setAttribute(Qt::WA_TranslucentBackground);
    QWSServer::setBackground(QColor(0, 0, 0, 0));
    setFocusPolicy(Qt::NoFocus);

    // 子控件大小设置
    // 设置信息显示框的高度
    ui->det_info->setMaximumHeight(SCREEN_HEIGHT*0.164);
    ui->det_info->setMinimumHeight(SCREEN_HEIGHT*0.164);

    //
    ui->show_date->setStyleSheet("#show_date{font-size:35px;}");
    ui->show_time->setStyleSheet("#show_time{font-size:65px;}");
    ui->show_name->setStyleSheet("#show_name{font-size:55px;}");

    // 更新时间（时间显示即时更新）
    slotUpdateTime();
    connect(&_timer_show, SIGNAL(timeout()), this, SLOT(slotUpdateTime()));
    _timer_show.start(1000);
    // 绑定长按超时（实现长按进入设置界面）
    connect(&_timer, SIGNAL(timeout()), this, SLOT(slotPressScreen()));
    // 人脸位置监听更新框
    connect(_sender, SIGNAL(signalForDraw()), this, SLOT(slotDrawFaceArea()));
    // 网络状态图标，以及平台心跳状态图标更新消息监听
    connect(_sender, SIGNAL(signalEthOnline()), this, SLOT(slotEthOn()));
    connect(_sender, SIGNAL(signalEthOffline()), this, SLOT(slotEthOff()));
    connect(_sender, SIGNAL(signalWifiConnected()), this, SLOT(slotWifiOn()));
    connect(_sender, SIGNAL(signalWifiDisConnected()), this, SLOT(slotWifiOff()));
    connect(_sender, SIGNAL(signalBeatSuccess()), this, SLOT(slotBeatSuccess()));
    connect(_sender, SIGNAL(signalBeatFailed()), this, SLOT(slotBeatFailed()));

    // 应用提示消息提示框
    connect(_sender, SIGNAL(signalMessageUI(const QString&,char*,int)), this, SLOT(SlotShowMsg(const QString&,char*,int)));

    // 唤醒屏幕并倒计时
    connect(_sender, SIGNAL(signalScreenOnTimeout()), this, SLOT(slotShowCamera()));
    // 唤醒人脸检测
    connect(_sender, SIGNAL(signalWakeFaceDetect()), this, SLOT(slotShowCamera()));
#if (DEVICE_USE_TYPE==READER)
    // 设备脱机
    connect(_sender, SIGNAL(signalRs485Online(int)), this, SLOT(slotRs485Online(int)));
#endif

    // 界面开关
    connect(_sender, SIGNAL(signalRunUIShow(bool)), this, SLOT(slotWinShow(bool)));
    // 修改欢迎词
    connect(_sender, SIGNAL(signalWelcomText(const QString&)), this, SLOT(SlotWelcomtext(const QString&)));

    // 检查运行状态，更新属性
    // 检查网络状态
    switch (eth_svc_GetState())
    {
    case LINK_UP_DHCPED:
    case LINK_UP_STATIC:
        _net_status |= ETH_ONLIEN_MASK;
        break;
    default:
        break;
    }

    switch (wifi_svc_GetStatus())
    {
    case WIFI_STATE_CONNECTED:
        _net_status |= WIFI_ONLINE_MASK;
        break;
    default:
        break;
    }
    updateNetIcon();

    // 显示应用程序版本号
    ui->show_version->setText(APP_VERSION);
    ui->show_version->setStyleSheet("#show_version{font-size:12px;}");

    // 显示芯片温度
    char tmp_str[16] = {0};
    file_read("/sys/class/thermal/thermal_zone0/temp", tmp_str, 8);
    LOG_I("芯片温度：%s\n", tmp_str);
    ui->show_cpu_temp->setStyleSheet("#show_cpu_temp{font-size:12px;}");
    ui->show_cpu_temp->setText(QString::fromLocal8Bit("%1℃").arg(atoi(tmp_str)/1000.0));

    // 显示内核版本号
    memset(tmp_str, 0, 16);
    if (-1!=file_read(KERNEL_V_FILE, tmp_str, 16))
    {
        LOG_I("内核版本：%s\n", tmp_str);
        //tmp_str[strlen(tmp_str)-1] = 0;
        ui->kernel_v->setText(QString::fromLocal8Bit(tmp_str));
    }
    ui->kernel_v->setStyleSheet("#kernel_v{font-size:12px;}");

    // 显示欢迎语
    ui->show_name->setText(_welcomText);

    // debug
    ui->debug_label->hide();
    ui->qrscan_test->hide();
    ui->label->setStyleSheet("background-color:rgb(0,0,0);");
    //ui->rgb_light->hide();
    //ui->rgb_label->hide();

    this->showMaximized();
}

widgetRun::~widgetRun()
{
    disconnect(&_timer, SIGNAL(timeout()), this, SLOT(slotPressScreen()));
    disconnect(_sender, SIGNAL(signalForDraw()), this, SLOT(slotDrawFaceArea()));
    _timer_show.stop();
    disconnect(&_timer_show, SIGNAL(timeout()), this, SLOT(slotUpdateTime()));
    delete ui;
}

void widgetRun::slotShowCamera()
{
    if (!this->isHidden())
        TaskFace::GetInstance()->LeaveMenu();
}

void widgetRun::slotHideCamera()
{

}

void widgetRun::SlotShowMsg(const QString &msg, char *voiceFile, int type)
{
    ui->show_name->setText(msg);
    WidgetMessage::GetInstance()->ExecMessageHeadHide(msg, true, voiceFile, type);
    ui->show_name->setText(_welcomText);
}

void widgetRun::SlotWelcomtext(const QString &text)
{
    _welcomText = text;
}

#if (DEVICE_USE_TYPE==READER)
void widgetRun::slotRs485Online(int sta)
{
    switch (sta)
    {
    case 0:
        _welcomText = tr("设备脱机");
        break;
    case 1:
        _welcomText = tr("欢迎使用");
        break;
    case 3:
        _welcomText = tr("设备重号");
        break;
    default:
        break;
    }
    ui->show_name->setText(_welcomText);
}
#endif

#define CAMERA_HIGHT_LIMIT 1050 // 1280-210=1070
void widgetRun::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)
#if 1
    QPainter painter(this);
    QPen pen(Qt::green, 5);
    painter.setPen(pen);
    faces_detected* face = NULL;
#ifdef FACE_ONEMORE
    struct list_head* face_list = TaskFace::GetInstance()->GetFaceList();
    if (NULL==face_list)
    {
        return ;
    }
    struct list_head* node = face_list->next;
#endif

    if (0!=TaskFace::GetInstance()->LockFaceList())
    {
        LOG_E("框脸，拿锁失败，返回\n");
        return ;
    }

    int face_count = TaskFace::GetInstance()->GetFaceCount();
#ifdef FACE_ONEMORE
    int p_diff = (char*)(&face->node)-(char*)face;
    //LOG_D("face node diff %d  ", p_diff);
#endif
    for(int i=0;i<face_count;i++)
    {
        // 遍历face list，框出人脸，如果识别到的人脸，显示出名字
#ifdef FACE_ONEMORE
        face = (faces_detected*)((char*)node - p_diff);
#else
        face = &face_det_svc.face;
#endif
        if (NULL==face)
        {
            LOG_I("警告，获取EV_DIALOG_EXIT的人脸为空指针");
        }
        //LOG_D("人脸活体状态 %d", face->is_living);
        // 活体绿，非活体红
        if (face->is_living)
        {
            pen.setWidth(5);
            pen.setColor(Qt::green);
            painter.setPen(pen);
        }
        else
        {
            pen.setWidth(5);
            pen.setColor(Qt::red);
            painter.setPen(pen);
        }
        // y坐标不超过底部
        face->rect.rect[1] = face->rect.rect[1]<CAMERA_HIGHT_LIMIT?face->rect.rect[1]:CAMERA_HIGHT_LIMIT;
        face->rect.rect[3] = face->rect.rect[3]<CAMERA_HIGHT_LIMIT?face->rect.rect[3]:CAMERA_HIGHT_LIMIT;
        // 坐标距离小于30,忽略
        if ((face->rect.rect[2]-face->rect.rect[0])<30
                || (face->rect.rect[3]-face->rect.rect[1])<30)
            continue ;
        // 左上
        painter.drawLine(QPoint(face->rect.rect[0], face->rect.rect[1]),
                QPoint(face->rect.rect[0]+30, face->rect.rect[1]));
        painter.drawLine(QPoint(face->rect.rect[0], face->rect.rect[1]),
                QPoint(face->rect.rect[0], face->rect.rect[1]+30));
        // 右上
        painter.drawLine(QPoint(face->rect.rect[2]-30, face->rect.rect[1]),
                QPoint(face->rect.rect[2], face->rect.rect[1]));
        painter.drawLine(QPoint(face->rect.rect[2], face->rect.rect[1]),
                QPoint(face->rect.rect[2], face->rect.rect[1]+30));
        // 左下
        painter.drawLine(QPoint(face->rect.rect[0], face->rect.rect[3]),
                QPoint(face->rect.rect[0]+30, face->rect.rect[3]));
        painter.drawLine(QPoint(face->rect.rect[0], face->rect.rect[3]),
                QPoint(face->rect.rect[0], face->rect.rect[3]-30));
        // 右下
        painter.drawLine(QPoint(face->rect.rect[2], face->rect.rect[3]),
                QPoint(face->rect.rect[2]-30, face->rect.rect[3]));
        painter.drawLine(QPoint(face->rect.rect[2], face->rect.rect[3]),
                QPoint(face->rect.rect[2], face->rect.rect[3]-30));

        if (NULL!=face->name)
        {
            // 识别到人脸了
        }
#ifdef FACE_ONEMORE
        node = node->next;
#endif
    }
    TaskFace::GetInstance()->UnLockFaceList();
#endif
}

#define PRESS_SCREEN_TIME_OUT 4000              // 定义长按超时时间
void widgetRun::mousePressEvent(QMouseEvent *e)
{
    if (e->y()<PRESS_AREA_Y)
    {
        LOG_I("开始长按计时");
        _timer.start(PRESS_SCREEN_TIME_OUT);
    }
}

void widgetRun::mouseReleaseEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
    if (_timer.isActive())
    {
        LOG_I("长按结束，取消长按计时");
        _timer.stop();
    }
}

// 网络图标的显示策略
void widgetRun::updateNetIcon()
{
    if (_net_status&BEAT_SUCCESS_MASK)
    {
        // 服务在线，优先级最高
        if (_net_status&ETH_ONLIEN_MASK)
        {
            ui->show_net->setStyleSheet(QString("border-image:url(%1/net_on.png);").arg(UI_IMG_DIR));
        }
        else if (_net_status&WIFI_ONLINE_MASK)
        {
            ui->show_net->setStyleSheet(QString("border-image:url(%1/wifi_4.png);").arg(UI_IMG_DIR));
        }
        g_BaseInfo.deviceStatusNet |= DEVICESTATUS_MASK_ONLINE;
    }
    else if (_net_status&ETH_ONLIEN_MASK)
    {
        // 以太网在线,服务离线，优先级较高
        ui->show_net->setStyleSheet(QString("border-image:url(%1/eth_beat_failed.png);").arg(UI_IMG_DIR));
        g_BaseInfo.deviceStatusNet |= DEVICESTATUS_MASK_ONLINE;
    }
    else if (_net_status&WIFI_ONLINE_MASK)
    {
        ui->show_net->setStyleSheet(QString("border-image:url(%1/eth_beat_failed.png);").arg(UI_IMG_DIR));
        g_BaseInfo.deviceStatusNet |= DEVICESTATUS_MASK_ONLINE;
    }
    else
    {
        ui->show_net->setStyleSheet(QString("border-image:url(%1/net_off.png);").arg(UI_IMG_DIR));
        g_BaseInfo.deviceStatusNet &= ~DEVICESTATUS_MASK_ONLINE;
    }
}

void widgetRun::slotUpdateTime()
{
    QLocale locale =  QLocale::Chinese;
    const QDateTime& date = QDateTime::currentDateTime();
    //ui->show_date->setText(locale.toString(date, "yyyy/MM/dd   ddd"));
    ui->show_date->setText(locale.toString(date, "yyyy/MM/dd"));
    ui->show_time->setText(date.toString("hh:mm"));

#if 1
    // 更新cup温度
    char tmp_str[8] = {0};
    file_read("/sys/class/thermal/thermal_zone0/temp", tmp_str, 8);
    ui->show_cpu_temp->setText(QString::fromLocal8Bit("%1℃").arg(atoi(tmp_str)/1000.0));
#endif

    // 检查是否到了指定时间
    // 时间戳-57600，对24小时取余，为0就是 00:00:00，如果余数是偏移，表示时间到了
    qint64 sec = date.toMSecsSinceEpoch();
    //LOG_I("当前时间ms %lld", sec);
    sec = sec/1000;
    //LOG_I("当前时间s %lld", sec);
    // 计算24点偏移
    sec = (sec-57600)%86400;
    //10:05 7500
    // 10:10
    //sec = (sec-7800)%86400;
    //LOG_I("当前时间偏移24点 %lld", sec);
    if (g_BaseInfo.offtime_s <= sec && sec < g_BaseInfo.offtime_s+10)
    {
#if 0
        // 获取上传日志实例，执行线程
        Task_uploadLogs* uplogs = Task_uploadLogs::getInstance(UPLD_LOGS);
        if (!uplogs->isRunning())
            uplogs->start();
#endif
    }

    ui->rgb_light->setText(QString("%1").arg(g_BaseInfo.rgbLight));
}

void widgetRun::slotDrawFaceArea()
{
#if 1
    QRegion region;
    QRegion last = _last_region;            // 保存上一次区域
    // 获取人脸列表
    struct list_head* face_list = TaskFace::GetInstance()->GetFaceList();
    int face_count = TaskFace::GetInstance()->GetFaceCount();
    faces_detected* face = NULL;
#ifdef FACE_ONEMORE
    // 获取下一个人脸的node
    struct list_head* node = face_list->next;
    // p_diff 是用node 计算 faces_detected地址的中间变量
    int p_diff = (char*)(&face->node)-(char*)face;
    //LOG_D("face node diff1 %d  ", p_diff);
#endif
    // face list 加锁
    //face_det_svc_lock_face_list();
    // 添加人脸区域
    for(int i=0;i<face_count;i++)
    {
#ifdef FACE_ONEMORE
        face = (faces_detected*)((char*)node - p_diff);
#else
        face = & face_det_svc.face;
#endif
        if (NULL==face)
        {
            LOG_I("警告，获取的人脸为空指针");
        }
        int x1 = face->rect.rect[0]<5?0:face->rect.rect[0]-5;
        int y1 = face->rect.rect[1]<5?0:face->rect.rect[1]-5;
        QRect rect(x1, y1,
                   face->rect.rect[2]+5, face->rect.rect[3]+5);
        region = region.united(rect);
#ifdef FACE_ONEMORE
        node = node->next;
#endif
    }
    // face list 解锁
    //face_det_svc_unlock_face_list();
    // 区域不为空，保存这一次的区域
    if (!region.isEmpty())
    {
        _last_region = region;
    }
    region = region.united(last);           // 初始化更新区域，包括本次需要更新区域和上一次更新区域
    if (region.isEmpty())
    {
        LOG_I("区域为空，使用全屏区域");
        region = region.united(QRect(0, 0, 720, 1280));
    }

    this->repaint(region);
#endif
}

void widgetRun::slotNetIconSet()
{

}

void widgetRun::slotPressScreen()
{
    LOG_I("长按发生，关掉计时器,切换到设置界面");
    _timer.stop();
    Widget_Base* w = new Widget_Mainmenu(0, tr("主菜单"));
    ManagerBkView* _managerBkView = ManagerBkView::getInstance();
    w->setBackPage(this);
    _managerBkView->addWidgetShow(w);
    _managerBkView->show();
    this->hide();
    TaskFace::GetInstance()->EnterMenu();
    SignalSender* send = SignalSender::getInstance();
    // 修改息屏倒计时时间
    send->sendSignalChangeOutTime(BLANK_TIMEOUT_MS_SETTING);
    // 设备进入设置界面
    g_BaseInfo.deviceStatusSwitch |= DEVICESTATUS_MASK_MENUSETTING;
}

void widgetRun::slotEthOn()
{
    _net_status |= ETH_ONLIEN_MASK;
    updateNetIcon();
}

void widgetRun::slotEthOff()
{
    _net_status &= ~ETH_ONLIEN_MASK;
    updateNetIcon();
}

void widgetRun::slotWifiOn()
{
    _net_status |= WIFI_ONLINE_MASK;
    updateNetIcon();
    // 保存当前连接的ssid,提交线程处理
    task_exe_req* req = (task_exe_req*)calloc(sizeof(task_exe_req), 1);
    req->task_num = 1;
    req->tasks[0] = task_exe_WifiSsidCopy;
    task_exe_CommitReq(req);
}

void widgetRun::slotWifiOff()
{
    _net_status &= ~WIFI_ONLINE_MASK;
    updateNetIcon();
}

void widgetRun::slotBeatSuccess()
{
    _net_status |= BEAT_SUCCESS_MASK;
    updateNetIcon();
}

void widgetRun::slotBeatFailed()
{
    _net_status &= ~BEAT_SUCCESS_MASK;
    updateNetIcon();
}



