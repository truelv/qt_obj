#ifndef DEVSELECT_H
#define DEVSELECT_H

#include <QDialog>

namespace Ui {
class DevSelect;
}

class DevSelect : public QDialog
{
    Q_OBJECT

public:
    explicit DevSelect(QWidget *parent = nullptr, int *plat_se = nullptr, int *dev_set=nullptr);
    ~DevSelect();

private slots:
    void on_plat_set_currentIndexChanged(int index);

    void on_dev_set_currentIndexChanged(int index);

    void on_bt_cancel_clicked();

    void on_bt_sure_clicked();

private:
    Ui::DevSelect *ui;

    int* _dev_set;
    int* _plat_set;
    int _tmp_dev;
    int _tmp_plat;
};

#endif // DEVSELECT_H
