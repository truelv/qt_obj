#include "guideframe.h"
#include "ui_guideframe.h"
#include "stepWin/ethsetting.h"
#include "stepWin/contrlmode.h"
#include "stepWin/authmode.h"
#include "stepWin/serverip.h"
#include "stepWin/serverurl.h"
#include "stepWin/doorandcontrlnum.h"
#include <QDebug>

GuideFrame::GuideFrame(QWidget *parent) :
    QWidget(parent),
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
    delete ui;
}

void GuideFrame::AddWidget(ONE_FRAME *frame)
{
    if (NULL==frame)
        return;

    qDebug() << "xxxx" << frame->index;
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
        qDebug() << "子控件地址 " << frame->w;
        _stackeCount++;
        wList.append(frame);
        qDebug()<< ui->stackedWidget->addWidget(frame->w) << _stackeCount;
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
    //qDebug() << "yyyyyyyy" << ui->stackedWidget->count();
}

void GuideFrame::ShowIndex(int index)
{
    if (wList.count()<=0)
        return;

    ui->stackedWidget->setCurrentIndex(index);
    ONE_FRAME* frame = wList[0];
    ui->title->setText(frame->title);
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
    ReturnPageInput(index);
    index++;
    index = index<_stackeCount?index:(_stackeCount-1);
    ui->stackedWidget->setCurrentIndex(index);
    ONE_FRAME* frame = wList[index];
    ui->title->setText(frame->title);
}

void GuideFrame::on_btpre_clicked()
{
    int index = ui->stackedWidget->currentIndex();
    index--;
    index = index>=0?index:0;
    ui->stackedWidget->setCurrentIndex(index);
    ONE_FRAME* frame = wList[index];
    ui->title->setText(frame->title);
}
