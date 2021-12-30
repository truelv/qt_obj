#ifndef GUIDEFRAME_H
#define GUIDEFRAME_H

#include <QWidget>
#include "stepWin/base/ifacechildopt.h"

typedef enum {
    GUIDE_ETH = 0,
    GUIDE_WIFI,
    GUIDE_CONTRLMODE,
    GUIDE_AUTHMODE,
    GUIDE_SERVERIP,
    GUIDE_SERVERURL,
    GUIDE_DOORNUM,
} GUIDEFRAME_TYPE;
// 描述一个窗口，
typedef struct {
    GUIDEFRAME_TYPE type;   // 类型
    int index;              // 位置（编号）
    int next;               // 下一个编号
    int pre;                // 上一个编号
    bool ignore;            // 是否可以跳过
    const char* title;
    QWidget* w;             // 窗口指针，
    //
} ONE_FRAME;

namespace Ui {
class GuideFrame;
}

class GuideFrame : public QWidget
{
    Q_OBJECT

public:
    explicit GuideFrame(QWidget *parent = 0);
    virtual ~GuideFrame();
    void AddWidget(ONE_FRAME* frame);
    void RemoveWidget(int index);
    void ShowIndex(int index);
    void SetButtonStyle(const QString& style);
    void SetTileStyle(const QString& style);
    void SetFrameStyle(const QString& style);

protected slots:
    void on_btnext_clicked();
    void on_btpre_clicked();
    // 实现这个方法，获取输入参数，处理参数
    virtual void ReturnPageInput(int index) = 0;

private:
    Ui::GuideFrame *ui;
    int _stackeCount;
    QVector<ONE_FRAME*> wList;
};

#endif // GUIDEFRAME_H
