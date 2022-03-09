#ifndef DIALOG_MODESETTING_H
#define DIALOG_MODESETTING_H
#include "dialog_base.h"
namespace Ui {
class Dialog_ModeSetting;
}

class Dialog_ModeSetting : public Dialog_Base
{
    Q_OBJECT
public:
    explicit Dialog_ModeSetting(Dialog_Base* parent=0, const QString& title="");
    ~Dialog_ModeSetting();

private slots:
    void on_bt_confirm_clicked();

private:
    Ui::Dialog_ModeSetting* ui;
};

#endif // DIALOG_MODESETTING_H
