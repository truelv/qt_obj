#ifndef ETHSETTING_H
#define ETHSETTING_H
#include "base/ifacechildopt.h"
#include <QWidget>

namespace Ui {
class EthSetting;
}

class EthSetting : public QWidget, public IfaceChildOpt
{
    Q_OBJECT

public:
    explicit EthSetting(QWidget *parent = 0);
    ~EthSetting();
    int GetInput(QVariantList& retval);
    int SetInput(QVariantList& retval);

private:
    Ui::EthSetting *ui;
};

#endif // ETHSETTING_H
