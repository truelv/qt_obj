#ifndef DIALOG_BACKLIGHTSETTING_H
#define DIALOG_BACKLIGHTSETTING_H
#include "dialog_base.h"
#include "ui_dialog_volumesetting.h"
namespace Ui {
class Dialog_BackLightSetting;
}
class Dialog_BackLightSetting : public Dialog_Base
{
    Q_OBJECT
public:
    explicit Dialog_BackLightSetting(Dialog_Base* parent=0, const QString& title="");
    ~Dialog_BackLightSetting();

private slots:
    void slotValueChanged(int value);

private:
    Ui::Dialog_VolumeSetting* ui;

    int _backLight;
};

#endif //
