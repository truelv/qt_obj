#ifndef DIALOG_FACESETTING_H
#define DIALOG_FACESETTING_H
#include "dialog_base.h"
namespace Ui {
class Dialog_FaceSetting;
}

class Dialog_FaceSetting : public Dialog_Base
{
    Q_OBJECT
public:
    explicit Dialog_FaceSetting(Dialog_Base* parent=0, const QString& title="");
    ~Dialog_FaceSetting();

private slots:
    void on_switch_bt_living_clicked();
    void on_recg_threshold_valueChanged(int value);
    void on_living_threshold_valueChanged(int value);

private:
    Ui::Dialog_FaceSetting* ui;

    bool _is_living;
    int _recg_threshold;
    int _living_threshold;
    bool _recg_update;
    bool _living_update;
};

#endif // DIALOG_FACESETTING_H
