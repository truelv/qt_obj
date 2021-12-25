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
    virtual void bindUi(QWidget* w) = 0;
};

#endif // IFACEINTERUI_H
