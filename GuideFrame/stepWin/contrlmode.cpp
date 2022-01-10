#include "contrlmode.h"
#include <QDebug>

static SELECT_ITEM contrlSl[] = {
    {0, "韦根模式", 0},
    {1, "485模式", 0},
};

ContrlMode::ContrlMode()
{
    int len = sizeof(contrlSl)/sizeof(SELECT_ITEM);
    for (int i=0;i<len;i++)
    {
        AddSelectItem(&contrlSl[i]);
    }
    AppendVSpacer();
    _index = 0;
    ((QRadioButton*)(contrlSl[0].w))->setChecked(true);
}




