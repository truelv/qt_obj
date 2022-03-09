/**
 * 信号发送类，
 * 自定义信号和发送信号接口，
 */
#include "signalsender.h"

#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include "global.h"
#include "task_exe.h"
#include "base/api/rs.h"
#include "link_handler.h"
#include "net/eth_svc.h"
#include "net/wifi_svc.h"
#ifdef __cplusplus
}
#endif

// 构造函数
SignalSender* SignalSender::_sender = NULL;

// 获取信号发送对象实例
SignalSender *SignalSender::getInstance()
{
    if (NULL==_sender)
        _sender = new SignalSender;

    return _sender;
}

//析构函数
SignalSender::~SignalSender()
{
    _sender = NULL;
}

void SignalSender::sendSignalRs485Online(int sta)
{
    emit signalRs485Online(sta);
}

// 发送信号更新屏幕
void SignalSender::sendSignalForDraw()
{
    emit signalForDraw();
}

void SignalSender::sendSignalWifiScanFailed()
{
    emit signalWifiScanFailed();
}

// 发送信号更新wifi列表
void SignalSender::sendSignalUpdateListWifi()
{
    emit signalUpdateListWifi();
}

// 发送清空wifi列表
void SignalSender::sendSignalClearListWifi()
{
    emit signalUpdateListWifi();
}

void SignalSender::sendSignalWifiOpen()
{
    emit signalWifiOpen();
}

void SignalSender::sendSignalWifiConnecting()
{
    emit signalWifiConnecting();
}

// 发送信号连接wifi，wifi在线
void SignalSender::sendSignalWifiConnected()
{
    emit signalWifiConnected();
}

// 发送信号断开wifi，wifi离线
void SignalSender::sendSignalWifiDisConnected()
{
    emit signalWifiDisConnected();
}

//发送信号以太网上线
void SignalSender::sendSignalEthOnline()
{
    emit signalEthOnline();
}

// 发送信号以太网离线
void SignalSender::sendSignalEthOffline()
{
    emit signalEthOffline();
}

// 发送信号服务请求成功
void SignalSender::sendSignalBeatSuccess()
{
    emit signalBeatSuccess();
}

// 发送信号服务请求失败
void SignalSender::sendSignalBeatFailed()
{
    emit signalBeatFailed();
}

void SignalSender::sendSignalScreenOff()
{
    emit signalScreenOff();
}

void SignalSender::sendSignalScreenOn()
{
    emit signalScreenOn();
}

void SignalSender::sendSignalScreenOnTimeout()
{
    emit signalScreenOnTimeout();
}

void SignalSender::sendSignalWakeFaceDetect()
{
    emit signalWakeFaceDetect();
}

void SignalSender::sendSignalResetToRunWin()
{
    emit signalResetToRunWin();
}

void SignalSender::sendSignalChangeOutTime(int ms)
{
    emit signalChangeOutTime(ms);
}

void SignalSender::sendSignalReboot()
{
    emit signalReboot();
}

void SignalSender::sendSignalSwithcTimer(bool on)
{
    emit signalSwitchTimer(on);
}

void SignalSender::sendSignalFaceUnregistered()
{
    emit signalFaceUnregistered();
}

void SignalSender::sendSignalTofeatFailed(const QString &msg)
{
    emit signalTofeatFailed(msg);
}

void SignalSender::sendSignalPthreadSleep(int pthreadMask, char sleep)
{
    emit signalPthreadSleep(pthreadMask, sleep);
}

void SignalSender::sendSignalRunUIShow(bool show)
{
    emit signalRunUIShow(show);
}

void SignalSender::sendSignalSendAcc(const char *accno)
{
    emit signalSendAcc(accno);
}

void SignalSender::sendSignalOpenDoor(const int index, const bool open)
{
    emit signalOpenDoor(index, open);
}

void SignalSender::sendSignalSettingDoor(const int index)
{
    emit signalSettingDoor(index);
}

void SignalSender::sendSignalMessageHeadHide(const QString &msg, bool isVoece, char *voiceFile, int type)
{
    emit signalMessageHeadHide(msg, isVoece, voiceFile, type);
}

void SignalSender::sendSignalShowMessageHide(const QString &msg, bool isVoice, char *voiceFile, int timeOut)
{
    emit signalShowMessageHide(msg, isVoice, voiceFile, timeOut);
}

void SignalSender::sendSignalMessageUI(const QString &msg, char *voiceFile, int type)
{
    emit signalMessageUI(msg, voiceFile, type);
}

void SignalSender::sendSignalWelcomText(const QString &msg)
{
    emit signalWelcomText(msg);
}

void SignalSender::sendSignalReportEvent(int doorId, int enterType, int evNum, int inOrOut, int readerId)
{
    LOG_D("发送事件报告信息\n");
    emit signalReportEvent(doorId, enterType, evNum, inOrOut, readerId);
}

// 构造函数
SignalSender::SignalSender(QObject *parent) : QObject(parent)
{
#if (DEVICE_USE_TYPE==READER)
    _time_count = 1;
    connect(&_timer, SIGNAL(timeout()), this, SLOT(slotTimeout()));
    _timer.start(1000);
#endif
}

#if (DEVICE_USE_TYPE==READER)
void SignalSender::slotTimeout()
{
#if 0
    //485在线状态判断
    AssertDisConnect();
#endif
    _time_count++;

    if (_time_count>99)
        _time_count = 0;
}
#endif



