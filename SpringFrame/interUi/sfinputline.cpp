#include "sfinputline.h"
#include "ui_inputline.h"

#define EDIT_DEFAUT_HIGHT 70

SFInputLine::SFInputLine() :
    ui(new Ui::InputLine)
{

}

SFInputLine::~SFInputLine()
{
    delete ui;
}

void SFInputLine::bindUi(QWidget *w)
{
    ui->setupUi(w);
    ui->lineEdit->setMinimumHeight(EDIT_DEFAUT_HIGHT);
}

void SFInputLine::setLabelStyle(const QString &style)
{
    ui->label->setStyleSheet(style);
}

void SFInputLine::setLabelText(const QString &lable)
{
    ui->label->setText(lable);
}

void SFInputLine::setInputStyle(const QString &style)
{
    ui->lineEdit->setStyleSheet(style);
}

void SFInputLine::setInputText(const QString &text)
{
    ui->lineEdit->setText(text);
}

void SFInputLine::returnInput()
{
    if (NULL!=_input)
        *_input = ui->lineEdit->text();
}

void SFInputLine::bindInputRetval(QString *retval)
{
    _input = retval;
}

