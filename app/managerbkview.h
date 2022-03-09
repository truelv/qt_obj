#ifndef MANAGERBKVIEW_H
#define MANAGERBKVIEW_H

#include <QWidget>
#include <QVBoxLayout>

namespace Ui {
class ManagerBkView;
}

class ManagerBkView : public QWidget
{
    Q_OBJECT

public:
    static ManagerBkView* getInstance();
    ~ManagerBkView();
    void addWidgetShow(QWidget* w);

private:
    Ui::ManagerBkView *ui;
    // 组合具体显示界面（实时）
    QWidget* _w;
    QVBoxLayout* _layout;

    explicit ManagerBkView(QWidget *parent = 0);
    static ManagerBkView* _intent;
};

// MANAGERBKVIEW_H
#endif
