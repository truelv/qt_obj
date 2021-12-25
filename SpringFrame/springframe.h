#ifndef SPRINGFRAME_H
#define SPRINGFRAME_H
#include "interUi/interui.h"
#include "interUi/sfinputline.h"
#include "interUi/sflinetext.h"
#include "interUi/sf485error.h"
#include <QDialog>

// 子控件类型
typedef enum {
    SF_LINETEXT = 0,     // 显示一行文字
    SF_INPUTLINE,       // 显示一个输入框
    SF_485ERR           // 显示底部2行文字显示，顶部一个图片显示
} SF_TYPE;

// 超时显示超时处理类型
typedef enum {
    EV_REBOOT,
    EV_DIALOG_EXIT,
    EV_DIALOG_HIDE,
} TIMEOUT_EV;

namespace Ui {
class SpringFrame;
class MessageLineText;
class InputLine;
}

class SpringFrame : public QDialog
{
    Q_OBJECT

public:
    explicit SpringFrame(QWidget *parent = 0, SF_TYPE type=SF_LINETEXT, int x=0, int y=0, int w=100, int h=100);
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
    void showTimeOut(TIMEOUT_EV e=EV_DIALOG_HIDE, int sec=3);
    // 切换类型

private slots:
    void on_sure_clicked();
    virtual void on_cancel_clicked();
    void countTimeOut();

private:
    Ui::SpringFrame *ui;
    SF_TYPE _type;
    InterUi* _uiOpt;
    // 超时显示
    int _count;
    TIMEOUT_EV _event;
};

#endif // SPRINGFRAME_H
