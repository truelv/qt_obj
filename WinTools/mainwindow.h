#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *event);
private slots:
    void on_splitter_splitterMoved(int pos, int index);

    void on_scanButton_clicked();

private:
    void updateScanButton();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
