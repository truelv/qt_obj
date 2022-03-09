#ifndef WIDGET_LISTBUTTON_H
#define WIDGET_LISTBUTTON_H

#include <QWidget>
#include <QMetaType>
#include "items/backtitle.h"
#include "widget_base.h"
typedef enum {
    BUTTON_NONE,
    BUTTON_DEVICE_SETTING,
    BUTTON_QUERY_INFO,
    BUTTON_DEVICE_INFO,
    BUTTON_NETPARAM_INFO,
    BUTTON_FACEFEAT_INFO,
} button_type;
typedef struct {
    button_type type;
    char name[32];
} item_button;
Q_DECLARE_METATYPE(item_button)
typedef enum {
    WIDGET_SETTING,
    WIDGET_DEVICE_SETTING,
    WIDGET_ADVANCED_SETTING,
    WIDGET_QUERY_INFO,
} listbutton_type;

namespace Ui {
class Widget_ListButton;
}

class Widget_ListButton : public Widget_Base
{
    Q_OBJECT

public:
    explicit Widget_ListButton(Widget_Base *parent = 0, const QString& title="", const listbutton_type w_type=WIDGET_SETTING);
    ~Widget_ListButton();

protected slots:
    void slotButtonClicked();

private:
    item_button* _itemList;
    int _item_len;
    QVector<QWidget*> _btList;
};

#endif // WIDGET_LISTBUTTON_H
