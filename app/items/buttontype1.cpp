// 主设置菜单使用的按键，大长方形
#include "buttontype1.h"
#include "ui_buttontype1.h"
#include "global.h"
#include <QDebug>

ButtonType1::ButtonType1(QWidget *parent) :
    QPushButton(parent),
    ui(new Ui::ButtonType1)
{
    ui->setupUi(this);
    this->setFocusPolicy(Qt::NoFocus);
}

ButtonType1::~ButtonType1()
{
    delete ui;
}

void ButtonType1::setText(const QString &text)
{
    ui->text->setText(text);
    ui->text->setStyleSheet("font: 50pt'微软雅黑';");
    ui->text->setAlignment(Qt::AlignVCenter|Qt::AlignHCenter);
}

void ButtonType1::setIcon(const QString &qss)
{
    ui->icon->setStyleSheet(qss);
}

void ButtonType1::mousePressEvent(QMouseEvent *e)
{
    ui->text->setStyleSheet("#text{color:black;font: 50pt'微软雅黑';}");
    return QPushButton::mousePressEvent(e);
}

void ButtonType1::mouseReleaseEvent(QMouseEvent *e)
{
    ui->text->setStyleSheet("#text{color:white;font: 50pt'微软雅黑';}");
    return QPushButton::mouseReleaseEvent(e);
}
