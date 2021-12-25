#ifndef SF485ERROR_H
#define SF485ERROR_H
#include "interui.h"

namespace Ui {
class SF485Error;
}

class SF485Error : public InterUi
{

public:
    SF485Error();
    ~SF485Error();
    void bindUi(QWidget* w);
    void setLabelStyle(const QString& style);
    void setTitleText(const QString& text);
    void setTitleStyle(const QString& style);
    void setContentText(const QString& text);
    void setContentStyle(const QString& style);

private:
    Ui::SF485Error *ui;
};

#endif // SF485ERROR_H
