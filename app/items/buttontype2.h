// 菜单列表使用的按键，横条形
#ifndef BUTTONTYPE2_H
#define BUTTONTYPE2_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class ButtonType2;
}

class ButtonType2 : public QPushButton
{
    Q_OBJECT

public:
    explicit ButtonType2(QWidget *parent = 0);
    ~ButtonType2();

    void setText(const QString& text);

protected:
    void mousePressEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);

private:
    Ui::ButtonType2 *ui;
};

#endif // BUTTONTYPE2_H
