#ifndef SPRINGFRAME_H
#define SPRINGFRAME_H
#include "interUi/interui.h"
#include "interUi/sfinputline.h"
#include "interUi/sflinetext.h"
#include "interUi/sf485error.h"
#include <QDialog>
#include <QSize>

// 子控件类型
typedef enum {
    SF_LINETEXT = 0,     // 显示一行文字
    SF_INPUTLINE,       // 显示一个输入框
    SF_485ERR           // 显示底部2行文字显示，顶部一个图片显示
} SF_TYPE;

// 超时显示超时处理类型
typedef enum {
    SFEV_REBOOT,
    SFEV_DIALOG_EXIT,
    SFEV_DIALOG_HIDE,
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
    explicit SpringFrame(QWidget *parent = 0, SF_TYPE type=SF_LINETEXT, const QRect& rect=QRect(0,0,100,100), bool btshow=false);
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
