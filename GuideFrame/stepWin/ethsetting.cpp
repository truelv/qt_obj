#include "ethsetting.h"
#include "ui_ethsetting.h"

EthSetting::EthSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EthSetting)
{
    ui->setupUi(this);
    setStyleSheet("QLabel{color:white;font-size:50px}QLineEdit{font-size:48px;color:black}"
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

void EthSetting::EditEnable(bool on)
{
    ui->ip->setEnabled(on);
    ui->mask->setEnabled(on);
    ui->gateway->setEnabled(on);
    ui->dns->setEnabled(on);

    if (on)
    {
        ui->ip->setStyleSheet("background-color: rgb(255, 255, 255);color: rgb(0, 0, 0);");
        ui->mask->setStyleSheet("background-color: rgb(255, 255, 255);color: rgb(0, 0, 0);");
        ui->gateway->setStyleSheet("background-color: rgb(255, 255, 255);color: rgb(0, 0, 0);");
        ui->dns->setStyleSheet("background-color: rgb(255, 255, 255);color: rgb(0, 0, 0);");
    }
    else
    {
        ui->ip->setStyleSheet("background-color: rgb(131, 131, 131);color: rgb(0, 0, 0);");
        ui->mask->setStyleSheet("background-color: rgb(131, 131, 131);color: rgb(0, 0, 0);");
        ui->gateway->setStyleSheet("background-color: rgb(131, 131, 131);color: rgb(0, 0, 0);");
        ui->dns->setStyleSheet("background-color: rgb(131, 131, 131);color: rgb(0, 0, 0);");
    }
}

void EthSetting::on_dhcp_stateChanged(int state)
{
    printf("vvvvvvv %d\n", state);
    bool check = 0==state?false:true;
    EditEnable(!check);
}
