#include "dialog_backlightsetting.h"
#include "ui_dialog_volumesetting.h"
#include "file_ops.h"
#include "global.h"
#include "DB/dbyt.h"


Dialog_BackLightSetting::Dialog_BackLightSetting(Dialog_Base *parent, const QString &title) :
    Dialog_Base(parent, title),
    ui(new Ui::Dialog_VolumeSetting)
{
    ui->setupUi(&_w);
    setContentWidget(&_w);
    _w.setStyleSheet("border: 0px solid black;");

    setCancelText(tr("退出"));

    // 从数据库获取背光值
    _backLight = g_BaseInfo.backlightValue;

    ui->show_volume->setStyleSheet("font: 45pt;");
    ui->show_volume->setText(QString("%1").arg(_backLight));

    ui->volume_slider->setTracking(false);
    ui->volume_slider->setMinimum(10);
    ui->volume_slider->setValue(_backLight);
    connect(ui->volume_slider, SIGNAL(valueChanged(int)), this, SLOT(slotValueChanged(int)));

    ui->label_4->setText(tr("当前亮度"));
    ui->label_4->setStyleSheet("font: 45pt;");
    this->showFullScreen();
}

Dialog_BackLightSetting::~Dialog_BackLightSetting()
{
    delete ui;
}
//设备音量调节
void Dialog_BackLightSetting::slotValueChanged(int value)
{
    LOG_I("滑块的数值333 %d", ui->volume_slider->value());
    if (_backLight!=value)
    {
        _backLight = value;
        ui->show_volume->setText(QString("%1").arg(_backLight));
        char* p = QString::number(_backLight).toAscii().data();
        file_write(INTERFACE_BACKLIGHT, p, strlen(p));

        g_BaseInfo.backlightValue = _backLight;
        DBYt::GetInstance()->UpdateKV("BaseInfo",
                                      "backlightValue",
                                      QString().setNum(_backLight));
    }
}


