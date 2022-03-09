#include "dialog_soundtypesetting.h"
#include "ui_dialog_showtextsetting.h"
#include "global.h"
#include "base/bsp/pn512.h"
#include "DB/dbyt.h"


Dialog_SoundtypeSetting::Dialog_SoundtypeSetting(Dialog_Base *parent, const QString &title) :
    Dialog_Base(parent, title),
    ui(new Ui::Dialog_ShowtextSetting)
{
    ui->setupUi(&_w);
    setContentWidget(&_w);
    _w.setStyleSheet("border: 0px solid black;");
    this->setStyleSheet("QRadioButton{color:white;font-size:50px;}"
                        "QRadioButton::indicator{width:50px;height:50px}"
                        "QRadioButton::indicator:checked{border-image:url(" PROJECT_DIR_IMG"/check_press.png)}");

    // 选中信号强度
    switch (g_BaseInfo.soundType) {
    case TYPE_SHOW_HIDENAME:
        ui->hidename->setChecked(true);
        break;
    case TYPE_SHOW_CUSTOM:
        ui->customtext->setChecked(true);
        break;
    case TYPE_SHOW_FULLNAME:
    default:
        ui->fullname->setChecked(true);
        break;
    }

    connect(ui->fullname, SIGNAL(clicked()), this, SLOT(slotFullname()));
    connect(ui->hidename, SIGNAL(clicked()), this, SLOT(slotHidename()));
    connect(ui->customtext, SIGNAL(clicked()), this, SLOT(slotCustomText()));

    this->showFullScreen();
}

Dialog_SoundtypeSetting::~Dialog_SoundtypeSetting()
{
    delete ui;
}

void Dialog_SoundtypeSetting::slotCustomText()
{
    if (TYPE_SHOW_CUSTOM!=g_BaseInfo.soundType)
    {
        g_BaseInfo.soundType = TYPE_SHOW_CUSTOM;
        DBYt::GetInstance()->UpdateKV("TerminalInfo", "soundType", TYPE_SHOW_CUSTOM);
        // 保存内容
        return;
    }
}

void Dialog_SoundtypeSetting::slotHidename()
{
    if (TYPE_SHOW_HIDENAME!=g_BaseInfo.soundType)
    {
        g_BaseInfo.soundType = TYPE_SHOW_HIDENAME;
        DBYt::GetInstance()->UpdateKV("TerminalInfo", "soundType", TYPE_SHOW_HIDENAME);
        return;
    }
}

void Dialog_SoundtypeSetting::slotFullname()
{
    if (TYPE_SHOW_FULLNAME!=g_BaseInfo.soundType)
    {
        g_BaseInfo.soundType = TYPE_SHOW_FULLNAME;
        DBYt::GetInstance()->UpdateKV("TerminalInfo", "soundType", TYPE_SHOW_FULLNAME);
        return;
    }
}



