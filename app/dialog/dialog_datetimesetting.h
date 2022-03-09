#ifndef DIALOG_DATETIMESETTING_H
#define DIALOG_DATETIMESETTING_H

#include "dialog_base.h"
namespace Ui {
class Dialog_DateTimeSetting;
}
class Dialog_DateTimeSetting : public Dialog_Base
{
    Q_OBJECT
public:
    explicit Dialog_DateTimeSetting(Dialog_Base* parent=0, const QString& title="");
    ~Dialog_DateTimeSetting();

private slots:
    void on_bt_confirm_clicked();

private:
    Ui::Dialog_DateTimeSetting* ui;
};

#endif // DIALOG_DATETIMESETTING_H
