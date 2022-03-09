#include "titledialog.h"
#include "ui_titledialog.h"
#include "global.h"

#define LOGTAG "title_dialog"

TitleDialog::TitleDialog(QWidget *parent, int *button) :
    QDialog(parent),
    _clickBt(button),
    ui(new Ui::TitleDialog)
{
    ui->setupUi(this);
    ui->cancel_bt->setStyleSheet("font: 45pt;");
    ui->sure_bt->setStyleSheet("font: 45pt;");
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    this->showMaximized();
}

TitleDialog::~TitleDialog()
{
    delete ui;
}

void TitleDialog::on_sure_bt_clicked()
{
    if (NULL!=_clickBt) {
        *_clickBt = BT_CONFIRM;
        _clickBt = NULL;
    }

    this->accept();
    this->hide();
}

void TitleDialog::on_cancel_bt_clicked()
{
    if (NULL!=_clickBt)
    {
        *_clickBt = BT_CANCEL;
        _clickBt = NULL;
    }

    this->reject();
    hide();
}
