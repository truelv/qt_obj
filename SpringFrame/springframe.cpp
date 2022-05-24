#include "springframe.h"
#include "ui_springframe.h"
#include "base/utils/mixShell.h"
#include "global.h"
#include <QWSServer>
#include <QColor>
#include <QDebug>
#include <QTimer>

SpringFrame::SpringFrame(QWidget *parent, SF_TYPE type, const QRect &rect, bool btshow) :
    QDialog(parent),
    ui(new Ui::SpringFrame),
    _count(0)
{
    // 主窗口
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    QWSServer::setBackground(QColor(0,0,0,0));
    ui->cancel->setVisible(btshow);
    ui->sure->setVisible(btshow);

    // 子窗口
    _uiOpt = NewInterWin(type);
    _uiOpt->bindUi(ui->widget);
    _type = type;
    // 设置控件位置
    ui->frame->setGeometry(rect);
    showMaximized();
}

SpringFrame::~SpringFrame()
{
    printf("销毁弹框\n");
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
#if 0
    while (true) {
        printf("显示\n");
        show();
        QCoreApplication::processEvents();
        sleep(3);
        printf("隐藏\n");
        hide();
        QCoreApplication::processEvents();
        sleep(3);
    }
#endif


    if (_event==SFEV_DIALOG_REJECT)
    {
        hide();
        QCoreApplication::processEvents();
    }

    _event = e;
    if (0==_count)
    {
        _count = sec;
        QTimer::singleShot(1000, this, SLOT(countTimeOut()));
    }
    else
        _count = sec;

    show();
    QCoreApplication::processEvents();

    if (SFEV_DIALOG_REJECT==e)
        exec();
    else
        show();
}

void DelLayoutItem(QLayoutItem* layoutItem)
{
    if (layoutItem->layout())
    {
        printf("是一个layout\n");
        QLayoutItem* layout = NULL;
        while((layout=((QLayout*)layoutItem)->takeAt(0)))
            DelLayoutItem(layout);
    }

    printf("删除一个布局控件\n");
    delete layoutItem;
}

// 返回值为true说明有切换控件操作
bool SpringFrame::switchType(SF_TYPE type, const QRect& rect)
{

    // 设置控件位置
    ui->frame->setGeometry(rect);

    if (_type==type)
        return false;

    // 考虑删除弹簧
    // 删除所有的子控件
#if 0
    const QList<QObject*>& items = ui->widget->findChildren<QObject*>();
    printf("控件数量 %d\n", items.count());
    for (QObject *item : items) {
        qDebug() << item->objectName();
        delete item;
    }
#else
    const QList<QWidget*>& items = ui->widget->findChildren<QWidget*>();
    printf("控件数量 %d\n", items.count());
    for (QWidget *item : items) {
        qDebug() << item->objectName();
        delete item;
    }

    DelLayoutItem(ui->widget->layout());
#if 0
    QLayoutItem* layout = NULL;
    while ((layout=ui->widget->layout()->takeAt(0)))
    {
        printf("xxxx %s\n", "删除一个布局控件");
        delete layout;
    }
    delete (ui->widget->layout());
#endif
#endif

    if (NULL!=_uiOpt)
    {
        delete _uiOpt;
        _uiOpt = NULL;
    }

    _uiOpt = NewInterWin(type);
    _uiOpt->bindUi(ui->widget);
    _type = type;

    return true;
}

InterUi *SpringFrame::NewInterWin(SF_TYPE type)
{
    InterUi* interUI = NULL;
    // 子窗口
    switch (type) {
    case SF_485ERR:
        interUI = new SF485Error;
        break;
    case SF_INPUTLINE:
        interUI = new SFInputLine;
        break;
    case SF_LINEBOX:
        interUI = new SFLineBox;
        break;
    case SF_LINETEXT:
    default:
        interUI = new SFLineText;
        break;
    }

    return interUI;
}

void SpringFrame::on_sure_clicked()
{
    // 控件销毁，执行子控件的获取数据函数
    if (NULL==_uiOpt)
        return ;
    _uiOpt->returnInput();
    accept();
    //deleteLater();
}

void SpringFrame::on_cancel_clicked()
{
    // 控件销毁/隐藏，根据继承类重写决定
    reject();
    //deleteLater();
}

void SpringFrame::countTimeOut()
{
    printf("当前数字 %d\n", _count);
#if 1
    switch (_event)
    {
    case SFEV_REBOOT:
        // 更新数字
        _uiOpt->updateCount(_count);
        break;
    case SFEV_DIALOG_EXIT:
    case SFEV_DIALOG_HIDE:
    default:
        break;
    }
#endif

    if (0==_count)
    {
        // 时间到
        switch (_event) {
        case SFEV_REBOOT:
            // 执行重启操作
            if(-1==exeShell(CMD_REBOOT, NULL, 0))
            {
                printf("执行重启，重启设备失败\n");
            }
            // 应用退出
            qApp->quit();
            break;
        case SFEV_DIALOG_EXIT:
            this->deleteLater();
            break;
        case SFEV_DIALOG_REJECT:
        case SFEV_DIALOG_HIDE:
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






