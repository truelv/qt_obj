#include "sflinebox.h"
#include "ui_messagelinebox.h"

SFLineBox::SFLineBox() :
    ui(new Ui::MessageLineBox)
{

}

SFLineBox::~SFLineBox()
{
    delete ui;
}

void SFLineBox::bindUi(QWidget *w)
{
    ui->setupUi(w);
}

void SFLineBox::updateCount(int num)
{
    printf("更新数字 %d\n", num);
    ui->count->setText(QString::number(num));
}

