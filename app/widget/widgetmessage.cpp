#include "widgetmessage.h"
#include "global.h"
#include "signalsender.h"
#include "task_exe.h"

WidgetMessage* WidgetMessage::_intent = NULL;
WidgetMessage::WidgetMessage()
{
    SignalSender *sender = SignalSender::getInstance();
    connect(sender, SIGNAL(signalMessageHeadHide(const QString&,bool,char*,int)),
            this, SLOT(ShowMessageHeadHide(const QString&,bool,char*,int)));
    connect(sender, SIGNAL(signalShowMessageHide(const QString&,bool,char*,int)),
            this, SLOT(ShowMessageHide(const QString&,bool,char*,int)));

    ui->cancel->setStyleSheet("font-size:50px");
    ui->sure->setStyleSheet("font-size:50px");
    //setStyleSheet("#SpringFrame{background-color:rgb(0,0,0,30);}");

}

WidgetMessage *WidgetMessage::GetInstance()
{
    if (NULL==_intent)
        _intent = new WidgetMessage;
    _intent->hide();
    _intent->hideButton(false);
    return _intent;
}

WidgetMessage::~WidgetMessage()
{
    LOG_I("销毁弹框\n");
    SignalSender *sender = SignalSender::getInstance();
    disconnect(sender, SIGNAL(signalMessageHeadHide(const QString,bool,char*,int)),
               this, SLOT(ShowMessageHeadHide(const QString,bool,char*,int)));
    _intent = NULL;
}

