#ifndef TESTSCREENPUSH_H
#define TESTSCREENPUSH_H

#include <QWidget>
#include <QMouseEvent>
#include <QTimer>
#include <QMessageBox>

#include "uicontroler.h"

namespace Ui {
class TestScreenPush;
}

class TestScreenPush : public QWidget
{
    Q_OBJECT

public:
    explicit TestScreenPush(QWidget *parent = 0);
    ~TestScreenPush();

protected:
    void mousePressEvent (QMouseEvent * event);
    void mouseMoveEvent (QMouseEvent * event);
    void mouseReleaseEvent (QMouseEvent * event);

private slots:
    void slotPressScreen();

private:
    Ui::TestScreenPush *ui;
    QTimer _timer;
    QMessageBox _msgBox;

    UiControler* _uiControler;
};

#endif // TESTSCREENPUSH_H
