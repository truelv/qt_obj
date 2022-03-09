/**
 * 消息提示框，
 * 接受直接调用提示和信号提示
*/
#ifndef WIDGETMESSAGE_H
#define WIDGETMESSAGE_H
#include "springframe.h"
#include "global.h"
#include <QString>

typedef enum {
    SHOW_KEEP = 0,
    SHOW_TIMEOUT,
} SHOW_TYPE;

#define MSG_ERROR       GMSG_ERROR
#define MSG_WARNING     GMSG_WARNING
#define MSG_SUCCES      GMSG_SUCCES

class WidgetMessage : public SpringFrame
{
    Q_OBJECT
public:
    WidgetMessage();
    static WidgetMessage* GetInstance();
    ~WidgetMessage();
    void ExecMessageHeadHide(const QString& msg, bool isVoice, char* voiceFile, int type);
    // 这些是与人交互的弹窗
    // 显示密码输入框
    int ExecPasswordInput(QString &retv);
    int ExecMessageButton(const QString& msg, bool isVoice, char* voiceFile);
    // 这些是与人交互的弹窗 end
    void hideKeyBoard();

protected:
    void PlayVoice(const QString& msg, bool isVoice, char* voiceFile);

public slots:
    // 这些是与设备交互的弹窗
    // 顶部文字显示（超时隐藏）
    void ShowMessageHeadHide(const QString& msg, bool isVoice, char* voiceFile, int type);
    // 居中弹框，背景为信息提示（超时隐藏）
    void ShowMessageHide(const QString& msg, bool isVoice, char* voiceFile, int timeOut);
    // 居中弹框，背景为信息提示（超时reboot）
    void ShowMessageReboot(const QString& msg, bool isVoice, char* voiceFile, int timeOut);
    // 居中弹框，背景为信息提示（超时销毁）
    void ShowMessageDrop(QString& msg, bool isVoece, char* voiceFile);
    // 居中弹框，背景为信息提示（保持，无按键）
    void ShowMessageKeep(const QString& msg, bool isVoice, char* voiceFile);
    //

private:
    static WidgetMessage* _intent;
};

#endif // WIDGETMESSAGE_H
