#include "dialog_facesetting.h"
#include "ui_dialog_facesetting.h"
#include "global.h"
#include "task/face/taskface.h"
#include "base/api/led.h"
#include "DB/dbyt.h"

Dialog_FaceSetting::Dialog_FaceSetting(Dialog_Base *parent, const QString &title) :
    Dialog_Base(parent, title),
    ui(new Ui::Dialog_FaceSetting)
{
    ui->setupUi(&_w);
    setContentWidget(&_w);
    _w.setStyleSheet("border: 0px solid black;");

    setCancelText(tr("退出"));

    _is_living = g_FaceInfo.faceLive==0?false:true;
    if (_is_living)
    {
        ui->switch_bt_living->setStyleSheet(QString("border-image:url(%1/switch_close.png);")
                                            .arg(UI_IMG_DIR));
        ui->label_openorclose->setText(tr("开启"));
    }
    else
    {
        ui->switch_bt_living->setStyleSheet(QString("border-image:url(%1/switch_open.png);")
                                            .arg(UI_IMG_DIR));
        ui->label_openorclose->setText(tr("关闭"));
    }

    // 获取人脸识别度
    float threshold = g_FaceInfo.faceRegcThreshold;
    _recg_threshold = threshold*100;
    ui->recg_threshold->setValue(_recg_threshold);
    ui->recg_threshold->setTracking(false);
    ui->recg_threshold_value->setText(QString::number(_recg_threshold));
    _recg_update = false;

    // 获取活体识别度
    threshold = g_FaceInfo.faceLiveThreshold;
    _living_threshold = threshold*100;
    ui->living_threshold->setValue(_living_threshold);
    ui->living_threshold->setTracking(false);
    ui->living_threshold_value->setText(QString::number(_living_threshold));
    _living_update = false;

    connect(ui->switch_bt_living, SIGNAL(clicked()), this, SLOT(on_switch_bt_living_clicked()));
    connect(ui->living_threshold, SIGNAL(valueChanged(int)), this, SLOT(on_living_threshold_valueChanged(int)));
    connect(ui->recg_threshold, SIGNAL(valueChanged(int)), this, SLOT(on_recg_threshold_valueChanged(int)));

    this->showFullScreen();
}

Dialog_FaceSetting::~Dialog_FaceSetting()
{
    delete ui;
}

void Dialog_FaceSetting::on_switch_bt_living_clicked()
{
    // 切换活体检测开关
    if (_is_living)
    {
        _is_living = false;

        ui->switch_bt_living->setStyleSheet(QString("border-image:url(%1/switch_open.png);")
                                            .arg(UI_IMG_DIR));
        ui->label_openorclose->setText(tr("关闭"));

        g_FaceInfo.faceLive = 0;
        DBYt::GetInstance()->UpdateKV("FaceModule", "faceLive", "0");
        TaskFace::GetInstance()->ReConfigSDK();
        infrared_led_ctrl(LED_OFF);
    }
    else
    {
        _is_living = true;

        ui->switch_bt_living->setStyleSheet(QString("border-image:url(%1/switch_close.png);")
                                            .arg(UI_IMG_DIR));
        ui->label_openorclose->setText(tr("开启"));
        g_FaceInfo.faceLive = 1;
        DBYt::GetInstance()->UpdateKV("FaceModule", "faceLive", "1");
        TaskFace::GetInstance()->ReConfigSDK();
        infrared_led_ctrl(LED_ON);
    }
}
//人脸识别度调节
void Dialog_FaceSetting::on_recg_threshold_valueChanged(int value)
{
    if (_recg_threshold!=value)
    {
        _recg_threshold = value;
        ui->recg_threshold_value->setText(QString::number(_recg_threshold));
        g_FaceInfo.faceRegcThreshold = _recg_threshold/100.0;
        DBYt::GetInstance()->UpdateKV("FaceModule",
                                      "faceRegcThreshold",
                                      QString().setNum(g_FaceInfo.faceRegcThreshold));
    }
}
//活体检测度调节
void Dialog_FaceSetting::on_living_threshold_valueChanged(int value)
{
    if (_living_threshold!=value)
    {
        _living_threshold = value;
        ui->living_threshold_value->setText(QString::number(_living_threshold));
        g_FaceInfo.faceLiveThreshold = _living_threshold/100.0;
        DBYt::GetInstance()->UpdateKV("FaceModule",
                                      "faceRegcThreshold",
                                      QString().setNum(g_FaceInfo.faceRegcThreshold));
    }
}

