#ifndef DIALOG_VOLUMESETTING_H
#define DIALOG_VOLUMESETTING_H
#include "dialog_base.h"
namespace Ui {
class Dialog_VolumeSetting;
}
class Dialog_VolumeSetting : public Dialog_Base
{
    Q_OBJECT
public:
    explicit Dialog_VolumeSetting(Dialog_Base* parent=0, const QString& title="");
    ~Dialog_VolumeSetting();

private slots:
    void slotValueChanged(int value);

private:
    Ui::Dialog_VolumeSetting* ui;

    int _volume;
};

#endif // DIALOG_VOLUMESETTING_H
