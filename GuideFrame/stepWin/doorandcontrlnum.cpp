#include "doorandcontrlnum.h"
#include <QLineEdit>

static INPUT_ITEM inWids[] = {
    {INPUT_LINEEDIT, 0, "控制器号", "0", NULL, NULL, NULL},
    {INPUT_LINEEDIT, 1, "门号", "0", NULL, NULL, NULL},
};

DoorAndContrlNum::DoorAndContrlNum()
{
    // 计算控件数量
    int len = sizeof(inWids)/sizeof(INPUT_ITEM);
    for (int i=0;i<len;i++)
    {
        AddWidget(&inWids[i]);
    }
    AppendVSpacer();
}

int DoorAndContrlNum::GetInput(QVariantList &retval)
{
    QLineEdit* ed = (QLineEdit*)inWids[0].inWid;
    retval.append(ed->text());
    ed = (QLineEdit*)inWids[1].inWid;
    retval.append(ed->text());
    return 0;
}

