#include "dialog_base.h"
#include "ui_dialog_base.h"
#include "ui_dialog_volumesetting.h"
#include "widget/widgetmessage.h"

Dialog_Base::Dialog_Base(QWidget *parent, const QString &title) :
    QDialog(parent),
    ui(new Ui::Dialog_Base)
{
    ui->setupUi(this);
    ui->show_title->setText(title);
    ui->bt_cancel->setStyleSheet("font: 45pt;");
    ui->bt_confirm->setStyleSheet("font: 45pt;");
    ui->show_title->setStyleSheet("font: 45pt;");
}

Dialog_Base::~Dialog_Base()
{
    delete ui;
}

void Dialog_Base::hideKeyBoard()
{
    ui->bt_cancel->setFocus();
}

QWidget *Dialog_Base::getContentWidget()
{
    return ui->content_widget;
}

void Dialog_Base::setContentWidget(QWidget* w)
{
    ui->content_layout->addWidget(w);
}

void Dialog_Base::hideConfirmButton()
{
    ui->bt_confirm->hide();
}

void Dialog_Base::setCancelText(const QString &text)
{
    ui->bt_cancel->setText(text);
}

void Dialog_Base::on_bt_cancel_clicked()
{
    this->deleteLater();
}

void Dialog_Base::on_bt_confirm_clicked()
{
    // 弹框提示
    WidgetMessage::GetInstance()->ShowMessageHide(tr("设置成功"), false, NULL, 1);
    this->deleteLater();
}
