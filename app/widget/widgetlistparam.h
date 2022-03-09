#ifndef WIDGETLISTPARAM_H
#define WIDGETLISTPARAM_H

#include <QWidget>
#include <QListWidget>
#include "widget_common_typedef.h"
#include "widgetConfig.h"

class WidgetListParam : public Widget_Base
{
    Q_OBJECT
public:
    explicit WidgetListParam(Widget_Base *parent=0, item_info* items=NULL, const QString& title="");
    ~WidgetListParam();

private:
    // 显示信息的列表控件
    QListWidget _listInfo;
    // 显示的信息数据的model
    item_info* _item_list;
    int _item_len;
};

#endif // WIDGETLISTPARAM_H
