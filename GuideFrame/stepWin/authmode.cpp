#include "authmode.h"
#include <QDebug>

static SELECT_ITEM authSl[] = {
    {0 ,"正常", 0},
    {1, "全量", 0},
    {2, "外挂", 0}
};

AuthMode::AuthMode()
{
    printf("子控件\n");
    int len = sizeof(authSl)/sizeof(SELECT_ITEM);
    for (int i=0;i<len;i++)
    {
        AddSelectItem(&authSl[i]);
    }
    AppendVSpacer();
    _index = 0;
    ((QRadioButton*)(authSl[0].w))->setChecked(true);

}
