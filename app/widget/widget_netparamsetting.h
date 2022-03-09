#ifndef WIDGET_NETPARAMSETTING_H
#define WIDGET_NETPARAMSETTING_H

#include "widget_base.h"
#include <QVBoxLayout>
namespace Ui {
class Widget_NetParamSetting;
}

class Widget_NetParamSetting : public Widget_Base
{
    Q_OBJECT
public:
    explicit Widget_NetParamSetting(Widget_Base *parent = 0, const QString& title="");
    ~Widget_NetParamSetting();
    void autoToBack();

protected:
    void ipEditDisable();
    void ipEditEnable();
    void dhcpEditDisable();
    void dhcpEditEnable();

    bool eventFilter(QObject* obj, QEvent* e);

private slots:
    void on_confirm_bt_clicked();
    void on_eth_is_dhcp_stateChanged(int arg1);

private:
    QVBoxLayout* _layout;
    Ui::Widget_NetParamSetting* ui;
    QWidget _w;

    bool _ethIsDhcp;

};

#endif // WIDGET_NETPARAMSETTING_H
