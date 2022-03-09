#include "dialog_datetimesetting.h"
#include "ui_dialog_datetimesetting.h"
#include "global.h"
#include "base/utils/mixShell.h"
#include "widget/widgetmessage.h"
#include <QDateTime>

Dialog_DateTimeSetting::Dialog_DateTimeSetting(Dialog_Base *parent, const QString &title) :
    Dialog_Base(parent, title),
    ui(new Ui::Dialog_DateTimeSetting)
{
    ui->setupUi(&_w);
    setContentWidget(&_w);
    _w.setStyleSheet("border: 0px solid black;");

    setCancelText(tr("退出"));
    // 获取时间
    QDateTime now = QDateTime::currentDateTime();
    QDate date = now.date();
    QTime time = now.time();

    ui->year->setValue(date.year());
    ui->year->setStyleSheet("font-size:40px");
    ui->month->setValue(date.month());
    ui->month->setStyleSheet("font-size:40px");
    ui->day->setValue(date.day());
    ui->day->setStyleSheet("font-size:40px");
    ui->hour->setValue(time.hour());
    ui->hour->setStyleSheet("font-size:40px");
    ui->min->setValue(time.minute());
    ui->min->setStyleSheet("font-size:40px");
    ui->sec->setValue(time.second());
    ui->sec->setStyleSheet("font-size:40px");

    this->showFullScreen();
}

Dialog_DateTimeSetting::~Dialog_DateTimeSetting()
{
    delete ui;
}

void Dialog_DateTimeSetting::on_bt_confirm_clicked()
{
    // 设置系统时间
    QString cmd;
    // date -s '2008-6-8 09:19:00'
    cmd = QString("date -s '%1-%2-%3 %4:%5:%6';hwclock -wl")
            .arg(ui->year->value(), 4, 10, QLatin1Char('0'))
            .arg(ui->month->value(), 2, 10, QLatin1Char('0'))
            .arg(ui->day->value(), 2, 10, QLatin1Char('0'))
            .arg(ui->hour->value(), 2, 10, QLatin1Char('0'))
            .arg(ui->min->value(), 2, 10, QLatin1Char('0'))
            .arg(ui->sec->value(), 2, 10, QLatin1Char('0'));
    LOG_D("cmd %s ", cmd.toAscii().data());
#if 0
    system(cmd.toAscii().data());
    sleep(1);
    system("hwclock -wl");
#else
    exeShell(cmd.toAscii().data(), NULL, 0);
#endif
    Dialog_Base::on_bt_confirm_clicked();
}

