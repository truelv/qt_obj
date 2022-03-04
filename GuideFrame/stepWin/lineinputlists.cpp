#include "lineinputlists.h"
#include <QLineEdit>
#include <QDebug>

LineInputLists::LineInputLists(LineInputItem* enty)
{
    if (NULL==enty)
    {
        _items = NULL;
        _lineCount = 0;
        return;
    }

    _items = enty->items;
    _lineCount = enty->count;

    for (int i=0;i<_lineCount;i++)
    {
        AddWidget(&_items[i]);
    }
    AppendVSpacer();
}

int LineInputLists::GetInput(QVariantList &retval)
{
    QLineEdit* ed = NULL;
    for (int i=0;i<_lineCount;i++)
    {
        ed = (QLineEdit*)_items[i].inWid;
        retval.append(ed->text());
    }
    return 0;
}

int LineInputLists::SetInput(QVariantList &retval)
{
    if (retval.isEmpty())
        return 0;
    QLineEdit* ed = NULL;
    for (int i=0;i<_lineCount;i++)
    {
        ed = (QLineEdit*)_items[i].inWid;
        ed->setText(retval[i].toString());
    }
    return 0;
}

QWidget *LineInputLists::GetWidget(int index)
{
    int itemIndex = index/2;
    if (itemIndex>=_lineCount)
        return NULL;

    //printf("获取窗口内部控件 %d \n", itemIndex);
    INPUT_ITEM* item = &_items[itemIndex];
    if (index%2)
        return (item->inWid);
    else
        return (item->lable);
}

