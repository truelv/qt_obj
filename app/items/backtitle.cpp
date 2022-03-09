/**
 * 窗口顶部导航栏
 * 包括返回按键和标题
 */
#include "backtitle.h"
#include "ui_backtitle.h"
#include "global.h"
/**
 * 构造函数
 * @brief BackTitle::BackTitle
 * @param parent
 */
BackTitle::BackTitle(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BackTitle)
{
    ui->setupUi(this);
    ui->show_title->setAlignment(Qt::AlignCenter);
    // 设置返回按键图片
    ui->back_button->setStyleSheet(QString("#back_button{border-image:url(%1/back.png);margin:30px;}")
                                   .arg(UI_IMG_DIR));
}
/**
 * 析构函数
 * @brief BackTitle::~BackTitle
 */
BackTitle::~BackTitle()
{
    delete ui;
}
/**
 * 清空标题
 * @brief BackTitle::clearTitle
 */
void BackTitle::clearTitle()
{
    ui->show_title->clear();
}
/**
 * 设置标题
 * @brief BackTitle::setTitle
 * @param title
 */
void BackTitle::setTitle(const QString &title)
{
    ui->show_title->setText(title);
}
/**
 * 隐藏返回按键
 * @brief BackTitle::hideBackBt
 */
void BackTitle::hideBackBt()
{
    ui->back_button->hide();
    ui->show_title->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
}
/**
 * 槽函数，点击返回按键
 * @brief BackTitle::on_back_button_clicked
 */
void BackTitle::on_back_button_clicked()
{
    emit buttonBackClick();
}
