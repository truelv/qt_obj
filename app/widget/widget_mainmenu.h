/**
 * 1、查询按键进入查询界面
 * 2、设置按键进入设置界面，需要密码验证
 * 3、返回按键，返回人脸检测界面
*/
#ifndef WIDGET_MAINMENU_H
#define WIDGET_MAINMENU_H

#include <QWidget>
#include <QMetaType>
#include "widget_base.h"
#include "widget/widgetConfig.h"
#include "widgetmessage.h"

namespace Ui {
class Widget_Mainmenu;
}

class Widget_Mainmenu : public Widget_Base
{
    Q_OBJECT

public:
    explicit Widget_Mainmenu(Widget_Base *parent = 0, const QString& title="");
    ~Widget_Mainmenu();
    void autoToBack();

protected:
    bool checkPass(const QString &pass);

protected slots:
    void slotPageBack();
    void slotButtonClicked();

private:
    item_box* _itemList;
    int _item_len;
    QVector<QWidget*> _btList;

    WidgetMessage* _passDialog;

};

#endif // WIDGET_MAINMENU_H
