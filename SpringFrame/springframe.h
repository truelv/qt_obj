/**
 * 弹框控件
 * 弹框行为，
 * 1、可以直接显示，通过按键来结束显示
 * 2、倒计时显示，自定义显示时间（持续显示时间长度）
 *  1、倒计时后有3中行为，自我销毁，隐藏，重启设备
 * 弹框内部自定义显示子控件
 * 1、显示一行文字
 * 2、显示一个输入框，带lable的那种
 * 3、显示485出错提示（自定义，不通用）
 * 弹框主体包括一个控件主体和2个按键，可以对其设置样式
 * 主要，窗体设置背景色或背景图片
 * 按键设置背景色或背景图片，文字大小及颜色
*/
#ifndef SPRINGFRAME_H
#define SPRINGFRAME_H
#include "interUi/interui.h"
#include "interUi/sfinputline.h"
#include "interUi/sflinetext.h"
#include "interUi/sf485error.h"
#include "interUi/sflinebox.h"
#include "ui_inputline.h"
#include "ui_springframe.h"
#include "ui_messagelinebox.h"
#include "ui_messagelinetext.h"
#include <QDialog>
#include <QSize>

// 子控件类型
typedef enum {
    SF_LINETEXT = 0,     // 显示一行文字
    SF_INPUTLINE,       // 显示一个输入框
    SF_LINEBOX,         // 显示一个提示框
    SF_485ERR           // 显示底部2行文字显示，顶部一个图片显示
} SF_TYPE;

// 超时显示超时处理类型
typedef enum {
    SFEV_REBOOT,
    SFEV_DIALOG_EXIT,
    SFEV_DIALOG_HIDE,
    SFEV_DIALOG_REJECT,
} TIMEOUT_EV;

namespace Ui {
class SpringFrame;
class MessageLineText;
class InputLine;
class MessageLineBox;
}

class SpringFrame : public QDialog
{
    Q_OBJECT
public:
    explicit SpringFrame(QWidget *parent = 0, SF_TYPE type=SF_LINETEXT,
                         const QRect& rect=QRect(0,0,100,100), bool btshow=false);
    ~SpringFrame();
    // 设置frame的样式
    void setFrameStyle(const QString& style);
    // 设置按键样式
    void setButtonStyle(const QString& style);
    // 设置按键隐藏
    void hideButton(bool show);
    // 获取子控件
    InterUi* getUiOpt();
    // 计时显示
    void showTimeOut(TIMEOUT_EV e=SFEV_DIALOG_HIDE, int sec=3);
    // 显示
    // 切换类型
    bool switchType(SF_TYPE type, const QRect &rect);

protected:
    // 实例化子窗口
    InterUi* NewInterWin(SF_TYPE type);


private slots:
    void on_sure_clicked();
    virtual void on_cancel_clicked();
    void countTimeOut();

public:
    Ui::SpringFrame *ui;

protected:   
    SF_TYPE _type;
    InterUi* _uiOpt;
    // 超时显示
    int _count;
    TIMEOUT_EV _event;
};

#endif // SPRINGFRAME_H
