#ifndef LINEINPUTLISTS_H
#define LINEINPUTLISTS_H
#include "base/inputkvs.h"

typedef struct {
    int count;
    INPUT_ITEM* items;
} LineInputItem;

class LineInputLists: public InputKVs
{
public:
    LineInputLists(LineInputItem* enty);
    int GetInput(QVariantList& retval);
    int SetInput(QVariantList& retval);
    QWidget *GetWidget(int index);

private:
    INPUT_ITEM* _items;
    int _lineCount;
};

#endif // LINEINPUTLISTS_H
