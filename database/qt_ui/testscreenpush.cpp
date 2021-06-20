#include "testscreenpush.h"
#include "ui_testscreenpush.h"
#include <QDebug>
#include <QMessageBox>

TestScreenPush::TestScreenPush(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestScreenPush)
{
    ui->setupUi(this);

    connect(&_timer, SIGNAL(timeout()), this, SLOT(slotPressScreen()));
    _uiControler = UiControler::getInstance();
}

TestScreenPush::~TestScreenPush()
{
    disconnect(&_timer, SIGNAL(timeout()), this, SLOT(slotPressScreen()));
    delete ui;
}

void TestScreenPush::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "mouse press";
    if (event->button()==Qt::LeftButton) {
        _timer.start(3000);
    }
}

void TestScreenPush::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() << "mouse move";
}

void TestScreenPush::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << "mouse release";
    if (_timer.isActive()) {
        _timer.stop();
    }
}

void TestScreenPush::slotPressScreen()
{
    qDebug() << "mouse PressScreen";
    _timer.stop();
#if 0
     _msgBox.setText("The document has been modified.");
     _msgBox.show();
#endif
     _uiControler->showLogin();
     this->deleteLater();
}