void WidgetMessage::ExecMessageHeadHide(const QString &msg, bool isVoice, char *voiceFile, int type)
{
    //LOG_I("消息框地址 %x\n", _intent);
    switchType(SF_LINETEXT, QRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
    SFLineText* iLine = dynamic_cast<SFLineText*>(getUiOpt());
    iLine->ui->label->setText(msg);
    ui->title->setVisible(false);
    ui->frame->setStyleSheet("");
    LOG_I("消息类型 %d\n", type);
    switch (type) {
    case MSG_ERROR:
        iLine->ui->label->setStyleSheet("margin:5px;border-radius:20px;font-size:50px;background-color:rgb(29,50,163,254);");
        break;
    case MSG_WARNING:
        iLine->ui->label->setStyleSheet("margin:5px;border-radius:20px;font-size:50px;background-color:rgb(213,85,80,254);");
        break;
    case MSG_SUCCES:
    default:
        // 默认成功色
        iLine->ui->label->setStyleSheet("margin:5px;border-radius:20px;font-size:50px;background-color:rgb(0,93,209,254);");
        break;
    }

    PlayVoice(msg, isVoice, voiceFile);

    showTimeOut(SFEV_DIALOG_REJECT, 3);
    LOG_I("顶部弹框显示\n");
}

// InputLine
int WidgetMessage::ExecPasswordInput(QString& retv)
{
    switchType(SF_INPUTLINE, QRect(SCREEN_WIDTH*0.05,
                                   (SCREEN_HEIGHT-SCREEN_WIDTH*0.6)*0.4,
                                   SCREEN_WIDTH*0.9, SCREEN_WIDTH*0.6));

    LOG_I("xxxxxxxxx  3\n");
    ui->frame->setStyleSheet("#frame{border-image:url(" PROJECT_DIR_IMG"/title_dialog_background.png);}");
    ui->title->setVisible(true);

    LOG_I("xxxxxxxxx  7\n");
    SFInputLine* iPutLine = dynamic_cast<SFInputLine*>(getUiOpt());
    iPutLine->bindInputRetval(&retv);
    iPutLine->ui->label->setText(tr("输入密码"));
    iPutLine->ui->label->setStyleSheet("font-size:40px;color:rgb(255,0,0);margin-right:20px;");
    iPutLine->ui->lineEdit->setStyleSheet("font-size: 30px;background-color:rgb(255,255,255);color:rgb(0,0,0);");
    iPutLine->ui->lineEdit->setEchoMode(QLineEdit::Password);

    hideButton(true);
    LOG_I("密码弹框\n");
    // exec返回后，对象没有删除
    return exec();
}

int WidgetMessage::ExecMessageButton(const QString &msg, bool isVoice, char *voiceFile)
{
    Q_UNUSED(isVoice)
    Q_UNUSED(voiceFile)

    switchType(SF_LINEBOX, QRect(SCREEN_WIDTH*0.05,
                                   (SCREEN_HEIGHT-SCREEN_WIDTH*0.6)*0.4,
                                   SCREEN_WIDTH*0.9, SCREEN_WIDTH*0.6));

    ui->frame->setStyleSheet("#frame{border-image:url(" PROJECT_DIR_IMG"/title_dialog_background.png);}");
    ui->title->setVisible(true);

    SFLineBox* iLinebox = dynamic_cast<SFLineBox*>(getUiOpt());
    iLinebox->ui->count->setVisible(false);
    iLinebox->ui->msg->setText(msg);
    iLinebox->ui->msg->setStyleSheet("font-size:48px;color:rgb(0,0,0);");

    hideButton(true);
    LOG_I("居中显示信息框，按键操作\n");
    return exec();
}

void WidgetMessage::hideKeyBoard()
{
    ui->cancel->setFocus();
}

void WidgetMessage::PlayVoice(const QString &msg, bool isVoice, char *voiceFile)
{
    if (!isVoice)
        return ;

    task_exe_req* task_req = (task_exe_req*)calloc(sizeof(task_exe_req), 1);
    task_req->task_num = 1;
    if (NULL==voiceFile)
    {
        task_req->tasks[0] = task_exe_PlayString;
        task_req->args[0] = msg.toAscii().data();
    }
    else
    {
        task_req->tasks[0] = task_exe_PlayWav;
        task_req->args[0] = (void*)voiceFile;
    }

    task_exe_CommitReq(task_req);
}

// rgb(29,50,163,254) 蓝色
// (0,93,209,1)
// (213,85,80,1) 红色
void WidgetMessage::ShowMessageHeadHide(const QString &msg, bool isVoice, char *voiceFile, int type)
{
    switchType(SF_LINETEXT, QRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
    SFLineText* iLine = dynamic_cast<SFLineText*>(getUiOpt());
    iLine->ui->label->setText(msg);
    ui->title->setVisible(false);
    ui->frame->setStyleSheet("");

    LOG_I("消息类型 %d\n", type);
    switch (type) {
    case MSG_ERROR:
        iLine->ui->label->setStyleSheet("border-radius:20px;background-color:rgb(29,50,163,254);");
        break;
    case MSG_WARNING:
        iLine->ui->label->setStyleSheet("border-radius:20px;background-color:rgb(213,85,80,254);");
        break;
    case MSG_SUCCES:
    default:
        // 默认成功色
        iLine->ui->label->setStyleSheet("border-radius:20px;background-color:rgb(0,93,209,254);");
        break;
    }

    showTimeOut(SFEV_DIALOG_HIDE, 3);
    LOG_I("顶部弹框显示\n");

    PlayVoice(msg, isVoice, voiceFile);
}

void WidgetMessage::ShowMessageHide(const QString &msg, bool isVoice, char *voiceFile, int timeOut)
{
    switchType(SF_LINEBOX, QRect(SCREEN_WIDTH*0.05,
                                  (SCREEN_HEIGHT-SCREEN_WIDTH*0.6)*0.4,
                                  SCREEN_WIDTH*0.9, SCREEN_WIDTH*0.6));

    ui->frame->setStyleSheet("#frame{border-image:url(" PROJECT_DIR_IMG"/title_dialog_background.png);}");
    ui->title->setVisible(true);

    SFLineBox* iLinebox = dynamic_cast<SFLineBox*>(getUiOpt());
    iLinebox->ui->count->setVisible(false);
    iLinebox->ui->msg->setText(msg);
    iLinebox->ui->msg->setStyleSheet("font-size:48px;color:rgb(0,0,0);");
    showTimeOut(SFEV_DIALOG_HIDE, timeOut);
    LOG_I("居中弹框显示\n");
    PlayVoice(msg, isVoice, voiceFile);
}

void WidgetMessage::ShowMessageReboot(const QString &msg, bool isVoice, char *voiceFile, int timeOut)
{
    switchType(SF_LINEBOX, QRect(SCREEN_WIDTH*0.05,
                                  (SCREEN_HEIGHT-SCREEN_WIDTH*0.6)*0.4,
                                  SCREEN_WIDTH*0.9, SCREEN_WIDTH*0.6));

    ui->frame->setStyleSheet("#frame{border-image:url(" PROJECT_DIR_IMG"/title_dialog_background.png);}");
    ui->title->setVisible(true);

    SFLineBox* iLinebox = dynamic_cast<SFLineBox*>(getUiOpt());
    iLinebox->ui->count->setVisible(true);
    iLinebox->ui->count->setStyleSheet("font-size:40px;color:rgb(0,0,0);");
    iLinebox->ui->count->setText(QString::number(timeOut));
    iLinebox->ui->msg->setText(msg);
    iLinebox->ui->msg->setStyleSheet("font-size:48px;color:rgb(0,0,0);");
    showTimeOut(SFEV_REBOOT, timeOut);
    LOG_I("居中弹框显示重启\n");
    PlayVoice(msg, isVoice, voiceFile);
}

void WidgetMessage::ShowMessageDrop(QString &msg, bool isVoece, char *voiceFile)
{
    Q_UNUSED(msg)
    Q_UNUSED(isVoece)
    Q_UNUSED(voiceFile)
}

void WidgetMessage::ShowMessageKeep(const QString &msg, bool isVoice, char *voiceFile)
{
    switchType(SF_LINEBOX, QRect(SCREEN_WIDTH*0.05,
                                  (SCREEN_HEIGHT-SCREEN_WIDTH*0.6)*0.4,
                                  SCREEN_WIDTH*0.9, SCREEN_WIDTH*0.6));

    ui->frame->setStyleSheet("#frame{border-image:url(" PROJECT_DIR_IMG"/title_dialog_background.png);}");

    SFLineBox* iLinebox = dynamic_cast<SFLineBox*>(getUiOpt());
    iLinebox->ui->count->setVisible(false);
    iLinebox->ui->msg->setText(msg);
    iLinebox->ui->msg->setStyleSheet("font-size:48px;color:rgb(0,0,0);");

    this->show();
    LOG_I("保持居中显示，等待隐藏调用\n");
    PlayVoice(msg, isVoice, voiceFile);
}


