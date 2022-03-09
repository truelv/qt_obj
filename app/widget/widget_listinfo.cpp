#include "widget_listinfo.h"
#include "device/yt328_device.h"
#include "items/listitemwidget.h"
#include "global_config.h"
#define LOGTAG "widget_listinfo"

extern device_info deviceInfo;
static item_info model_deviceinfo[] = {
    INFO_STRING, "固件版本号", deviceInfo.base_info_data.framework_version,
    INFO_STRING, "软件版本号", deviceInfo.base_info_data.software_version,
    INFO_STRING, "终端序列号", deviceInfo.base_info_data.sn,
    INFO_CHAR, "代理号", deviceInfo.base_info_data.sn,
    INFO_SHORT, "客户号", deviceInfo.base_info_data.sn,
};
static item_info model_netparaminfo[] = {
    INFO_STRING, "IP地址", deviceInfo.network_info_data.eth_ip,
    INFO_STRING, "网关", deviceInfo.network_info_data.eth_gateway,
    INFO_STRING, "掩码", deviceInfo.network_info_data.eth_mask,
    INFO_STRING, "DNS", deviceInfo.network_info_data.dns1,
};
static item_info model_facefeatinfo[] = {
    INFO_STRING, "初始化状态", deviceInfo.network_info_data.eth_ip,
    INFO_STRING, "注册人脸数", deviceInfo.network_info_data.eth_gateway,
    INFO_STRING, "图片数量", deviceInfo.network_info_data.eth_mask,
    INFO_STRING, "权限数量", deviceInfo.network_info_data.dns1,
    INFO_STRING, "相识度", deviceInfo.network_info_data.dns1,
    INFO_STRING, "活体开关", deviceInfo.network_info_data.dns1,
    INFO_STRING, "人脸本机版本", deviceInfo.network_info_data.dns1,
    INFO_STRING, "人脸平台版本", deviceInfo.network_info_data.dns1,
    INFO_STRING, "权限本机版本", deviceInfo.network_info_data.dns1,
    INFO_STRING, "权限平台版本", deviceInfo.network_info_data.dns1,
    INFO_STRING, "人脸http地址", deviceInfo.network_info_data.dns1,
    INFO_STRING, "权限http地址", deviceInfo.network_info_data.dns1,
};

Widget_ListInfo::Widget_ListInfo(Widget_Base *parent, const QString& title, const listinfo_type w_type) :
    Widget_Base(parent, title)
{
    _listInfo.setParent(this);
    _listInfo.setObjectName("listInfo");
    _listInfo.setGeometry(0, TOP_PADING, 600, 1280-TOP_PADING);
    _listInfo.setStyleSheet("#listInfo{background-color:rgb(255,255,255,0);border-radius:10px;margin-left:60px;}#listInfo::item:selected{background-color:rgb(255,255,255,0);}");
    _listInfo.show();
    switch (w_type) {
    case WIDGET_DEVICE_INFO:
        _item_list = model_deviceinfo;
        _item_len = sizeof(model_deviceinfo)/sizeof(item_info);
        break;
    case WIDGET_NET_INFO:
        _item_list = model_netparaminfo;
        _item_len = sizeof(model_netparaminfo)/sizeof(item_info);
        break;
    case WIDGET_FACE_INFO:
        _item_list = model_facefeatinfo;
        _item_len = sizeof(model_facefeatinfo)/sizeof(item_info);
        break;
    default:
        break;
    }
#if 1
    for(int i=0;i<_item_len;i++) {
        QListWidgetItem* item = new QListWidgetItem(&_listInfo);
        item->setSizeHint(QSize(600, 100));
        LOG_D(LOGTAG, "item地址0x%x \n", item);
        LIstItemWidget* w = new LIstItemWidget;
        _listInfo.setItemWidget(item, w);
        w->setKV(tr(_item_list[i].name), (char*)_item_list[i].p);
        LOG_D(LOGTAG, "w地址0x%x \n", w);
        if (i%2) {
            w->setBackColor("#frame{background-color:rgb(0,123,231,20);}");
        } else {
            w->setBackColor("#frame{background-color:rgb(71,166,255,20);}");
        }
    }
#endif
}

Widget_ListInfo::~Widget_ListInfo()
{
#if 1
    QListWidgetItem* item = NULL;
    QWidget* w = NULL;
    // 遍历list widget item，删除调
    int count = _listInfo.count();
    for (int i=0;i<count;i++) {
        item = _listInfo.item(0);
        w = _listInfo.itemWidget(item);
        _listInfo.removeItemWidget(item);
        delete w;
        delete item;
    }
#endif
}
