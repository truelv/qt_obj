#include "widget_mainmenu.h"
#include "items/buttontype1.h"
#include "global.h"
#include "managerbkview.h"
#include "task/face/taskface.h"
#include "widgetlistmenu.h"
#include "widget/widgetmessage.h"
#include <QVariant>

#define HIGHT_SPACE 362
#define WIDTH_SPACE 316
#define TOP_PADING_MAINMENU 300

Widget_Mainmenu::Widget_Mainmenu(Widget_Base *parent, const QString &title) :
    Widget_Base(parent, title),
    _passDialog(NULL)
{
    _itemList = model_mainmenu;
    _item_len = 0;

    int pos_y = TOP_PADING_MAINMENU;
    for (int i=0;BOX_NULL!=_itemList[i].type;i++,_item_len++)
    {
        ButtonType1* bt = new ButtonType1;
        bt->setParent(this);
        bt->move(55+(i%2)*WIDTH_SPACE, pos_y+(i/2)*HIGHT_SPACE);
        bt->setText(QString(tr("%1")).arg(tr(_itemList[i].name)));
        bt->setIcon(QString("image:url(%1/%2);").arg(UI_IMG_DIR).arg(_itemList[i].iconURl));
        bt->show();
        bt->setProperty("type", _itemList[i].type);
        connect(bt, SIGNAL(clicked()), this, SLOT(slotButtonClicked()));
        _btList.append(bt);

    }
}

Widget_Mainmenu::~Widget_Mainmenu()
{
    foreach (QWidget* var, _btList) {
        delete var;
    }
}

void Widget_Mainmenu::autoToBack()
{
    if (0!=_passDialog)
    {
        _passDialog->hideKeyBoard();
        _passDialog->reject();
        delete _passDialog;
        _passDialog = NULL;
    }

    if (NULL!=_backPage)
    {
        // 进入运行界面，重新设置为15ms
        SignalSender* send = SignalSender::getInstance();
        send->sendSignalChangeOutTime(BLANK_TIMEOUT_MS_RUN);
        send->sendSignalPthreadSleep(MASK_SLEEP_PTHREAD_QRSCAN|MASK_SLEEP_PTHREAD_READCARD, PTHREAD_WAKEUP);
        // 上一页不为空
        _backPage->show();
        ManagerBkView* _managerBkView = ManagerBkView::getInstance();
        _managerBkView->deleteLater();
        this->deleteLater();
    }
}

// 重写返回按键按下处理方法
void Widget_Mainmenu::slotPageBack()
{
    if (NULL!=_backPage)
    {
        // 进入运行界面，重新设置为15ms
        SignalSender* send = SignalSender::getInstance();
        send->sendSignalChangeOutTime(BLANK_TIMEOUT_MS_RUN);
        g_BaseInfo.deviceStatusSwitch &= (~DEVICESTATUS_MASK_MENUSETTING);
        // 开启预览和检测
        TaskFace::GetInstance()->LeaveMenu();
        //  上一页是运行页，显示
        LOG_I("进入运行窗口");
        _backPage->show();
        ManagerBkView* _managerBkView = ManagerBkView::getInstance();
        // 销毁当前页和背景窗口
        LOG_I("销毁设置主页和背景窗口");
        _managerBkView->deleteLater();
        this->deleteLater();
    }
}

// 列表按键按事件
void Widget_Mainmenu::slotButtonClicked()
{
    Widget_Base* w = NULL;
    QObject* sender = QObject::sender();
    int box_type = sender->property("type").toInt();
    LOG_D("发送信号控件类型属性 %d", box_type);
    switch (box_type)
    {
    case BOX_QUERY:
        w = new WidgetListmenu(0, model_queryInfo, tr("查询"));
        break;

    case BOX_SETTING:
    {
        QString retv;
        _passDialog = new WidgetMessage;
        LOG_I("xxxxxxxx 2\n");
        if (QDialog::Rejected==_passDialog->ExecPasswordInput(retv))
        {
            delete _passDialog;
            _passDialog = NULL;
            return;
        }
        delete _passDialog;
        _passDialog = NULL;

        LOG_I("点击了确定按键\n");
        // 验证密码
        if (!checkPass(retv))
        {
            // 弹框提示
            WidgetMessage::GetInstance()->ShowMessageHide(tr("密码错误"), false, NULL, 1);
            return;
        }
        w = new WidgetListmenu(0, model_setting, tr("设置"));
        //w = new Widget_Setting(0, tr("设置"));
        break;
    }
    default:
        return;
        break;
    }

    // 获取背景窗口
    ManagerBkView* _managerBkView = ManagerBkView::getInstance();
    w->setBackPage(this);
    _managerBkView->addWidgetShow(w);
    _managerBkView->show();
    this->hide();
}

// 校验密码
bool Widget_Mainmenu::checkPass(const QString &pass)
{
    if (pass.isNull() || pass.isEmpty())
        return false;
    // 验证密码，88994788
    if (pass.compare("88994788"))
        return false;
    return true;
}
