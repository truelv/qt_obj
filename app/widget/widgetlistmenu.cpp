/**
 * 列出菜单按键控件，根据传入的参数列出按键菜单
*/
#include "widgetlistmenu.h"
#include "items/buttontype2.h"  //  菜单按键类型的button
#include "managerbkview.h"
#include "global.h"
#include "widgetlistparam.h"
#include "dialog/dialog_modesetting.h"
#include "dialog/dialog_facesetting.h"
#include "base/api/led.h"
#include "dialog/dialog_rfidsignalsetting.h"
#include "dialog/dialog_showtextsetting.h"
#include "dialog/dialog_soundtypesetting.h"
#include "widget_netparamsetting.h"
#include "widget_wifiqrscansetting.h"
#include "widget_wifisetting.h"
#include "dialog/dialog_backlightsetting.h"
#include "dialog/dialog_volumesetting.h"
#include "dialog/dialog_datetimesetting.h"
#include "hotap/widget_wifihotap.h"
#include "base/utils/mixShell.h"
#include "widgetmessage.h"
#include "task/uploadLogs/task_uploadLogs.hpp"
#include "DB/dbyt.h"
#include <QVariant>

static LED_STATE s_ledOn = LED_OFF;

WidgetListmenu::WidgetListmenu(Widget_Base *parent, item_button* items, const QString &title) :
    Widget_Base(parent, title),
    _baseDialog(NULL),
    _msgDialog(NULL)
{
    if (NULL==items)
        return ;

    _btList.clear();
    _itemList = items;
    _item_len = 0;

    int pos_y = TOP_PADING;
    for (int i=0;BUTTON_NULL!=_itemList[i].type;i++,_item_len++)
    {
        ButtonType2* bt = new ButtonType2;
        bt->setParent(this);
        bt->move(50, pos_y+i*BUTTONS_HIGHT_SPACE);
        bt->setText(QString(tr("%1 %2")).arg(i+1).arg(tr(_itemList[i].name)));
        bt->show();
        bt->setProperty("type", _itemList[i].type);
        bt->setProperty("index", i);
        connect(bt, SIGNAL(clicked()), this, SLOT(slotButtonClicked()));
        _btList.append(bt);
    }
}

WidgetListmenu::~WidgetListmenu()
{
    // 清理所有构造函数中创建的控件
    foreach (QWidget* bt, _btList)
    {
        delete bt;
    }
}

void WidgetListmenu::autoToBack()
{
    // 自动退出，如果有弹框，销毁
    if (NULL!=_msgDialog)
    {
        _msgDialog->hideKeyBoard();
        _msgDialog->reject();
        _msgDialog = NULL;
    }

    if (NULL!=_baseDialog)
    {
        // 该界面有弹框
        _baseDialog->hideKeyBoard();
        _baseDialog->reject();
        delete _baseDialog;
        _baseDialog = NULL;
    }
    Widget_Base::autoToBack();
}

