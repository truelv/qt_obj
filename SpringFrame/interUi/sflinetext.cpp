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

void SFLineText::bindUi(QWidget *w)
{
    ui->setupUi(w);
}


