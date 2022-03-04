#ifndef SFLINEBOX_H
#define SFLINEBOX_H
#include "interui.h"
#include <QWidget>

namespace Ui {
class MessageLineBox;
}

class SFLineBox : public InterUi
{
public:
    SFLineBox();
    ~SFLineBox();
    void bindUi(QWidget* w);
    void updateCount(int num);

    Ui::MessageLineBox *ui;
};

#endif // SFLINEBOX_H
