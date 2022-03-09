#include "widget_listbutton.h"
#include "items/buttontype2.h"
#include "managerbkview.h"
#include "mainmenu.h"
#include "global_config.h"
#include "widget_listinfo.h"

#define LOGTAG "widget_listbutton"
// 按键列表间距
#define HIGHT_SPACE 120
// 查询信息界面的所有按键
static item_button model_queryInfo[] = {
    BUTTON_DEVICE_INFO, "设备信息",
    BUTTON_NETPARAM_INFO, "网络信息",
    BUTTON_FACEFEAT_INFO, "人脸信息",
};
// 本机设置界面的所有按键
static item_button model_deviceSetting[] = {
    BUTTON_NONE, "wif设置",
    BUTTON_NONE, "网路配置",
    BUTTON_NONE, "时钟配置",
    BUTTON_NONE, "音量调节",
};
// 高级参数设置界面的所有按键
static item_button model_advancedSetting[] = {
    BUTTON_NONE, "恢复出厂设置",
    BUTTON_NONE, "初始化设备",
    BUTTON_NONE, "重启设备",
    BUTTON_NONE, "切换到工厂程序",
    BUTTON_NONE, "服务控制",
};
// 设置界面的所有按键
static item_button model_setting[] = {
    BUTTON_DEVICE_SETTING, "本机配置",
    BUTTON_NONE, "模式配置",
    BUTTON_NONE, "人脸检测设置",
    BUTTON_NONE, "高级参数",
};

Widget_ListButton::Widget_ListButton(Widget_Base *parent,
                                     const QString &title,
                                     const listbutton_type w_type) :
    Widget_Base(parent, title)
{
    _btList.clear();
    switch (w_type) {
    case WIDGET_SETTING:
        _itemList = model_setting;
        _item_len = sizeof(model_setting)/sizeof(item_button);
        break;
    case WIDGET_DEVICE_SETTING:
        _itemList = model_deviceSetting;
        _item_len = sizeof(model_deviceSetting)/sizeof(item_button);
        break;
    case WIDGET_QUERY_INFO:
        _itemList = model_queryInfo;
        _item_len = sizeof(model_queryInfo)/sizeof(item_button);
        break;
    case WIDGET_ADVANCED_SETTING:
        _itemList = model_advancedSetting;
        _item_len = sizeof(model_advancedSetting)/sizeof(item_button);
        break;
    default:
        break;
    }

    int pos_y = TOP_PADING;
    for (int i=0;i<_item_len;i++) {
        ButtonType2* bt = new ButtonType2;
        bt->setParent(this);
        bt->move(50, pos_y+i*HIGHT_SPACE);
        bt->setText(QString(tr("%1 %2")).arg(i+1).arg(tr(_itemList[i].name)));
        bt->show();
        bt->setProperty("type", _itemList[i].type);
        connect(bt, SIGNAL(clicked()), this, SLOT(slotButtonClicked()));
        _btList.append(bt);
    }
}

Widget_ListButton::~Widget_ListButton()
{
    foreach (QWidget* var, _btList) {
        delete var;
    }
}

void Widget_ListButton::slotButtonClicked()
{
    Widget_Base* w = NULL;
    QObject* sender = QObject::sender();
    int bt_type = sender->property("type").toInt();
    LOG_D(LOGTAG, "发送信号控件类型属性 %d\n", bt_type);
    switch (bt_type) {
    case BUTTON_DEVICE_SETTING:
        w = new Widget_ListButton(0, tr("本机设置"), WIDGET_DEVICE_SETTING);
        break;
    case BUTTON_QUERY_INFO:
        w = new Widget_ListButton(0, tr("信息查询"), WIDGET_QUERY_INFO);
        break;
    case BUTTON_DEVICE_INFO:
        w = new Widget_ListInfo(0, tr("设备信息"), WIDGET_DEVICE_INFO);
        break;
    case BUTTON_NETPARAM_INFO:
        w = new Widget_ListInfo(0, tr("网络参数信息"), WIDGET_NET_INFO);
        break;
    case BUTTON_FACEFEAT_INFO:
        w = new Widget_ListInfo(0, tr("人脸参数信息"), WIDGET_FACE_INFO);
        break;
    default:
        return;
        break;
    }
    ManagerBkView* _managerBkView = ManagerBkView::getInstance();
    w->setBackPage(this);
    _managerBkView->addWidgetShow(w);
    _managerBkView->show();
    this->hide();
}
