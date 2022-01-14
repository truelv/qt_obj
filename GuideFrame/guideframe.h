#ifndef GUIDEFRAME_H
#define GUIDEFRAME_H

#include <QWidget>
#include <QDialog>
#include "stepWin/base/ifacechildopt.h"
#include "stepWin/base/inputkvs.h"
#include "stepWin/lineinputlists.h"

typedef enum {
    GUIDE_ETH = 0,
    GUIDE_WIFI,
    GUIDE_CONTRLMODE,
    GUIDE_AUTHMODE,
    GUIDE_SERVERIP,
    GUIDE_SERVERURL,
    GUIDE_DOORNUM,
    GUIDE_MACHNUM,
    GUIDE_LINEINPUT_LISTS,
} GUIDEFRAME_TYPE;
// 描述一个窗口，
typedef struct {
    GUIDEFRAME_TYPE type;   // 类型
    int index;              // 位置（编号）
    int next;               // 下一个编号
    int pre;                // 上一个编号
    bool ignore;            // 是否可以跳过
    const char* title;
    QWidget* w;             // 窗口指针
    void* pri;               // 私有参数
    //
} ONE_FRAME;

namespace Ui {
class GuideFrame;
}

class GuideFrame : public QDialog
{
    Q_OBJECT

public:
    explicit GuideFrame(QDialog *parent = 0);
    virtual ~GuideFrame();
    void AddWidget(ONE_FRAME* frame);
    void RemoveWidget(int index);
    void ShowIndex(int index);
    void SetButtonStyle(const QString& style);
    void SetTileStyle(const QString& style);
    void SetFrameStyle(const QString& style);
    void HideKeyBoard();

protected slots:
    void on_btnext_clicked();
    void on_btpre_clicked();
    // 实现这个方法，获取输入参数，处理参数，
    // 并返回下一个子窗口序号为下一个显示窗口，返回-1结束引导
    virtual int ReturnPageInput(int index) = 0;
    // 实现这个方法，给控件设置初始参数
    virtual void InitUIData(int index) = 0;

protected:
    Ui::GuideFrame *ui;
    int _stackeCount;
    QVector<ONE_FRAME*> wList;
};

#endif // GUIDEFRAME_H
