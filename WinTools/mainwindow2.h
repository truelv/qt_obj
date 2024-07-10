#ifndef MAINWINDOW2_H
#define MAINWINDOW2_H

#include <QMainWindow>
#include "servers/telnet/telnetsv.h"

namespace Ui {
class MainWindow2;
}

class MainWindow2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow2(QWidget *parent = nullptr);
    ~MainWindow2();

    void ShowUILock(bool lock);

private slots:
    void on_lock_info_clicked();
    void on_dev_type_currentIndexChanged(int index);
    void on_plat_type_currentIndexChanged(int index);
    //
    void on_dev_reboot_clicked();
    //
    void on_get_db_clicked();
    void on_get_bin_clicked();
    void on_get_logs_clicked();
    //
    void SlotShowTelnetMsg(const QString& msg);

private:
    Ui::MainWindow2 *ui;
    TelnetSV* _tel;
    //
    bool _lockip;
    //
    int dev_set;
    int plat_set;
};

#endif // MAINWINDOW2_H
