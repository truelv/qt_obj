#include "guideframe.h"
#include "ui_guideframe.h"
#include "stepWin/ethsetting.h"
#include "stepWin/contrlmode.h"
#include "stepWin/authmode.h"
#include "stepWin/serverip.h"
#include "stepWin/serverurl.h"
#include "stepWin/doorandcontrlnum.h"
#include <QDebug>

GuideFrame::GuideFrame(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::GuideFrame)
{
    ui->setupUi(this);
    _stackeCount = ui->stackedWidget->count();
    wList.clear();

    showFullScreen();
}

GuideFrame::~GuideFrame()
{
    foreach (ONE_FRAME* frame, wList) {
        if (NULL!=frame->w)
        {
            delete frame->w;
            frame->w = NULL;
        }
    }
    wList.clear();
    delete ui;
}

void GuideFrame::AddWidget(ONE_FRAME *frame)
{
    if (NULL==frame)
        return;

    printf("窗口序号 %d\n", frame->index);
    switch (frame->type) {
    case GUIDE_ETH:
        frame->w = new EthSetting;
        break;
    case GUIDE_WIFI:
        break;
    case GUIDE_CONTRLMODE:
        frame->w = new ContrlMode;
        break;
    case GUIDE_AUTHMODE:
        frame->w = new AuthMode;
        break;
    case GUIDE_SERVERIP:
        frame->w = new ServerIP;
        break;
    case GUIDE_SERVERURL:
        frame->w = new ServerUrl;
        break;
    case GUIDE_DOORNUM:
        frame->w = new DoorAndContrlNum;
        break;
    default:
        break;
    }
    if (NULL!=frame->w)
    {
        //qDebug() << "子控件地址 " << frame->w;
        wList.append(frame);
        ui->stackedWidget->addWidget(frame->w);
        InitUIData(frame->index);
        _stackeCount++;
    }
}

void GuideFrame::RemoveWidget(int index)
{
    ONE_FRAME *frame = wList[index];
    wList.remove(index);
    if (NULL!=frame->w)
    {
        delete frame->w;
        frame->w = NULL;
    }
    _stackeCount = ui->stackedWidget->count();
    printf("子窗口数量 %d\n", ui->stackedWidget->count());
}

void GuideFrame::ShowIndex(int index)
{
    if (wList.count()<=0)
        return;

    ui->stackedWidget->setCurrentIndex(index);
    ONE_FRAME* frame = wList[index];
    frame->pre = index;
    ui->title->setText(tr(frame->title));
}

void GuideFrame::SetButtonStyle(const QString &style)
{
    ui->btnext->setStyleSheet(style);
    ui->btpre->setStyleSheet(style);
}

void GuideFrame::SetTileStyle(const QString &style)
{
    ui->title->setStyleSheet(style);
}

void GuideFrame::SetFrameStyle(const QString &style)
{
    this->setStyleSheet(style);
}

void GuideFrame::on_btnext_clicked()
{
    int index = ui->stackedWidget->currentIndex();
    printf("切换下一个窗口，当前 %d\n", index);
    int next  = ReturnPageInput(index);
    printf("切换下一个窗口，下一个 %d\n", next);
    if (index==next)
        return;
    //index = index<_stackeCount?index:(_stackeCount-1);
    if (-1==next)
    {
        deleteLater();
        return;
    }

    ui->stackedWidget->setCurrentIndex(next);
    ONE_FRAME* frame = wList[next];
    // 设置窗口标题
    ui->title->setText(tr(frame->title));
    // 保存上一个窗口序号
    frame->pre = index;
}

void GuideFrame::on_btpre_clicked()
{
    int index = ui->stackedWidget->currentIndex();
    printf("切换上一个窗口 %d\n", index);
    ONE_FRAME* frame = wList[index];
    // 切换窗口
    index = frame->pre;
    index = index>=0?index:0;
    ui->stackedWidget->setCurrentIndex(index);
    frame = wList[index];
    ui->title->setText(tr(frame->title));
}
