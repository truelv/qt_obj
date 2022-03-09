/**
 * 1、显示日期时间，1s更新一次
 * 2、框选检测到的人脸
 * 3、显示识别到的人脸名字
 * 4、显示网络状态
 * 5、长按3秒进入主设置界面
*/
#ifndef WIDGET_DETECTFACE_H
#define WIDGET_DETECTFACE_H

#include <QWidget>
#include <QTimer>
#include <QMouseEvent>
#include "global.h"
#include "signalsender.h"

namespace Ui {
class widgetRun;
}

class widgetRun : public QWidget
{
    Q_OBJECT

public:
    explicit widgetRun(QWidget *parent = 0);
    ~widgetRun();

protected:
    void paintEvent(QPaintEvent* e);
    void mousePressEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);

    void updateNetIcon();

protected slots:
    void slotUpdateTime();
    void slotDrawFaceArea();
    void slotNetIconSet();
    void slotPressScreen();

    void slotEthOn();
    void slotEthOff();
    void slotWifiOn();
    void slotWifiOff();
    void slotBeatSuccess();
    void slotBeatFailed();

    void slotShowCamera();
    void slotHideCamera();
#if (DEVICE_USE_TYPE==READER)
    void slotRs485Online(int sta);
#endif
    // 界面开关（显示隐藏）
    void slotWinShow(bool show) {show?this->show():this->hide();}
    // 显示消息(必须有语音)
    void SlotShowMsg(const QString& msg, char* voiceFile, int type);
    // 修改欢迎词
    void SlotWelcomtext(const QString& text);

private:
    Ui::widgetRun *ui;
    QTimer _timer;
    QTimer _timer_show;
    QRegion _last_region;
    SignalSender* _sender;

    QString _welcomText;

    char _net_status;

    // 测试
    bool _qrTimerIsRun;
};

#endif // WIDGET_DETECTFACE_H
