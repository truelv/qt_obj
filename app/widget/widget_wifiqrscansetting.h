#ifndef WIDGET_WIFIQRSCANSETTING_H
#define WIDGET_WIFIQRSCANSETTING_H

#include <QWidget>
#include <QVBoxLayout>
#include <QTimer>

#include "widget_base.h"
#include "signalsender.h"
#include "widgetmessage.h"

namespace Ui {
class Widget_WifiQrscanSetting;
}

class Widget_WifiQrscanSetting : public Widget_Base
{
    Q_OBJECT

public:
    explicit Widget_WifiQrscanSetting(Widget_Base *parent = 0, const QString& title="");
    ~Widget_WifiQrscanSetting();

protected slots:
    void slotWifiConnected();
    void slotWifiOpen();
    void slotShowWifiOpening();

signals:
    void signalShowWifiOpening();

private:
    QVBoxLayout* _layout;
    QWidget _w;

    SignalSender* _sigSender;
    Ui::Widget_WifiQrscanSetting *ui;

    bool isConnected;
    QTimer _timer;
};

#endif // WIDGET_WIFIQRSCANSETTING_H