void WidgetListmenu::slotButtonClicked()
{
    Widget_Base* w = NULL;
    // 获取按键的类型
    QObject* sender = QObject::sender();
    int bt_type = sender->property("type").toInt();
    int bt_index = sender->property("index").toInt();
    LOG_D("发送信号控件类型属性 %d", bt_type);

    // 响应按键
    switch (bt_type)
    {

    case BUTTON_DEVICE_INFO:
        w = new WidgetListParam(0, model_deviceinfo, tr("设备信息"));
        break;

    case BUTTON_NETPARAM_INFO:
        w = new WidgetListParam(0, model_netparaminfo, tr("网络配置信息"));
        break;

    case BUTTON_FACEFEAT_INFO:
        w = new WidgetListParam(0, model_facedetinfo, tr("人脸识别信息"));
        break;
    case BUTTON_DATCNT_INFO:
        w = new WidgetListParam(0, model_datcountinfo, tr("存储数据量信息"));
        break;
    case BUTTON_DATVER_INFO:
        w = new WidgetListParam(0, model_datlocalverinfo, tr("数据版本信息"));
        break;
    case BUTTON_DEVICE_SETTING:
        w = new WidgetListmenu(0, model_deviceSetting, tr("本机设置"));
        break;

    case BUTTON_ADVANCED_SETTING:
        w = new WidgetListmenu(0, model_advancedSetting, tr("高级设置"));
        break;

    case BUTTON_HARDWARE_CONF:
        w = new WidgetListmenu(0, model_hardwareconf, tr("硬件配置"));
        break;

        // 这里开始对话框设置界面
    case BUTTON_MODE_SETTING:
    {
        _baseDialog = new Dialog_ModeSetting(0, tr("模式选择"));
        _baseDialog->exec();
        _baseDialog = NULL;
        return;
        break;
    }

    case BUTTON_FACE_SETTING:
    {
        _baseDialog = new Dialog_FaceSetting(0, tr("人脸检测设置"));
        _baseDialog->exec();
        _baseDialog = NULL;
        return;
        break;
    }

    // 这里对话框设置界面结束
    case BUTTON_UPLOAD_LOGS:
    {
        // 提示正在上传
        WidgetMessage::GetInstance()->ShowMessageKeep(tr("正在上传日志"), false, NULL);
        // 提交打包上传任务，上传任务完成后，发送成功或者失败消息
        // 获取上传日志实例，执行线程
        Task_uploadLogs* uplogs = Task_uploadLogs::getInstance(UPLD_PKG);
        if (!uplogs->isRunning())
            uplogs->start();
        return;
        break;
    }

    case BUTTON_WHITELED_SWITCH:
    {
        if (LED_ON==s_ledOn)
        {
            white_led_ctrl(LED_OFF);
            s_ledOn = LED_OFF;
            ((ButtonType2*)sender)->setText(QString(tr("%1 白光开关（关）")).arg(1));
        }
        else
        {
            white_led_ctrl(LED_ON);
            s_ledOn = LED_ON;
            ((ButtonType2*)sender)->setText(QString(tr("%1 白光开关（开）")).arg(1));
        }
        return ;
        break;
    }

    case BUTTON_RFIDSIGNAL_SETTING:
    {
        _baseDialog = new Dialog_RFIDSignalSetting(0, tr("天线信号设置"));
        _baseDialog->exec();
        _baseDialog = NULL;
        return;
        break;
    }

    case BUTTON_SHOWTEXT_SETTING:
    {
        _baseDialog = new Dialog_ShowtextSetting(0, tr("显示方式设置"));
        _baseDialog->exec();
        _baseDialog = NULL;
        return;
        break;
    }

    case BUTTON_SOUND_SETTING:
    {
        _baseDialog = new Dialog_SoundtypeSetting(0, tr("音频方式设置"));
        _baseDialog->exec();
        _baseDialog = NULL;
        return;
        break;
    }

    case BUTTON_NETPARAM_SETTING:
    {
        w = new Widget_NetParamSetting(0, tr("网络参数设置"));
        break;
    }

    case BUTTON_WIFI_SETTING:
    {
        w = new Widget_WIfiSetting(0, tr("wifi设置"));
        break;
    }

    case BUTTON_WIFI_SCANC:
    {
        w = new Widget_WifiQrscanSetting(0, tr("wifi扫码设置"));
        break;
    }

    case BUTTON_WIFI_HOTAP:
    {
        w = new Widget_WifiHotap(0, tr("运维助手"));
        // 设置倒计时时间为1h
        SignalSender::getInstance()->sendSignalChangeOutTime(BLANK_TIMEOUT_MS_WIIFHOTAP);
        break;
    }

        // 开始弹框设置界面
    case BUTTON_BACKLIGHT_SETTING:
    {
        _baseDialog = new Dialog_BackLightSetting(0, tr("亮度调节"));
        _baseDialog->exec();
        _baseDialog = NULL;
        return ;
        break;
    }

    case BUTTON_VOLUME_SETTING:
    {
        _baseDialog = new Dialog_VolumeSetting(0, tr("音量调节"));
        _baseDialog->exec();
        _baseDialog = NULL;
        return ;
        break;
    }

    case BUTTON_DATE_SETTING:
    {
        _baseDialog = new Dialog_DateTimeSetting(0, tr("时钟设置"));
        _baseDialog->exec();
        _baseDialog = NULL;
        return ;
        break;
    }

        // 高级设置
    case BUTTON_DEVICE_INIT:
        slotDeviceInit();
        return ;
        break;
    case BUTTON_DEVICE_REBOOT:
        slotDeviceReboot();
        return ;
        break;

    case BUTTON_CLEAR_ALL:
        slotClearAll();
        return ;
        break;

    case BUTTON_TIMREBOOT_SWITCH:
        switchTimrebootButton(sender, bt_index);
        return ;
        break;

    default:
        return;
        break;
    }

    ManagerBkView* _managerBkView = ManagerBkView::getInstance();
    w->setBackPage(this);
    _managerBkView->addWidgetShow(w);
    _managerBkView->show();
    this->hide();
}

void WidgetListmenu::slotDeviceReboot()
{
    if (QDialog::Rejected==WidgetMessage::GetInstance()->ExecMessageButton(
                tr("是否确定重启设备"), false, NULL))
        return ;

    LOG_I("执行重启\n");
    if(-1==exeShell("sync;reboot", NULL, 0))
    {
        LOG_E("执行重启，重启设备失败\n");
    }
    qApp->quit();
}

