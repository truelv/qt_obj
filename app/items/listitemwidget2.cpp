#include "listitemwidget2.h"
#include "ui_listitemwidget2.h"

LIstItemWidget2::LIstItemWidget2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LIstItemWidget2)
{
    ui->setupUi(this);
    ui->value->setStyleSheet("font-size:17px;margin-left:20px");
}

LIstItemWidget2::~LIstItemWidget2()
{
    delete ui;
}

void LIstItemWidget2::setKV(const QString &key, const QString &value)
{
    ui->key->setText(key);
    ui->value->setText(value);
}

void LIstItemWidget2::setBackColor(const QString &qss)
{
    ui->frame->setStyleSheet(qss);
}
