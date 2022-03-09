#ifndef WIDGET_WIFISETTING_H
#define WIDGET_WIFISETTING_H

#include <QWidget>
#include <QVBoxLayout>
#include <QListWidget>
#include "widget_base.h"
#include "signalsender.h"
#include "widgetmessage.h"

// 空闲，正在打开，正在扫描，正在连接

namespace Ui {
class Widget_WIfiSetting;
}

class Widget_WIfiSetting : public Widget_Base
{
    Q_OBJECT
public:
    explicit Widget_WIfiSetting(Widget_Base *parent = 0, const QString& title="");
    ~Widget_WIfiSetting();
    void autoToBack();

signals:
    void signalShowOpen();

protected slots:
    void slotWifiSwitch();
    void slotWifiScanFailed();
    void slotListWIFI();
    void slotClearListWIFI();
    void slotWifiSlecet(QModelIndex index);
    void slotWifiConnecting();
    void slotWifiConnected();
    void slotShowOpen();

private:
    QVBoxLayout* _layout;
    Ui::Widget_WIfiSetting* ui;
    QWidget _w;

    SignalSender* _sigSender;
    bool _wifiIsOn;             // wifi是否开
    int _connected_index;
    int _connect_index;

    WidgetMessage* _dialogPass;

};

#endif // WIDGET_WIFISETTING_H
