#include "inputkvs.h"
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QDebug>

InputKVs::InputKVs(QWidget *parent) :
    QWidget(parent)
{
    _vLayout = new QVBoxLayout(this);
    _vLayout->setContentsMargins(60, 160, 60, 100);
    _vLayout->setSpacing(30);
    _iList.clear();
}

InputKVs::~InputKVs()
{
    foreach (INPUT_ITEM* item, _iList) {
        if (NULL!=item->inWid)
        {
            qDebug() << "清除输入控件";
            delete item->inWid;
            item->inWid = NULL;
        }

        if (NULL!=item->lable)
        {
            qDebug() << "清除标题控件";
            delete item->lable;
            item->lable = NULL;
        }

        if (NULL!=item->hLayout)
        {
            qDebug() << "清除布局控件";
            delete item->hLayout;
            item->hLayout = NULL;
        }
    }
    delete _vLayout;
}

void InputKVs::AddWidget(INPUT_ITEM *item)
{
    if (NULL==item)
        return ;

    QWidget* input = NULL;
    // 横向布局
    QHBoxLayout* hLayout = new QHBoxLayout;
    item->hLayout = (QWidget*)hLayout;

    if (NULL!=item->lableName)
    {
        QLabel* label = new QLabel(item->lableName);
        // 添加默认样式
        label->setMinimumWidth(200);
        label->setStyleSheet("font-size:50px;color:white");
        hLayout->addWidget(label);
        item->lable = label;
    }

    // 以下添加输入控件
    switch (item->type) {
    case INPUT_LINEEDIT:
        if(NULL!=item->inTmpstr)
            input = new QLineEdit(item->inTmpstr);
        else
            input = new QLineEdit;
        input->setStyleSheet("font-size:50px;");
        break;
    case INPUT_CHECKBOX:
        input = new QCheckBox;
        break;
    default:
        break;
    }

    if (NULL!=input)
    {
        item->inWid = input;
        hLayout->addWidget(input);
    }

    _vLayout->addLayout(hLayout);
    _iList.append(item);
}

void InputKVs::AppendVSpacer()
{
    _vLayout->addStretch();
}

void InputKVs::AppendInputValue(INPUT_ITEM *item, QVariantList &list)
{
    if (NULL==item || NULL==item->inWid)
        return ;

    switch (item->type) {
    case INPUT_LINEEDIT:
        list.append(dynamic_cast<QLineEdit*>(item->inWid)->text());
        break;
    case INPUT_CHECKBOX:
        list.append(dynamic_cast<QCheckBox*>(item->inWid)->isChecked()?1:0);
        break;
    case INPUT_LABEL:
        break;
    default:
        break;
    }
}
