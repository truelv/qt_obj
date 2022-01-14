#include "guideconf.h"
#include <QDebug>

static ONE_FRAME frames[] = {
    {GUIDE_ETH,         0, 2, -1, true, "以太网设置", 0},
    //{GUIDE_WIFI,        1, -1, 2, true,  "WIFI配置", 0},
    {GUIDE_CONTRLMODE,  2, 3, 0, false,  "控制器模式", 0},
    {GUIDE_AUTHMODE,  3, 3, 0, false,  "权限模式", 0},
    {GUIDE_SERVERIP,    4, -1, 2, false,  "服务器IP配置", 0},
    {GUIDE_SERVERURL,    5, -1, 2, false,  "服务器URL配置", 0},
    {GUIDE_DOORNUM,    6, -1, 2, false,  "门号控制器号配置", 0}
};

GuideConf::GuideConf()
{
    int count = sizeof(frames)/sizeof(ONE_FRAME);
    SetButtonStyle("font-size:50px;color:red");
    SetTileStyle("font-size:60px;color:white");
    SetFrameStyle("#frame{border-image:url(/data/zytk_reader/img/background_pic.jpg)}");
    // 创建n个窗口
    for (int i=0;i<count;i++)
    {
        AddWidget(&frames[i]);
        // 设置样式
    }

    ShowIndex(0);
    //RemoveWidget(2);
}

void GuideConf::ReturnPageInput(int index)
{
    qDebug() << "切换页面 "<< index;
    // 第index个控件保存结果
    // 这里要用dynamic_cast强制转换，不然调不到接口的方法
    IfaceChildOpt* w = dynamic_cast<IfaceChildOpt*>(frames[index].w);
    if (NULL==w)
    {
        qDebug() << "子控件为NULL";
        return ;
    }
    QVariantList list;
    w->GetInput(list);
    //qDebug() << "子控件地址xxx " << w;
    if (list.length()<=0)
    {
        qDebug() << "未获取到数据";
        return ;
    }
//    GUIDE_SERVERIP,
//    GUIDE_SERVERURL,
//    GUIDE_DOORNUM,
    switch (frames[index].type) {
    case GUIDE_ETH:
        qDebug() << list[0].toString() << list[1].toString();
        break;
    case GUIDE_CONTRLMODE:
        qDebug() << list[0].toInt();
        break;
    case GUIDE_AUTHMODE:
        qDebug() << list[0].toInt();
        break;
    case GUIDE_SERVERIP:
        qDebug() << list[0].toString() << list[1].toString();
        break;
    case GUIDE_SERVERURL:
        qDebug() << list[0].toString();
        break;
    case GUIDE_DOORNUM:
        qDebug() << list[0].toString() << list[1].toString();
        break;
    default:
        break;
    }
}



