#include "listitemwidget.h"
#include "ui_listitemwidget.h"

LIstItemWidget::LIstItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LIstItemWidget)
{
    ui->setupUi(this);
}

LIstItemWidget::~LIstItemWidget()
{
    delete ui;
}

void LIstItemWidget::setBackColor(const QString &qss)
{
    ui->frame->setStyleSheet(qss);
}

void LIstItemWidget::setSize(const QSize &size)
{
    this->setMaximumSize(size);
    setMinimumSize(size);
}

void LIstItemWidget::setKV(const QString &key, const QString &value)
{
    ui->key->setText(key);
    ui->value->setText(value);
}
