// 主设置菜单使用的按键，大长方形
#ifndef BUTTONTYPE1_H
#define BUTTONTYPE1_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class ButtonType1;
}

class ButtonType1 : public QPushButton
{
    Q_OBJECT

public:
    explicit ButtonType1(QWidget *parent = 0);
    ~ButtonType1();

    void setText(const QString& text);
    void setIcon(const QString& qss);

protected:
    void mousePressEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);

private slots:

private:
    Ui::ButtonType1 *ui;
};

#endif // BUTTONTYPE1_H
