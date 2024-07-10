#include "mainwindow2.h"
#include "ui_mainwindow2.h"
#include "servers/telnet/telnetsv.h"

typedef struct {
    int num;
    char* name;
    char* dir;
} PLAT_TYPE;

typedef struct {
    int num;
    char* name;
    char* rootdir;
    char* type;
} DEV_TYPE;
#define CUM_EOF -1

static DEV_TYPE dev[] = {
    {1, "YT328", "/data", "dctr"},
    {2, "YT327L", "/data", "pdctr"},
    {3, "YT216", "/home", "spos"},
    {CUM_EOF, 0, 0},
};

static PLAT_TYPE plat[] = {
    {1, "易通", "zyep"},
    {2, "40", "zytk"},
    {3, "易通云", "zyetc"},
    {4, "出入", "zyacs"},
    {CUM_EOF, 0, 0},
};

MainWindow2::MainWindow2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow2),
    _tel(nullptr),
    _lockip(false)
{
    ui->setupUi(this);
    ShowUILock(false);

    ui->dev_ip->setText("172.16.70.185");

    for (int i=0;;i++)
    {
        if (CUM_EOF==dev[i].num)
            break;
        ui->dev_type->addItem(dev[i].name);
    }

    for (int i=0;;i++)
    {
        if (CUM_EOF==plat[i].num)
            break;
        ui->plat_type->addItem(plat[i].name);
    }


    ui->splitter->setStretchFactor(0,3);
    ui->splitter->setStretchFactor(1,7);
    dev_set = 0;
    plat_set = 0;

    setWindowTitle("一款比较好用的维护工具，点赞打赏哦");
}

MainWindow2::~MainWindow2()
{
    delete ui;
}

void MainWindow2::ShowUILock(bool lock)
{
    ui->dev_ip->setEnabled(!lock);
    ui->dev_type->setEnabled(!lock);
    ui->plat_type->setEnabled(!lock);

    const QObjectList& clist = ui->groupBox->children();
    foreach(QObject* obj, clist)
    {
        if (!obj->inherits("QPushButton"))
            continue ;
        qobject_cast<QWidget*>(obj)->setEnabled(lock);
    }

    const QObjectList& clist2 = ui->groupBox_3->children();
    foreach(QObject* obj, clist2)
    {
        if (!obj->inherits("QPushButton") && !obj->inherits("QLineEdit"))
            continue ;
        qobject_cast<QWidget*>(obj)->setEnabled(lock);
    }
}

void MainWindow2::on_get_logs_clicked()
{
    // cd /data/zyep_pdctr;tar zcvf log.tar.gz log;ftpput -uxxx -pxxx 172.16.70.13 log.tar.gz;rm log.tar.gz
    QString cmd;
    cmd.append("cd ").append(dev[dev_set].rootdir).append("/");
    cmd.append(plat[plat_set].dir).append("_").append(dev[dev_set].type);
    cmd.append("&&tar zcvf log.tar.gz log&&");
    cmd.append("ftpput -uxxx -pxxx ").append("172.16.70.13").append(" log.tar.gz&&");
    cmd.append("rm log.tar.gz");

    _tel->ExeCommond(cmd);
}

void MainWindow2::SlotShowTelnetMsg(const QString &msg)
{
    ui->show_msg->append(msg);
}

void MainWindow2::on_lock_info_clicked()
{
    ShowUILock(!_lockip);
    if (!_lockip)
    {
        qDebug() << "new telnet";
        _tel = new TelnetSV(ui->dev_ip->text());
        _lockip = true;
        connect(_tel, &TelnetSV::RelyMsg, this, &MainWindow2::SlotShowTelnetMsg);
        ui->lock_info->setText("解锁");
        return ;
    }

    qDebug() << "del telnet";
    disconnect(_tel, &TelnetSV::RelyMsg, this, &MainWindow2::SlotShowTelnetMsg);
    delete _tel;
    ui->lock_info->setText("锁定");
    _lockip = false;
}

void MainWindow2::on_dev_type_currentIndexChanged(int index)
{
    qDebug() << "dev " << dev[index].name;
    dev_set = index;
}

void MainWindow2::on_plat_type_currentIndexChanged(int index)
{
    qDebug() << "plat " << plat[index].name;
    plat_set = index;
}

void MainWindow2::on_dev_reboot_clicked()
{
    _tel->ExeCommond("reboot");
}

void MainWindow2::on_get_db_clicked()
{
    // cd /data/zyep_pdctr;tar zcvf data.tar.gz data;ftpput -uxxx -pxxx 172.16.70.13 data.tar.gz;rm data.tar.gz
    QString cmd;
    cmd.append("cd ").append(dev[dev_set].rootdir).append("/");
    cmd.append(plat[plat_set].dir).append("_").append(dev[dev_set].type);
    cmd.append("&&tar zcvf data.tar.gz data&&");
    cmd.append("ftpput -uxxx -pxxx ").append("172.16.70.13").append(" data.tar.gz&&");
    cmd.append("rm data.tar.gz");
    _tel->ExeCommond(cmd);
}

void MainWindow2::on_get_bin_clicked()
{
    // cd /data/zyep_pdctr;tar zcvf app.tar.gz app;ftpput -uxxx -pxxx 172.16.70.13 app.tar.gz;rm app.tar.gz
    QString cmd;
    cmd.append("cd ").append(dev[dev_set].rootdir).append("/");
    cmd.append(plat[plat_set].dir).append("_").append(dev[dev_set].type);
    cmd.append("&&tar zcvf app.tar.gz app&&");
    cmd.append("ftpput -uxxx -pxxx ").append("172.16.70.13").append(" app.tar.gz&&");
    cmd.append("rm app.tar.gz");
    _tel->ExeCommond(cmd);
}

void MainWindow2::on_up_app_clicked()
{

}