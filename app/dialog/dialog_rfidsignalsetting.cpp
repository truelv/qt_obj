#include "dialog_rfidsignalsetting.h"
#include "ui_dialog_rfidsignalsetting.h"
#include "global.h"
#include "base/bsp/pn512.h"
#include "DB/dbyt.h"



Dialog_RFIDSignalSetting::Dialog_RFIDSignalSetting(Dialog_Base *parent, const QString &title) :
    Dialog_Base(parent, title),
    ui(new Ui::Dialog_RFIDSignalSetting)
{
    ui->setupUi(&_w);
    setContentWidget(&_w);
    _w.setStyleSheet("border: 0px solid black;");
    this->setStyleSheet("QRadioButton{color:white;font-size:50px;}"
                        "QRadioButton::indicator{width:50px;height:50px}"
                        "QRadioButton::indicator:checked{border-image:url(" PROJECT_DIR_IMG"/check_press.png)}");

    // 选中信号强度
    switch (g_rfidinfo.rfidSignalLevel) {
    case 3:
        ui->signal_strongest->setChecked(true);
        _sigType = 3;
        break;
    case 2:
        ui->signal_enhanced->setChecked(true);
        _sigType = 2;
        break;
    case 1:
    default:
        ui->signal_normal->setChecked(true);
        _sigType = 1;
        break;
    }

    connect(ui->signal_strongest, SIGNAL(clicked()), this, SLOT(slotSignalStrongest()));
    connect(ui->signal_enhanced, SIGNAL(clicked()), this, SLOT(slotSignalEnhanced()));
    connect(ui->signal_normal, SIGNAL(clicked()), this, SLOT(slotSignalNormal()));

    this->showFullScreen();
}

Dialog_RFIDSignalSetting::~Dialog_RFIDSignalSetting()
{
    delete ui;
}

void Dialog_RFIDSignalSetting::slotSignalNormal()
{
    if (1==_sigType)
    {
        return;
    }
    saveSignalType(1);
}

void Dialog_RFIDSignalSetting::slotSignalEnhanced()
{
    if (2==_sigType)
    {
        return;
    }
    saveSignalType(2);
}

void Dialog_RFIDSignalSetting::slotSignalStrongest()
{
    if (3==_sigType)
    {
        return;
    }
    saveSignalType(3);
}

void Dialog_RFIDSignalSetting::saveSignalType(char type)
{
    g_rfidinfo.rfidSignalLevel = type;
    DBYt::GetInstance()->UpdateKV("RfidModule", "rfidSignalLevel", type);
    // 切换信号强度
    PcdSignalLevelSet(g_rfidinfo.rfidSignalLevel);
}


