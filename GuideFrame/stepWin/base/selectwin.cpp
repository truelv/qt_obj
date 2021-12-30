#include "selectwin.h"
#include <QDebug>

SelectWin::SelectWin(QWidget *parent) :
    QWidget(parent)
{
    qDebug() << "父控件";
    //ui->setupUi(this);
    _vLayout = new QVBoxLayout(this);
    _vLayout->setContentsMargins(260, 160, 100, 100);
    _vLayout->setSpacing(30);
    setLayout(_vLayout);
    _slList.clear();
    _index = 0;
}

SelectWin::~SelectWin()
{
    foreach (SELECT_ITEM* item, _slList) {
        if (NULL!=item->w)
        {
            //qDebug() << "清除单选框选项";
            disconnect(dynamic_cast<QRadioButton*>(item->w), SIGNAL(clicked(bool)), this, SLOT(SlotRbtClick(bool)));
            delete item->w;
            item->w = NULL;
        }
    }
    delete _vLayout;
}

void SelectWin::AddSelectItem(SELECT_ITEM *item)
{
    if (NULL==item)
        return ;

    QRadioButton* ck = new QRadioButton(item->label, this);
    if (NULL==ck)
        return;

    ck->setProperty("id", item->index);
    item->w = ck;
    ck->setStyleSheet("font-size:50px;color:red");
    if (NULL!=_vLayout)
        _vLayout->addWidget(ck);

    connect(ck, SIGNAL(clicked(bool)), this, SLOT(SlotRbtClick(bool)));
    _slList.append(item);
}

void SelectWin::AppendVSpacer()
{
    _vLayout->addStretch();
}

int SelectWin::GetInput(QVariantList &retval)
{
    retval.append(_index);
    qDebug() << " 带回数据 "<< retval.length();
    return 0;
}

void SelectWin::SlotRbtClick(bool click)
{
    Q_UNUSED(click)
    _index = sender()->property("id").toInt();
    qDebug() << "选择了权限模式" << _index;
}



