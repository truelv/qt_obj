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
    void SlotTelnetLost();
    void on_up_app_clicked();
    void on_pc_ip_currentTextChanged(const QString &arg1);
    void on_dev_switch_clicked();
    // 列表命令
    void on_do_cmd_clicked();
    void on_cmd_list_editTextChanged(const QString &arg1);
    void on_cmd_list_currentIndexChanged(int index);

private:
    static void Do_upapp(QObject *itent, const QString& filename);
    static void Do_copybin(QObject *itent, const QString& filename);
    //
    void SelectFile(QObject *itent, void(*do_some)(QObject *itent, const QString&));
    //
    Ui::MainWindow2 *ui;
    TelnetSV* _tel;
    //
    bool _lockip;
    //
    int dev_set;
    int plat_set;
    QString _pcIP;
    //
    int clist_set;
};

#endif // MAINWINDOW2_H
