#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "testthreadtype1.h"
#include "testthreadtype2.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void sigStartThread2Work();

private slots:
    void on_start_type1_clicked();

    void on_start_type2_clicked();

private:
    Ui::MainWindow *ui;
    TestThreadType1 _thread1;
    TestThreadType2 _thread2Work;
    QThread _thread2;
};

#endif // MAINWINDOW_H
