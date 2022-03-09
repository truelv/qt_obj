#ifndef TITLEDIALOG2_H
#define TITLEDIALOG2_H

#include <QMainWindow>

namespace Ui {
class TitleDialog2;
}

class TitleDialog2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit TitleDialog2(QWidget *parent = 0);
    ~TitleDialog2();

private:
    Ui::TitleDialog2 *ui;
};

#endif // TITLEDIALOG2_H
