// wifi的列表按键
#include "buttontype3.h"
#include "ui_buttontype3.h"

ButtonType3::ButtonType3(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ButtonType3)
{
    ui->setupUi(this);
}

ButtonType3::~ButtonType3()
{
    delete ui;
}

void ButtonType3::setSSIDName(const QString &name)
{
    ui->ssid_name->setText(name);
}

void ButtonType3::setSignalIcon(const QString &qss)
{
    ui->signal->setStyleSheet(qss);
}

void ButtonType3::setConnected(const QString &sta)
{
    ui->connected->setText(sta);
}
