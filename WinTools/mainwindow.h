#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    // 显示日志
    void apandeLogs(const QString& text);

    static MainWindow* itent;

protected:
    void resizeEvent(QResizeEvent *event);
private slots:
    void on_splitter_splitterMoved(int pos, int index);
    void on_scanButton_clicked();
    void on_updateButton_clicked();
    void checkboxChange(int state);
    void on_logButton_clicked();
    void on_rebootButton_clicked();
    void on_upButton_clicked();

private:
    void updateScanButton();
    void updateTable();
    void clearTableData();
    static int handRsp(char* rsp, int len);
private:
    Ui::MainWindow *ui;
    QMessageBox msgbox;
};
#endif // MAINWINDOW_H
