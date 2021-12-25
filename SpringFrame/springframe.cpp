#include "springframe.h"
#include "ui_springframe.h"
#include <QWSServer>
#include <QColor>
#include <QDebug>
#include <QTimer>

SpringFrame::SpringFrame(QWidget *parent, SF_TYPE type, int x, int y, int w, int h) :
    QDialog(parent),
    ui(new Ui::SpringFrame)
{
    // 主窗口
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    QWSServer::setBackground(QColor(0,0,0,0));

    // 子窗口
    switch (type) {
    case SF_485ERR:
        _uiOpt = new SF485Error;
        break;
    case SF_INPUTLINE:
        _uiOpt = new SFInputLine;
        break;
    case SF_LINETEXT:
    default:
        _uiOpt = new SFLineText;
        break;
    }

    _uiOpt->bindUi(ui->widget);
    _type = type;
    ui->frame->setGeometry(x,y,w,h);
    showMaximized();
}

SpringFrame::~SpringFrame()
{
    delete _uiOpt;
    delete ui;
}

void SpringFrame::setFrameStyle(const QString &style)
{
    QString str("#frame{");
    str.append(style).append("}");
    ui->frame->setStyleSheet(str);
}

void SpringFrame::setButtonStyle(const QString &style)
{
    ui->cancel->setStyleSheet(style);
    ui->sure->setStyleSheet(style);
}

void SpringFrame::hideButton(bool show)
{
    if (show)
    {
        ui->cancel->show();
        ui->sure->show();
    }
    else
    {
        ui->cancel->setVisible(false);
        ui->sure->setVisible(false);
    }
}

InterUi *SpringFrame::getUiOpt()
{
    return _uiOpt;
}

void SpringFrame::showTimeOut(TIMEOUT_EV e, int sec)
{
    // sec秒后按e类事件来处理
    _event = e;
    _count = sec;
    QTimer::singleShot(1000, this, SLOT(countTimeOut()));
}

void SpringFrame::on_sure_clicked()
{
    // 控件销毁，执行子控件的获取数据函数
    _uiOpt->returnInput();
    deleteLater();
}

void SpringFrame::on_cancel_clicked()
{
    // 控件销毁/隐藏，根据继承类重写决定
    deleteLater();
}

void SpringFrame::countTimeOut()
{
    switch (_event)
    {
    case EV_REBOOT:
        break;
    case EV_DIALOG_EXIT:
    case EV_DIALOG_HIDE:
    default:
        break;
    }

    if (0==_count)
    {
        // 时间到
        switch (_event) {
        case EV_REBOOT:

            break;
        case EV_DIALOG_EXIT:
            this->deleteLater();
            break;
        case EV_DIALOG_HIDE:
            // 隐藏
            this->hide();
            break;
        default:
            break;
        }
    }
    else
    {
        _count--;
        QTimer::singleShot(1000, this, SLOT(countTimeOut()));
    }
}






