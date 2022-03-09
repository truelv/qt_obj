#include "dialog_volumesetting.h"
#include "ui_dialog_volumesetting.h"
#include "DB/dbyt.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "task_exe.h"
#include "lombo_system_sound.h"
#include "global.h"
#ifdef __cplusplus
}
#endif

Dialog_VolumeSetting::Dialog_VolumeSetting(Dialog_Base *parent, const QString &title) :
    Dialog_Base(parent, title),
    ui(new Ui::Dialog_VolumeSetting)
{
    ui->setupUi(&_w);
    setContentWidget(&_w);
    _w.setStyleSheet("border: 0px solid black;");

    setCancelText(tr("退出"));
    // 从数据库获取音量值
    ui->label_4->setStyleSheet("font: 45pt;");
    _volume = g_BaseInfo.playVolume;
    ui->show_volume->setStyleSheet("font: 45pt;");
    ui->show_volume->setText(QString("%1").arg(_volume));
    ui->volume_slider->setTracking(false);
    ui->volume_slider->setValue(_volume);
    connect(ui->volume_slider, SIGNAL(valueChanged(int)), this, SLOT(slotValueChanged(int)));

    this->showFullScreen();
}

Dialog_VolumeSetting::~Dialog_VolumeSetting()
{
    delete ui;
}

int task_exe_set_volume(void* arg)
{
    int* volume = (int*)arg;
    lombo_system_set_volume(*volume);
    g_BaseInfo.playVolume = *volume;
    DBYt::GetInstance()->UpdateKV("BaseInfo", "playVolume", *volume);
    lombo_system_sound_play(WELCOME_SOUND);

    return 0;
}
//音量调节
void Dialog_VolumeSetting::slotValueChanged(int value)
{
    if (_volume!=value)
    {
        _volume = value;
        ui->show_volume->setText(QString("%1").arg(_volume));
        task_exe_req* req = (task_exe_req*)calloc(sizeof(task_exe_req), 1);
        req->task_num = 1;
        req->tasks[0] = task_exe_set_volume;
        req->args[0] = &_volume;
        task_exe_CommitReq(req);
    }
}



