// wifi的列表按键
#ifndef BUTTONTYPE3_H
#define BUTTONTYPE3_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class ButtonType3;
}

class ButtonType3 : public QWidget
{
    Q_OBJECT

public:
    explicit ButtonType3(QWidget *parent = 0);
    ~ButtonType3();
    void setSSIDName(const QString& name);
    void setSignalIcon(const QString& qss);
    void setConnected(const QString& sta);

private:
    Ui::ButtonType3 *ui;
};

#endif // BUTTONTYPE3_H
