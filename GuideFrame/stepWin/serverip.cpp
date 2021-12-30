#include "serverip.h"
#include <QLineEdit>

static INPUT_ITEM inWids[] = {
    {INPUT_LINEEDIT, 0, "服务IP", "0", NULL, NULL, NULL},
    {INPUT_LINEEDIT, 1, "服务端口", "0", NULL, NULL, NULL},
};
// 计算控件数量
static const int len = sizeof(inWids)/sizeof(INPUT_ITEM);

ServerIP::ServerIP()
{

    for (int i=0;i<len;i++)
    {
        AddWidget(&inWids[i]);
    }
    AppendVSpacer();
}

int ServerIP::GetInput(QVariantList &retval)
{
    for (int i=0;i<len;i++)
    {
        AppendInputValue(&inWids[i], retval);
    }
    return 0;
}

