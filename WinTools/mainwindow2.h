#ifndef MAINWINDOW2_H
#define MAINWINDOW2_H

#include <QMainWindow>
#include "servers/telnet/telnetsv.h"
#include "globalsignal.h"
#include <QTimer>

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
    // 监听telnet状态
    void SlotShowTelnetMsg(const QString& msg);
    void SlotTelnetLost();
    /** 用户操作 */
    //
    void on_dev_reboot_clicked();
    //
    void on_get_db_clicked();
    void on_get_bin_clicked();
    void on_get_logs_clicked();
    // 用户操作
    void on_up_app_clicked();
    void on_pc_ip_currentTextChanged(const QString &arg1);
    void on_dev_switch_clicked();
    // 列表命令，用户操作
    void on_do_cmd_clicked();
    void on_cmd_list_editTextChanged(const QString &arg1);
    void on_cmd_list_currentIndexChanged(int index);
    // 用户操作
    void on_next_ip_clicked();
    void on_pre_ip_clicked();

    void on_bt_clear_clicked();
    void on_dev_factory_clicked();
    void on_dev_init_clicked();
    void on_facelist_clicked();

    // 监听服务状态
    void SlotSftpSta(SFTP_STA sta);
    void SlotCftpEnd();
    // 监听ftp超时
    void SlotWaitFtpEnd();

private:
    static void Do_upapp(QObject *itent, const QString& filename);
    static void Do_copybin(QObject *itent, const QString& filename);
    static void Do_copyispconf(QObject *itent, const QString& filename);
    static void Do_kernelup(QObject *itent, const QString& filename);
    //
    void SelectFile(QObject *itent, void(*do_some)(QObject *itent, const QString&));
    //
    // 自增自减重新连接telnet
    void reConnectIp(bool ipIns);
    //
    Ui::MainWindow2 *ui;
    TelnetSV* _tel;
    //
    bool _lockip;
    //
    int dev_set;
    int plat_set;
    int plat_select;
    QString _pcIP;
    //
    int clist_set;
    // 如果需要等待文件ftp传输结束，这里登记一下信息
    char* _dbname;
    QTimer waitFtpEnd;
};

#endif // MAINWINDOW2_H
