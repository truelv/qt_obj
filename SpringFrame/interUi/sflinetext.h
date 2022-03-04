#ifndef SFLINETEXT_H
#define SFLINETEXT_H
#include "interui.h"
namespace Ui {
class MessageLineText;
}
class SFLineText : public InterUi
{
public:
    SFLineText();
    ~SFLineText();
    void bindUi(QWidget* w);

    Ui::MessageLineText* ui;
};

#endif // SFLINETEXT_H
