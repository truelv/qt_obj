#ifndef WIDGET_LISTINFO_H
#define WIDGET_LISTINFO_H

#include <QWidget>
#include <QMetaType>
#include <QVariant>
#include <QListWidget>
#include "widget_base.h"

typedef enum {
    INFO_CHAR,
    INFO_INT,
    INFO_SHORT,
    INFO_FLOAT,
    INFO_STRING,
} info_type;
typedef struct {
    info_type type;
    char name[32];
    void* p;
} item_info;
Q_DECLARE_METATYPE(item_info)

typedef enum {
    WIDGET_DEVICE_INFO,
    WIDGET_NET_INFO,
    WIDGET_FACE_INFO,
} listinfo_type;

namespace Ui {
class Widget_ListInfo;
}

class Widget_ListInfo : public Widget_Base
{
    Q_OBJECT

public:
    explicit Widget_ListInfo(Widget_Base *parent = 0, const QString& title="", const listinfo_type w_type=WIDGET_DEVICE_INFO);
    ~Widget_ListInfo();

private:
    QListWidget _listInfo;
    item_info* _item_list;
    int _item_len;
};

#endif // WIDGET_LISTINFO_H
