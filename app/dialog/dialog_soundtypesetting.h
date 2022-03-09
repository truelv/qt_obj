#ifndef DIALOG_SOUNDTYPESETTING_H
#define DIALOG_SOUNDTYPESETTING_H

#include <QWidget>
#include "dialog_base.h"

namespace Ui {
class Dialog_ShowtextSetting;
}

class Dialog_SoundtypeSetting : public Dialog_Base
{
    Q_OBJECT

public:
    explicit Dialog_SoundtypeSetting(Dialog_Base* parent=0, const QString& title="");
    ~Dialog_SoundtypeSetting();

protected slots:
    void slotFullname();
    void slotHidename();
    void slotCustomText();

private:
    Ui::Dialog_ShowtextSetting *ui;
};

#endif // DIALOG_SOUNDTYPESETTING_H
