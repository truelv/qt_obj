#include "sflinetext.h"
#include "ui_messagelinetext.h"

SFLineText::SFLineText() :
    ui(new Ui::MessageLineText)
{

}

SFLineText::~SFLineText()
{
    delete ui;
}

void SFLineText::setLineTextStyle(const QString &style)
{
    ui->label->setStyleSheet(style);
}

void SFLineText::setLineTextAlignment(Qt::Alignment a)
{
    ui->label->setAlignment(a);
}

void SFLineText::bindUi(QWidget *w)
{
    ui->setupUi(w);
}

void SFLineText::setShowText(const QString &text)
{
    ui->label->setText(text);
}

