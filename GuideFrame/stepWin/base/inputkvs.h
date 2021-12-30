#ifndef INPUTKVS_H
#define INPUTKVS_H

#include <QWidget>
#include <QVBoxLayout>
#include "ifacechildopt.h"
typedef enum {
    INPUT_LINEEDIT = 0,
    INPUT_CHECKBOX,
    INPUT_LABEL,
} INPUT_ITEM_TYPE;

typedef struct {
    INPUT_ITEM_TYPE type;
    int index;
    const char* lableName;
    const char* inTmpstr;
    QWidget* lable;
    QWidget* inWid;
    QWidget* hLayout;
} INPUT_ITEM;

class InputKVs : public QWidget, public IfaceChildOpt
{
    Q_OBJECT
public:
    explicit InputKVs(QWidget *parent = 0);
    ~InputKVs();
    void AddWidget(INPUT_ITEM* item);
    void AppendVSpacer();
    void AppendInputValue(INPUT_ITEM* item, QVariantList& list);

private:
    QVBoxLayout* _vLayout;
    QVector<INPUT_ITEM*> _iList;
};

#endif // INPUTKVS_H
