#include "titledialog2.h"
#include "ui_titledialog2.h"

TitleDialog2::TitleDialog2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TitleDialog2)
{

    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    ui->setupUi(this);

    this->showMaximized();
}

TitleDialog2::~TitleDialog2()
{
    delete ui;
}
