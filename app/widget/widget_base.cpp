#include "widget_base.h"
#include "ui_widget_base.h"
#include "managerbkview.h"
#include "global.h"
#include "widgetmessage.h"

#define LOGTAG "widget_base"

Widget_Base::Widget_Base(QWidget *parent, const QString &title) :
    QWidget(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    _backPage = 0;

    _sender = SignalSender::getInstance();

    _backTitle.setTitle(title);
    _backTitle.setStyleSheet("font: 50pt;");
    _backTitle.setParent(this);
    connect(&_backTitle, SIGNAL(buttonBackClick()), this, SLOT(slotPageBack()));
    connect(_sender, SIGNAL(signalResetToRunWin()), this, SLOT(slotRestToRun()));
    this->showMaximized();
}

Widget_Base::~Widget_Base()
{
}

void Widget_Base::setBackPage(QWidget *w)
{
    _backPage = w;
}

void Widget_Base::autoToBack()
{
    WidgetMessage* msgDialog = WidgetMessage::GetInstance();
    if (!msgDialog->isHidden())
    {
        // 如果弹框不是隐藏，隐藏弹框
        msgDialog->hideKeyBoard();
        msgDialog->reject();
    }

    if (NULL!=_backPage)
    {
        // 上一页不为空
        LOG_I("复位窗口，返回一个窗口");
        ((Widget_Base*)_backPage)->autoToBack();
        // 当前页销毁
        this->deleteLater();
    }
}

void Widget_Base::slotPageBack()
{
    if (NULL!=_backPage)
    {
        // 上一页不为空
        ManagerBkView* _managerBkView = ManagerBkView::getInstance();
        // 上一页添加显示
        _managerBkView->addWidgetShow(_backPage);
        _managerBkView->show();
        _backPage->show();
        // 当前页销毁
        this->deleteLater();
    }
}

void Widget_Base::slotRestToRun()
{
    if (!this->isHidden())
        autoToBack();
}
