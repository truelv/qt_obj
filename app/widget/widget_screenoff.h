#ifndef WIDGET_SCREENOFF_H
#define WIDGET_SCREENOFF_H

#include <QWidget>
#include <QTimer>
#include <QEvent>
#include <QLabel>

#include "signalsender.h"

typedef enum {
    SCREEN_OFF = 0,
    SCREEN_SAVE,
    SCREEN_ON,
    SCREEN_COUNTING,
} screen_status;

class Widget_ScreenOff : public QWidget
{
    Q_OBJECT
public:
    explicit Widget_ScreenOff(QWidget *parent = 0);

signals:

protected slots:
    void slotScreenOff();
    void slotScreenOn();
    void slotScreenOnTimeout();
    void slotTimeOut();
    void slotChangeOutTime(int ms);
    void slotUpdateLight();

protected:
    bool eventFilter(QObject *obj, QEvent *e);

private:
    QTimer _timer;
    int _outTimeMs;
    SignalSender* _sender;
    screen_status _status;

    QLabel _showText;
    QLabel _showLight;

    QTimer _timerDebug;
};

#endif // WIDGET_SCREENOFF_H
