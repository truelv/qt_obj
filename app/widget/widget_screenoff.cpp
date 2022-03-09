#include "widget_screenoff.h"
#include "global.h"
#include "task/face/taskface.h"
#include "file_ops.h"
#include "base/api/led.h"


#define LIGHT_THRESHOLD 300
#define BLANKFILE       "/sys/class/graphics/fb0/blank"
#define LOGTAG          "widget_screenoff"

Widget_ScreenOff::Widget_ScreenOff(QWidget *parent) :
    QWidget(parent),
    _outTimeMs(BLANK_TIMEOUT_MS_RUN),
    _status(SCREEN_ON)
{
#if 1
    setWindowFlags(Qt::FramelessWindowHint);
    _showText.setParent(this);
    _showText.setText(tr("轻触屏幕唤醒设备"));
    _showText.setGeometry(0, 500, 720, 200);
    setStyleSheet("background-color:rgb(0,0,0);font-size:90px;color:rgb(255,255,255)");

    _showLight.setParent(this);
    _showLight.setGeometry(0, 700, 720, 100);
#endif

    _sender = SignalSender::getInstance();
    connect(_sender, SIGNAL(signalScreenOff()), this, SLOT(slotScreenOff()));
    connect(_sender, SIGNAL(signalScreenOn()), this, SLOT(slotScreenOn()));
    connect(_sender, SIGNAL(signalScreenOnTimeout()), this, SLOT(slotScreenOnTimeout()));
    connect(_sender, SIGNAL(signalChangeOutTime(int)), this, SLOT(slotChangeOutTime(int)));
    // 进入熄屏倒计时
    connect(&_timer, SIGNAL(timeout()), this, SLOT(slotTimeOut()));
    // 实例化后开始倒计时,状态改为倒计时
    _timer.start(_outTimeMs);
    _status = SCREEN_COUNTING;

    connect(&_timerDebug, SIGNAL(timeout()), this, SLOT(slotUpdateLight()));
    _timerDebug.start(1000);
}

// 启动倒计时熄屏
void Widget_ScreenOff::slotScreenOff()
{
    // 是亮屏，开启定时器
    switch (_status)
    {
    case SCREEN_ON:
        LOG_I("现在是亮屏，希望熄屏，开始倒计时");
        _timer.start(_outTimeMs);
        _status = SCREEN_COUNTING;
        break;
    default:
        break;
    }

}

void Widget_ScreenOff::slotScreenOn()
{
    // 是熄屏，直接亮屏，是倒计时（亮屏），关掉定时器
    switch (_status)
    {
    case SCREEN_OFF:
        LOG_D("现在是熄屏，希望亮屏，亮屏");
        file_write(BLANKFILE, "0", 2);
        _status = SCREEN_ON;
        break;
    case SCREEN_SAVE:
    {
        char val[8] = {0};
        hide();
        snprintf(val, 8, "%d", g_BaseInfo.backlightValue);
        file_write(INTERFACE_BACKLIGHT, val, strlen(val)+1);
        //_sender->sendSignalRunUIShow(true);
        _status = SCREEN_ON;
        break;
    }
    case SCREEN_COUNTING:
        LOG_D("正在倒计时，希望亮屏，停止倒计时");
        _timer.stop();
        _status = SCREEN_ON;
        break;
    default:
        break;
    }
}

// 刷卡和扫码使用的亮屏策略，优先级比人脸要低
void Widget_ScreenOff::slotScreenOnTimeout()
{
    // 如果是亮屏，忽略;是倒计时，重新倒计时;是熄屏，先亮屏再熄屏
    switch (_status) {
    case SCREEN_ON:
        break;
    case SCREEN_OFF:
    case SCREEN_SAVE:
        LOG_D("刷卡或扫码，熄屏，希望亮屏，先执行亮屏，再执行熄屏");
        // 执行亮屏
        slotScreenOn();
        // 开始熄屏倒计时
        slotScreenOff();
        break;
    case SCREEN_COUNTING:
        //LOG_D("刷卡或扫码，正在倒计时，希望亮屏，重新计时");
        _timer.stop();
        _timer.start(_outTimeMs);
        break;
    default:
        break;
    }
}

void Widget_ScreenOff::slotTimeOut()
{
    _timer.stop();
    // 关闭人脸
    TaskFace::GetInstance()->EnterMenu();
    // 关闭扫码
    // 关闭读卡

    // 复位窗口
    _sender->sendSignalResetToRunWin();
    file_write(WHITE_LED, "0", 2);
    infrared_led_ctrl(LED_OFF);
    // 计时到熄屏
    LOG_I("倒计时到了，熄屏");
    if (g_BaseInfo.rgbLight>LIGHT_THRESHOLD)
    {
        file_write(BLANKFILE, "1", 2);
        _status = SCREEN_OFF;
    }
    else
    {
        // 显示屏保窗口
        showMaximized();
        raise();
        file_write(INTERFACE_BACKLIGHT, "1", 2);
        //_sender->sendSignalRunUIShow(false);
        _status = SCREEN_SAVE;
    }
}

void Widget_ScreenOff::slotChangeOutTime(int ms)
{
    _outTimeMs = ms;
}

void Widget_ScreenOff::slotUpdateLight()
{
    _showLight.setText(QString("%1").arg(g_BaseInfo.rgbLight));
}

bool Widget_ScreenOff::eventFilter(QObject *obj, QEvent *e)
{
    Q_UNUSED(obj)

    if (e->type() == QEvent::MouseButtonRelease)
    {
        _sender->sendSignalScreenOnTimeout();
        LOG_D("有点机屏幕，rgb亮度%d\n", g_BaseInfo.rgbLight);
        if (g_BaseInfo.rgbLight<LIGHT_THRESHOLD)
           file_write(WHITE_LED, "1", 2);
    }

    return QObject::eventFilter(obj, e);
}

