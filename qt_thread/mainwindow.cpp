#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _thread2Work.moveToThread(&_thread2);
    connect(this, SIGNAL(sigStartThread2Work()), &_thread2Work, SLOT(doWork()));
    //connect(&_thread2, SIGNAL(finished()), &_thread2Work, SLOT(stop()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_start_type1_clicked()
{
    if (_thread1.isRunning()) {
        ui->start_type1->setText(tr("方式一启动线程"));
        _thread1.stop();
        return;
    }

    ui->start_type1->setText(tr("停止"));
    _thread1.start();
}

void MainWindow::on_start_type2_clicked()
{
    if (_thread2.isRunning()) {
        ui->start_type2->setText(tr("方式二启动线程"));
        _thread2Work.stop();
        _thread2.quit();
        return;
    }
    ui->start_type2->setText(tr("停止"));
    _thread2.start();
    emit sigStartThread2Work();
}
