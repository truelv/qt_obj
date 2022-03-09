// 设置列表按键
#include "buttontype2.h"
#include "ui_buttontype2.h"
#include "global.h"

ButtonType2::ButtonType2(QWidget *parent) :
    QPushButton(parent),
    ui(new Ui::ButtonType2)
{
    ui->setupUi(this);
    this->setFocusPolicy(Qt::NoFocus);
    this->setStyleSheet(QString("#ButtonType2{border-image:url(%1/list_bt.png);}"
                                "#ButtonType2:pressed{border-image:url(%1/list_bt_press.png);}")
                        .arg(UI_IMG_DIR));
}

ButtonType2::~ButtonType2()
{
    delete ui;
}

void ButtonType2::setText(const QString &text)
{
    ui->text->setText(text);
    ui->text->setStyleSheet("font: 45pt'微软雅黑';");
    ui->text->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
}

void ButtonType2::mousePressEvent(QMouseEvent *e)
{
    ui->text->setStyleSheet("#text{color:black;font: 45pt'微软雅黑';}");
    return QPushButton::mousePressEvent(e);
}

void ButtonType2::mouseReleaseEvent(QMouseEvent *e)
{
    ui->text->setStyleSheet("#text{color:white;font: 45pt'微软雅黑';}");
    return QPushButton::mouseReleaseEvent(e);
}
