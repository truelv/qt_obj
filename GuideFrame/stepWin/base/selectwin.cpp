#include "selectwin.h"
#include "global.h"
#include <QDebug>

SelectWin::SelectWin(QWidget *parent) :
    QWidget(parent)
{
    //printf("父控件\n");
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
    _slList.clear();
    delete _vLayout;
}

void SelectWin::AddSelectItem(SELECT_ITEM *item)
{
    if (NULL==item)
        return ;

    QRadioButton* ck = new QRadioButton(tr(item->label), this);
    if (NULL==ck)
        return;

    ck->setProperty("id", item->index);
    item->w = ck;
    ck->setStyleSheet("font-size:50px;color:white");
    if (NULL!=_vLayout)
        _vLayout->addWidget(ck);

    connect(ck, SIGNAL(clicked(bool)), this, SLOT(SlotRbtClick(bool)));
    _slList.append(item);
}

void SelectWin::AppendVSpacer()
{
    _vLayout->addStretch();
    //QRadioButton::indicator:checked{image:url(./image4.png);QRadioButton::indicator:unchecked{image:url(./image1.png);}
    setStyleSheet("QRadioButton::indicator{width:50px;height:50px}"
                  "QRadioButton::indicator:checked{border-image:url(" PROJECT_DIR_IMG"/radio_button.png);}");

}

int SelectWin::GetInput(QVariantList &retval)
{
    retval.append(_index);
    //printf("带回数据 %d\n", retval.length());
    return 0;
}

int SelectWin::SetInput(QVariantList &retval)
{
    int index = retval[0].toInt();
    if (index>=_slList.count())
        index = 0;

    SELECT_ITEM* item = _slList[index];
    if (NULL==item || NULL==item->w)
        return -1;

    ((QRadioButton*)(item->w))->setChecked(true);
    _index = index;
    return 0;
}

void SelectWin::SlotRbtClick(bool click)
{
    Q_UNUSED(click)
    _index = sender()->property("id").toInt();
    //printf("选择了权限模式 %d\n", _index);
}



