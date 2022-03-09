#include "widgetlistparam.h"
#include "items/listitemwidget.h"
#include "items/listitemwidget2.h"

WidgetListParam::WidgetListParam(Widget_Base *parent, item_info *items, const QString &title) :
    Widget_Base(parent, title),
    _item_list(items),
    _item_len(0)
{
    if (NULL==items)
        return ;

    _listInfo.setParent(this);
    _listInfo.setObjectName("listInfo");
    _listInfo.setGeometry(60, TOP_PADING, 600, 1200-TOP_PADING);
    _listInfo.setStyleSheet("#listInfo{background-color:rgb(255,255,255,0);border-radius:10px;}"
                            "#listInfo::item:selected{background-color:rgb(255,255,255,0);}");
    _listInfo.show();

    for(int i=0;INFO_NULL!=_item_list[i].type;i++,_item_len++)
    {
        QListWidgetItem* item = new QListWidgetItem(&_listInfo);
        item->setSizeHint(QSize(LIST_ITEM_WIDTH, LIST_ITEM_HEIGHT2));
        QWidget* w = NULL;
        // 显示http地址的用类型2的item，其他用类型1
        switch (_item_list[i].type)
        {
        case INFO_HTTP_ADDR:
            item->setSizeHint(QSize(LIST_ITEM_WIDTH, 2*LIST_ITEM_HEIGHT));
            w = new LIstItemWidget2;
            break;
        default:
            item->setSizeHint(QSize(LIST_ITEM_WIDTH, LIST_ITEM_HEIGHT));
            w = new LIstItemWidget;
            ((LIstItemWidget*)w)->setSize(QSize(LIST_ITEM_WIDTH, LIST_ITEM_HEIGHT));
            break;
        }
        _listInfo.setItemWidget(item, w);

        switch (_item_list[i].type)
        {
        case INFO_AGENT_GUEST:
            ((LIstItemWidget*)w)->setKV(tr(_item_list[i].name), QString("%1-%2")
                     .arg(g_qrinfo.agentID)
                     .arg(g_qrinfo.guestID));
            break;
        case INFO_STRING:
            ((LIstItemWidget*)w)->setKV(tr(_item_list[i].name),
                                        (char*)_item_list[i].p);
            break;

        case INFO_INT:
            ((LIstItemWidget*)w)->setKV(tr(_item_list[i].name),
                                        QString("%1").arg(*(int*)(_item_list[i].p)));
            break;

        case INFO_LONG:
            ((LIstItemWidget*)w)->setKV(tr(_item_list[i].name),
                                        QString("%1").arg(*(long*)(_item_list[i].p)));
            break;

        case INFO_CHAR:
            ((LIstItemWidget*)w)->setKV(tr(_item_list[i].name),
                                        QString("%1").arg(*(char*)(_item_list[i].p)));
            break;

        case INFO_FLOAT:
            ((LIstItemWidget*)w)->setKV(tr(_item_list[i].name),
                                        QString("%1").arg(*(float*)(_item_list[i].p)));
            break;

        case INFO_HTTP_ADDR:
            ((LIstItemWidget2*)w)->setKV(tr(_item_list[i].name),
                                         (char*)_item_list[i].p);
            break;
        case INFO_FACE_INIT:
            ((LIstItemWidget*)w)->setKV(tr(_item_list[i].name),
                                        tr(*(char*)_item_list[i].p==0?"成功":"失败"));
            break;

        case INFO_LIVING_DET:
            ((LIstItemWidget*)w)->setKV(tr(_item_list[i].name),
                                        tr(*(unsigned char*)_item_list[i].p==0?"关闭":"打开"));
            break;

        case INFO_FACE_COUNT:
            ((LIstItemWidget*)w)->setKV(tr(_item_list[i].name),
                                        QString("%1/5000").arg(*(int*)(_item_list[i].p)));
            break;
        case INFO_IP:
        {
            char* ch_p = (char*)_item_list[i].p;
            char tmp_str[16] = {0};
            snprintf(tmp_str, 16, "%d.%d.%d.%d", ch_p[0], ch_p[1], ch_p[2], ch_p[3]);
            ((LIstItemWidget*)w)->setKV(tr(_item_list[i].name), tmp_str);
            break;
        }
        default:
            break;
        }

        if (i%2)
        {
            ((LIstItemWidget*)w)->setBackColor("#frame{background-color:rgb(71,166,255,70);}");
        }
        else
        {
            ((LIstItemWidget*)w)->setBackColor("#frame{background-color:rgb(0,123,231,70);}");
        }
    }
}

WidgetListParam::~WidgetListParam()
{
    // 清除listview的所有子控件
    QListWidgetItem* item = NULL;
    QWidget* w = NULL;
    // 遍历list widget item，删除调
    int count = _listInfo.count();
    for (int i=0;i<count;i++)
    {
        item = _listInfo.item(0);
        w = _listInfo.itemWidget(item);
        _listInfo.removeItemWidget(item);
        delete w;
        delete item;
    }
}
