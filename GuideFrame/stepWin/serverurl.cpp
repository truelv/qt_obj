#include "serverurl.h"
#include <QLineEdit>

static INPUT_ITEM inWids[] = {
    {INPUT_LABEL, 0, "输入人脸url全地址", "0", NULL, NULL, NULL},
    {INPUT_LINEEDIT, 1, NULL, "0", NULL, NULL, NULL},
};
// 计算控件数量
static const int len = sizeof(inWids)/sizeof(INPUT_ITEM);

ServerUrl::ServerUrl()
{
    for (int i=0;i<len;i++)
    {
        AddWidget(&inWids[i]);
    }
    AppendVSpacer();
}

int ServerUrl::GetInput(QVariantList &retval)
{
    for (int i=0;i<len;i++)
    {
        AppendInputValue(&inWids[i], retval);
    }
    return 0;
}

int ServerUrl::SetInput(QVariantList &retval)
{
    QLineEdit* ed = (QLineEdit*)inWids[1].inWid;
    ed->setText(retval[0].toString());
    return 0;
}
