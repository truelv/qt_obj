/**
 * 列出菜单按键控件
*/
#ifndef WIDGETLISTMENU_H
#define WIDGETLISTMENU_H

#include <QWidget>
#include "widget_base.h"
#include "widgetConfig.h"
#include "dialog/dialog_base.h"
#include "widgetmessage.h"

#define BUTTONS_HIGHT_SPACE 120

class WidgetListmenu : public Widget_Base
{
    Q_OBJECT
public:
    explicit WidgetListmenu(Widget_Base *parent=0, item_button* items=NULL, const QString &title="");
    ~WidgetListmenu();
    void autoToBack();

protected:
    void switchTimrebootButton(QObject *bt, int index);
    void slotDeviceReboot();
    void slotDeviceInit();
    void slotClearAll();

protected slots:
    void slotButtonClicked();   // 响应按键，每种类型的按键都要实现响应

private:
    item_button* _itemList;     // 指向model数据
    int _item_len;              // 记录model数据大小
    QVector<QWidget*> _btList;  // 保存实例化的控件（按键），析构函数要清理这些控件
    Dialog_Base* _baseDialog;   // 处理本界面有些菜单按键触发的设置弹框
    WidgetMessage* _msgDialog;  // 处理本界面触发的消息框（考虑把这块消息处理直接移到消息框处理）
};

#endif // WIDGETLISTMENU_H
