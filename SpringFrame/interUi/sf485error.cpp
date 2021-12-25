#include "sf485error.h"
#include "ui_sf485error.h"

SF485Error::SF485Error() :
    ui(new Ui::SF485Error)
{
}

SF485Error::~SF485Error()
{
    delete ui;
}

void SF485Error::bindUi(QWidget *w)
{
    ui->setupUi(w);
}

void SF485Error::setLabelStyle(const QString &style)
{
    ui->img->setStyleSheet(style);
}

void SF485Error::setTitleText(const QString &text)
{
    ui->title->setText(text);
}

void SF485Error::setTitleStyle(const QString &style)
{
    ui->title->setStyleSheet(style);
}

void SF485Error::setContentText(const QString &text)
{
    ui->content->setText(text);
}

void SF485Error::setContentStyle(const QString &style)
{
    ui->content->setStyleSheet(style);
}
