#include "ethsetting.h"
#include "ui_ethsetting.h"

EthSetting::EthSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EthSetting)
{
    ui->setupUi(this);
    setStyleSheet("QLabel{color:white;font-size:50px}QLineEdit{font-size:60px}"
                  "QCheckBox::indicator{height:50px;width:50px}"
                  "QCheckBox::indicator:checked{border-image:url(/data/zytk_reader/img/check_press.png);}");
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

int EthSetting::SetInput(QVariantList &retval)
{
    ui->ip->setText(retval[0].toString());
    ui->mask->setText(retval[1].toString());
    ui->gateway->setText(retval[2].toString());
    ui->dns->setText(retval[3].toString());
    retval[4].toInt()?ui->dhcp->setChecked(true):ui->dhcp->setChecked(false);
    return 0;
}



