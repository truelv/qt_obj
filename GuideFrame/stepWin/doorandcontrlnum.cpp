#include "doorandcontrlnum.h"
#include <QLineEdit>

static INPUT_ITEM inWids[] = {
    {INPUT_LINEEDIT, 0, "控制器号", "0", NULL, NULL, NULL},
};
// 计算控件数量
static const int len = sizeof(inWids)/sizeof(INPUT_ITEM);

DoorAndContrlNum::DoorAndContrlNum()
{
    for (int i=0;i<len;i++)
    {
        AddWidget(&inWids[i]);
    }
    AppendVSpacer();
}

int DoorAndContrlNum::GetInput(QVariantList &retval)
{
    QLineEdit* ed = NULL;
    for (int i=0;i<len;i++)
    {
        ed = (QLineEdit*)inWids[i].inWid;
        retval.append(ed->text());
    }
    return 0;
}

int DoorAndContrlNum::SetInput(QVariantList &retval)
{
    QLineEdit* ed = NULL;
    for (int i=0;i<len;i++)
    {
        ed = (QLineEdit*)inWids[i].inWid;
        ed->setText(retval[i].toString());
    }
}

