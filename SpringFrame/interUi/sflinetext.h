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
    void setLineTextStyle(const QString& style);
    void setLineTextAlignment(Qt::Alignment a);
    void bindUi(QWidget* w);
    void setShowText(const QString& text);

    Ui::MessageLineText* ui;
};

#endif // SFLINETEXT_H
