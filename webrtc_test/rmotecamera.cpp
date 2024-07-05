#include "rmotecamera.h"
#include "ui_rmotecamera.h"

RmoteCamera::RmoteCamera(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RmoteCamera)
{
    ui->setupUi(this);
}

RmoteCamera::~RmoteCamera()
{
    delete ui;
}
