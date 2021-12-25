#ifndef SFINPUTLINE_H
#define SFINPUTLINE_H
#include "interui.h"
namespace Ui {
class InputLine;
}
class SFInputLine : public InterUi
{
public:
    SFInputLine();
    ~SFInputLine();
    void bindUi(QWidget* w);
    void setLabelStyle(const QString& style);
    void setLabelText(const QString& lable);
    void setInputStyle(const QString& style);
    void setInputText(const QString& text);
    void returnInput();
    void bindInputRetval(QString* retval);

    Ui::InputLine* ui;
private:
    QString* _input;
};

#endif // SFINPUTLINE_H
