#ifndef DIALOG_RFIDSIGNALSETTING_H
#define DIALOG_RFIDSIGNALSETTING_H

#include <QWidget>
#include "dialog_base.h"

namespace Ui {
class Dialog_RFIDSignalSetting;
}

class Dialog_RFIDSignalSetting : public Dialog_Base
{
    Q_OBJECT

public:
    explicit Dialog_RFIDSignalSetting(Dialog_Base* parent=0, const QString& title="");
    ~Dialog_RFIDSignalSetting();

protected slots:
    void slotSignalNormal();
    void slotSignalEnhanced();
    void slotSignalStrongest();

protected:
    void saveSignalType(char type);

private:
    Ui::Dialog_RFIDSignalSetting *ui;
    char _sigType;

};

#endif // DIALOG_RFIDSIGNALSETTING_H
