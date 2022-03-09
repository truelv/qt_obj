#ifndef DIALOG_SHOWTEXTSETTING_H
#define DIALOG_SHOWTEXTSETTING_H

#include <QWidget>
#include "dialog_base.h"

namespace Ui {
class Dialog_ShowtextSetting;
}

class Dialog_ShowtextSetting : public Dialog_Base
{
    Q_OBJECT

public:
    explicit Dialog_ShowtextSetting(Dialog_Base* parent=0, const QString& title="");
    ~Dialog_ShowtextSetting();

protected slots:
    void slotFullname();
    void slotHidename();
    void slotCustomText();

private:
    Ui::Dialog_ShowtextSetting *ui;
};

#endif // DIALOG_SHOWTEXTSETTING_H
