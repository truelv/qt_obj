#ifndef SELECTWIN_H
#define SELECTWIN_H

#include <QWidget>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QCheckBox>
#include <QSpacerItem>
#include "ifacechildopt.h"
/**
 * 单选框窗口，其他具体单选功能，继承实现
*/
typedef struct {
    int index;
    const char* label;
    QWidget* w;
} SELECT_ITEM;

class SelectWin : public QWidget, public IfaceChildOpt
{
    Q_OBJECT
public:
    explicit SelectWin(QWidget *parent = 0);
    virtual ~SelectWin();
    void AddSelectItem(SELECT_ITEM* item);
    void AppendVSpacer();
    int GetInput(QVariantList& retval);
    int SetInput(QVariantList& retval);

protected slots:
    virtual void SlotRbtClick(bool click);

protected:
    int _index;
private:
    QVBoxLayout* _vLayout;
    QVector<SELECT_ITEM*> _slList;
};

#endif // SELECTWIN_H
