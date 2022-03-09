/**
 * 信号发送类，
 * 自定义信号和发送信号接口，
 */
#ifndef SIGNALSENDER_H
#define SIGNALSENDER_H

#include "global.h"
#include <QObject>
#include <QTimer>

#define PTHREAD_SLEEP   1
#define PTHREAD_WAKEUP  0

#define MASK_SLEEP_PTHREAD_QRSCAN       0x01
#define MASK_SLEEP_PTHREAD_READCARD     0x02

class SignalSender : public QObject
{
    Q_OBJECT
public:
    static SignalSender* getInstance();
    ~SignalSender();
    // 485信号
    void sendSignalRs485Online(int sta);
    // 人脸检测结果信号
    void sendSignalForDraw();
    // wifi状态变化信号
    void sendSignalWifiScanFailed();
    void sendSignalUpdateListWifi();
    void sendSignalClearListWifi();
    void sendSignalWifiOpen();
    void sendSignalWifiConnecting();
    void sendSignalWifiConnected();
    void sendSignalWifiDisConnected();
    // 以太网状态变化信号
    void sendSignalEthOnline();
    void sendSignalEthOffline();
    // 服务连接成功/失败
    void sendSignalBeatSuccess();
    void sendSignalBeatFailed();
    // 通知亮屏/熄屏
    void sendSignalScreenOff();
    void sendSignalScreenOn();
    void sendSignalScreenOnTimeout();
    void sendSignalWakeFaceDetect();
    // 复位到主窗口
    void sendSignalResetToRunWin();
    // 修改息屏倒计时时间
    void sendSignalChangeOutTime(int ms);
    // 系统重启
    void sendSignalReboot();
    //
    void sendSignalSwithcTimer(bool on);
    //
    void sendSignalFaceUnregistered();
    // 更新转特征码失败信息
    void sendSignalTofeatFailed(const QString& msg);
    // 线程休眠
    void sendSignalPthreadSleep(int pthreadMask, char sleep);
    // 运行界面开关
    void sendSignalRunUIShow(bool show);

    void sendSignalSendAcc(const char* accno);

    void sendSignalOpenDoor(const int index, const bool open);

    void sendSignalSettingDoor(const int index);
    // 提示框消息
    void sendSignalMessageHeadHide(const QString &msg, bool isVoece, char *voiceFile, int type);
    void sendSignalShowMessageHide(const QString &msg, bool isVoice, char *voiceFile, int timeOut);
    // 运行界面弹框消息
    void sendSignalMessageUI(const QString& msg, char* voiceFile, int type);
    // 修改欢迎词
    void sendSignalWelcomText(const QString& msg);
    // 事件处理消息
    void sendSignalReportEvent(int doorId, int enterType, int evNum, int inOrOut, int readerId);


signals:
    // 485信号
    void signalRs485Online(int sta);
    // 人脸检测结果信号
    void signalForDraw();
    // wifi状态变化信号
    void signalWifiScanFailed();
    void signalUpdateListWifi();
    void signalClearListWifi();
    void signalWifiOpen();
    void signalWifiConnecting();
    void signalWifiConnected();
    void signalWifiDisConnected();
    // 以太网状态变化信号
    void signalEthOnline();
    void signalEthOffline();
    // 服务连接成功/失败
    void signalBeatSuccess();
    void signalBeatFailed();
    // 通知亮屏/熄屏
    void signalScreenOff();
    void signalScreenOn();
    void signalScreenOnTimeout();
    void signalWakeFaceDetect();
    // 复位窗口
    void signalResetToRunWin();
    // 修改息屏倒计时时间
    void signalChangeOutTime(int ms);
    // 系统重启
    void signalReboot();
    // 测试，开关扫码定时器
    void signalSwitchTimer(bool on);
    // 信号，人脸信息未注册
    void signalFaceUnregistered();
    //
    void signalTofeatFailed(const QString& msg);
    // 线程休眠
    void signalPthreadSleep(int pthreadMask, char sleep);
    // 运行界面开关
    void signalRunUIShow(bool show);
    // 发送帐号，卡码脸获取帐号
    void signalSendAcc(const char* accno);
    // 发送消息，指定门开门操作
    void signalOpenDoor(const int index, const bool open);
    // 通知设置门参数
    void signalSettingDoor(const int index);

    // 通知消息框消息
    void signalMessageHeadHide(const QString &msg, bool isVoece, char *voiceFile, int type);
    void signalShowMessageHide(const QString &msg, bool isVoice, char *voiceFile, int timeOut);
    // 通知消息框消息 end

    // 通知运行UI消息
    // 弹框提示（文字）
    void signalMessageUI(const QString& msg, char* voiceFile, int type);
    // 修改欢迎词
    void signalWelcomText(const QString& msg);
    // 通知运行UI消息 end

    // 事件模块消息
    void signalReportEvent(int doorId, int enterType, int evNum, int inOrOut, int readerId);
    // 事件模块消息 end
public slots:
#if (DEVICE_USE_TYPE==READER)
    // 全局定时器超时处理
    void slotTimeout();
#endif

private:
    explicit SignalSender(QObject *parent = 0);
    static SignalSender* _sender;

#if (DEVICE_USE_TYPE==READER)
    QTimer _timer;
    int _time_count;
#endif

};

#endif // SIGNALSENDER_H
