#include "devselect.h"
#include "ui_devselect.h"
#include "ui_defind.h"

extern DEV_TYPE dev[];
extern PLAT_TYPE plat[];


DevSelect::DevSelect(QWidget *parent, int* plat_set, int* dev_set) :
    QDialog(parent),
    ui(new Ui::DevSelect),
    _dev_set(dev_set),
    _plat_set(plat_set)
{
    ui->setupUi(this);

    for (int i=0;;i++)
    {
        if (CUM_EOF==dev[i].num)
            break;
        ui->dev_set->addItem(dev[i].name);
    }

    for (int i=0;;i++)
    {
        if (CUM_EOF==plat[i].num)
            break;
        if (!(plat[i].supflag&dev[*dev_set].devflag))
            continue ;
        ui->plat_set->addItem(plat[i].name);
    }

    if (nullptr!=plat_set)
        ui->plat_set->setCurrentIndex(*plat_set);
    if (nullptr!=dev_set)
        ui->dev_set->setCurrentIndex(*dev_set);

    ui->dev_set->setEnabled(false);
}

DevSelect::~DevSelect()
{
    delete ui;
}

void DevSelect::on_plat_set_currentIndexChanged(int index)
{
    _tmp_plat = index;
}

void DevSelect::on_dev_set_currentIndexChanged(int index)
{
    _tmp_dev = index;
}

void DevSelect::on_bt_cancel_clicked()
{
    this->reject();
}

void DevSelect::on_bt_sure_clicked()
{
    *_plat_set = _tmp_plat;
    *_dev_set = _tmp_dev;
    this->accept();
}
