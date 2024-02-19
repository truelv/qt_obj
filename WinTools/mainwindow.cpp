#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    updateScanButton();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    updateScanButton();
}

void MainWindow::updateScanButton()
{
    // 扫描按键修改尺寸
    int width = ui->scanButton->width();
    //qDebug() << "width " << width;
    ui->scanButton->setMinimumHeight(static_cast<int>(width*0.4));
    QFont ft;
    ft.setPixelSize(static_cast<int>(width*0.2));
    ui->scanButton->setFont(ft);
}


void MainWindow::on_splitter_splitterMoved(int pos, int index)
{
    updateScanButton();
}

void MainWindow::on_scanButton_clicked()
{
    // 扫描局域网内设备
}
