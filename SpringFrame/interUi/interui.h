/**
 * 子控件基类，定义子控件的通用接口
 * 子控件不是控件实例，只在主控件中添加组件
*/
#ifndef IFACEINTERUI_H
#define IFACEINTERUI_H
#include <QString>
#include <QWidget>

class InterUi
{
public:
    InterUi();
    virtual ~InterUi();
    virtual void returnInput();
    virtual void updateCount(int num);
    virtual void bindUi(QWidget* w) = 0;
};

#endif // IFACEINTERUI_H
