#include "MachineNumber.h"
#include <QLineEdit>
#include <QIntValidator>

static INPUT_ITEM inWids[] = {
    {INPUT_LINEEDIT, 0, "读头号", "0", NULL, NULL, NULL},
};

// 计算控件数量
static const int len = sizeof(inWids)/sizeof(INPUT_ITEM);

MachineNumber::MachineNumber()
{
    for (int i=0;i<len;i++)
    {
        AddWidget(&inWids[i]);
    }
    AppendVSpacer();
}

int MachineNumber::GetInput(QVariantList &retval)
{
    QLineEdit* ed = NULL;
    for (int i=0;i<len;i++)
    {
        ed = (QLineEdit*)inWids[i].inWid;
        retval.append(ed->text());
    }
    return 0;
}

int MachineNumber::SetInput(QVariantList &retval)
{
    QLineEdit* ed = NULL;
    for (int i=0;i<len;i++)
    {
        ed = (QLineEdit*)inWids[i].inWid;
        ed->setText(retval[i].toString());
        ed->setMaxLength(1);
        ed->setValidator(new QIntValidator(ed));
    }
    return 0;
}