// 设备初始化
void WidgetListmenu::slotDeviceInit()
{
    _msgDialog = WidgetMessage::GetInstance();
    if (QDialog::Rejected==_msgDialog->ExecMessageButton(
                tr("是否确定初始化设备"), false, NULL))
    {
        _msgDialog = NULL;
        return ;
    }
    _msgDialog = NULL;

    LOG_I("执行设备初始化\n");

    // 清理数据库
    // 1
    DBYt::GetInstance()->Del("BaseInfo", "deviceStatusBeat", "0");
    DBYt::GetInstance()->Del("BaseInfo", "platSoftWareVer", "0");
    // 2
    DBYt::GetInstance()->DelTB("LogManage");
    // 3
    DBYt::GetInstance()->DelTB("FaceInfo");
    // 4
    DBYt::GetInstance()->DelTB("VersionInfo");
    // 5
    DBYt::GetInstance()->DelTB("SystemParm");
    // 6
    DBYt::GetInstance()->DelTB("TerminalInfo");
    // 7
    DBYt::GetInstance()->DelTB("DoorInfo");
    // 8
    DBYt::GetInstance()->DelTB("ReaderInfo");
    // 9
    DBYt::GetInstance()->DelTB("accAuthorityInfo");
    // 10
    DBYt::GetInstance()->DelTB("AccBaseInfo");
    // 11
    DBYt::GetInstance()->DelTB("CardAccnumInfo");
    // 12
    DBYt::GetInstance()->DelTB("TimeGroupInfo");
    // 13
    DBYt::GetInstance()->DelTB("DoorHolidayInfo");
    // 14
    DBYt::GetInstance()->DelTB("AccTmpAuthorityInfo");
    // 15
    DBYt::GetInstance()->DelTB("face_img_info");
    // 删除文件
    if (-1==exeShell("rm " PROJECT_DIR_LOG"/* "
                 PROJECT_DIR_TMP"/* -rf", NULL, 0))
    {
        LOG_E("设备初始化，执行删除文件失败\n");
        WidgetMessage::GetInstance()->ShowMessageHide(tr("设备初始化失败"),
                                                      false, NULL, 1);
    }

    LOG_I("设备初始化，开始重启倒计时\n");
    WidgetMessage::GetInstance()->ShowMessageReboot(tr("即将重启"), false, NULL, 5);
}

// 恢复出厂设置
void WidgetListmenu::slotClearAll()
{
    _msgDialog = WidgetMessage::GetInstance();
    if (QDialog::Rejected==_msgDialog->ExecMessageButton(
                tr("是否确定恢复出厂设置"), false, NULL))
    {
        _msgDialog = NULL;
        return ;
    }
    _msgDialog = NULL;

    LOG_I("执行恢复出厂设置\n");
    if (-1==exeShell("rm " PROJECT_DIR_LOG"/* "
                 PROJECT_DIR_TMP"/* "
                 PROJECT_DIR_DATA"/* "
                 "/data/etc/DeviceProType.ini -rf", NULL, 0))
    {
        LOG_E("恢复出厂设置，执行删除文件失败\n");
        WidgetMessage::GetInstance()->ShowMessageHide(tr("恢复出厂失败"),
                                                      false, NULL, 1);
        return;
    }

    // 消息框会执行重启
    WidgetMessage::GetInstance()->ShowMessageReboot(tr("即将重启"), false, NULL, 5);
}

void WidgetListmenu::switchTimrebootButton(QObject* bt, int index)
{
    switch (g_BaseInfo.deviceStatusSwitch&DEVICESTATUS_MASK_REBOOT) {
    case OFF:
        g_BaseInfo.deviceStatusSwitch |= DEVICESTATUS_MASK_REBOOT;
        //db_set_localinfo2("timrebootSwitch", g_LoaclInfo.timrebootSwitch);
        ((ButtonType2*)bt)->setText(QString(tr("%1 %2"))
                                  .arg(index+1)
                                  .arg(tr("凌晨重启（开）")));
        break;
    case DEVICESTATUS_MASK_REBOOT:
    default:
        g_BaseInfo.deviceStatusSwitch &= ~DEVICESTATUS_MASK_REBOOT;
        //db_set_localinfo2("timrebootSwitch", g_LoaclInfo.timrebootSwitch);
        ((ButtonType2*)bt)->setText(QString(tr("%1 %2"))
                                  .arg(index+1)
                                  .arg(tr("凌晨重启（关）")));
        break;
    }
}





