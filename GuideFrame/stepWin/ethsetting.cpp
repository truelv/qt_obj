#include "ethsetting.h"
#include "ui_ethsetting.h"

EthSetting::EthSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EthSetting)
{
    ui->setupUi(this);
    setStyleSheet("QLabel{color:white;font-size:50px}QLineEdit{font-size:60px}");
}

EthSetting::~EthSetting()
{
    delete ui;
}

int EthSetting::GetInput(QVariantList &retval)
{
    retval.append(ui->ip->text());
    retval.append(ui->mask->text());
    retval.append(ui->gateway->text());
    retval.append(ui->dns->text());
    retval.append(ui->dhcp->isChecked()?1:0);
    return 0;
}



