#include "mainwindow2.h"
#include "ui_mainwindow2.h"
#include "servers/telnet/telnetsv.h"
#include "ui_defind.h"
#include <QNetworkInterface>
#include <QFileDialog>
#include <QMessageBox>
#include "devselect.h"

DEV_TYPE dev[] = {
    // index,设备名字，根目录，设备类型后缀
    {1, "328一体机", "/data", "dctr"},
    {2, "327L一体机", "/data", "pdctr"},
    {3, "216", "/home", "spos"},
    {4, "328读卡器", "/data", "reader"},
    {5, "312控制器", "/home", "smartdc"},
    {6, "312梯控", "/home", "tk"},
    {CUM_EOF, 0, 0, 0},
};

PLAT_TYPE plat[] = {
    // index，平台名字，平台类型前缀
    {1, "易通", "zyep"},
    {2, "易通（http）", "zyeph"},
    {3, "40", "zytk"},
    {4, "易通云", "zyetc"},
    {5, "易通云（http）", "zyetch"},
    {6, "出入", "zyacs"},
    {CUM_EOF, 0, 0},
};

static CMD_LIST clist[] = {
    // 序号，名称，命令标记
    {1, "替换bin文件", LT_REPLACE_BIN},
    {2, "修改平台版本号", LT_NONE},
    {3, "修改数据库字段", LT_NONE},
    {4, "查看序列号（SN）", LT_NONE},
    {5, "查看网络IP", LT_VIEW_IP},
    {6, "查看网络网关", LT_VIEW_ROUTE},
    {7, "查看网络DNS", LT_VIEW_DNS},
    {8, "替换ISP配置文件", LT_REPLACE_ISPCONF},
    {9, "升级内核", LT_KERNEL_UP},
    {10, "查看内核版本", LT_KERNEL_VER},
    {CUM_EOF, 0},
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

    for (int i=0;;i++)
    {
        if (CUM_EOF==clist[i].num)
            break;
        ui->cmd_list->addItem(clist[i].name);
    }


    ui->splitter->setStretchFactor(0,3);
    ui->splitter->setStretchFactor(1,7);
    dev_set = 0;
    plat_set = 0;
    clist_set = 0;

    setWindowTitle("一款比较好用的维护工具，点赞打赏哦");
    const QList<QNetworkInterface>& inface = QNetworkInterface::allInterfaces();
    foreach(const QNetworkInterface& face, inface)
    {
#if 0
        if (face.type() != QNetworkInterface::Ethernet)
            continue ;
#endif

        if (face.humanReadableName().contains("VMware"))
            continue;

        if (face.humanReadableName().contains("VirtualBox"))
            continue;

        if (!face.flags().testFlag(QNetworkInterface::IsUp)
                || face.flags().testFlag(QNetworkInterface::IsLoopBack))
            continue;

        qDebug() << face.humanReadableName();
        const QList<QNetworkAddressEntry>& hostip = face.addressEntries();
        foreach(const QNetworkAddressEntry& addr, hostip)
        {
            if (addr.ip().protocol() != QAbstractSocket::IPv4Protocol)
                continue;
            qDebug() << addr.ip().toString();
            ui->pc_ip->addItem(addr.ip().toString());
        }

        _pcIP = ui->pc_ip->currentText();
        qDebug() << "pc ip " <<_pcIP;
    }
    //const QNetworkAddressEntry& addr = inface.addressEntries().at(0);

     //qDebug() << addr.ip();
    ui->stat_msg->setStyleSheet("color:red;font-size:23px;");
    //ui->stat_msg->setText(QString::fromUtf8("显示状态"));
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
    ui->pc_ip->setEnabled(!lock);
    ui->next_ip->setEnabled(!lock);
    ui->pre_ip->setEnabled(!lock);

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

    ui->cmd_list->setEnabled(lock);
}

void MainWindow2::on_get_logs_clicked()
{
    // cd /data/zyep_pdctr;tar zcvf log.tar.gz log;ftpput -uxxx -pxxx 172.16.70.13 log.tar.gz;rm log.tar.gz
    QString cmd;
    cmd.append("cd ").append(dev[dev_set].rootdir).append("/");
    cmd.append(plat[plat_set].dir).append("_").append(dev[dev_set].type);
    cmd.append("&&tar zcvf log.tar.gz log&&");
    cmd.append("ftpput -uxxx -pxxx ").append(_pcIP).append(" log.tar.gz&&");
    cmd.append("rm log.tar.gz");

    _tel->ExeCommond(cmd);
}

void MainWindow2::SlotShowTelnetMsg(const QString &msg)
{
    ui->show_msg->append(msg);
    ui->stat_msg->clear();
}

void MainWindow2::SlotTelnetLost()
{
    ShowUILock(false);
#if 0
    if (!_lockip)
    {
        qDebug() << "new telnet";
        _tel = new TelnetSV(ui->dev_ip->text());
        _lockip = true;
        connect(_tel, &TelnetSV::RelyMsg, this, &MainWindow2::SlotShowTelnetMsg);
        connect(_tel, &TelnetSV::Logout, this, &MainWindow2::SlotTelnetLost);
        ui->lock_info->setText("解锁");
        return ;
    }
#endif

    qDebug() << "del telnet";
    if (nullptr!=_tel)
    {
        disconnect(_tel, &TelnetSV::RelyMsg, this, &MainWindow2::SlotShowTelnetMsg);
        disconnect(_tel, &TelnetSV::Logout, this, &MainWindow2::SlotTelnetLost);
        _tel->deleteLater();
        //delete _tel;
        _tel = nullptr;
    }
    ui->lock_info->setText("锁定");
    _lockip = false;

    ui->stat_msg->setText(QString::fromUtf8("telnet连接失败！！！"));
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
        connect(_tel, &TelnetSV::Logout, this, &MainWindow2::SlotTelnetLost);
        ui->lock_info->setText("解锁");
        return ;
    }

    qDebug() << "del telnet";
    disconnect(_tel, &TelnetSV::RelyMsg, this, &MainWindow2::SlotShowTelnetMsg);
    disconnect(_tel, &TelnetSV::Logout, this, &MainWindow2::SlotTelnetLost);
    delete _tel;
    _tel = nullptr;
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
    cmd.append("ftpput -uxxx -pxxx ").append(_pcIP).append(" data.tar.gz&&");
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
    cmd.append("ftpput -uxxx -pxxx ").append(_pcIP).append(" app.tar.gz&&");
    cmd.append("rm app.tar.gz");
    _tel->ExeCommond(cmd);
}

void MainWindow2::on_up_app_clicked()
{
    SelectFile(this, MainWindow2::Do_upapp);
}

void MainWindow2::on_pc_ip_currentTextChanged(const QString &arg1)
{
    _pcIP = arg1;
    qDebug() << "pc switch ip " << _pcIP;
}

/*
327L 易通云
[DeviceProType]
DeviceName=YT328/YT327L/YT312
Tpye=zyetc_pdctr
*/
void MainWindow2::on_dev_switch_clicked()
{
    DevSelect* devs = new DevSelect(this, &plat_set, &dev_set);
    int ret = devs->exec();
    if (QDialog::Rejected==ret)
        return;

    // cd /data/etc&&echo "[DeviceProType]\nDeviceName=YT328\nTpye=zyetc_pdctr\n" > DeviceProType.ini
    QString cmd;
    cmd.append("cd ").append(dev[dev_set].rootdir).append("/etc&&");
    cmd.append("echo [DeviceProType]>DeviceProType.ini&&");
    cmd.append("echo DeviceName=").append("YT328").append(">>DeviceProType.ini&&");
    cmd.append("echo Tpye=").append(plat[plat_set].dir).append("_").append(dev[dev_set].type).append(">>DeviceProType.ini");
    _tel->ExeCommond(cmd);
}

void MainWindow2::on_do_cmd_clicked()
{
    QString cmd;
    switch (clist[clist_set].type) {
    case LT_REPLACE_BIN:
        SelectFile(this, MainWindow2::Do_copybin);
        return ;
        break;
    case LT_VIEW_ROUTE:
        cmd.append("route -n");
        break;
    case LT_VIEW_IP:
        cmd.append("ifconfig");
        break;
    case LT_VIEW_DNS:
        cmd.append("cat /etc/resolv.conf");
        break;
    case LT_REPLACE_ISPCONF:
        SelectFile(this, MainWindow2::Do_copyispconf);
        return ;
        break;
    case LT_KERNEL_UP:
        SelectFile(this, MainWindow2::Do_kernelup);
        return ;
        break;
    case LT_KERNEL_VER:
        cmd.append("uname -a");
        break;
    case LT_NONE:
    //default:
        return ;
    }

    _tel->ExeCommond(cmd);
}

void MainWindow2::on_cmd_list_editTextChanged(const QString &arg1)
{
    qDebug() << "change text " << arg1;
}

void MainWindow2::on_cmd_list_currentIndexChanged(int index)
{
    clist_set = index;
}

void MainWindow2::Do_upapp(QObject* itent, const QString &filename)
{
    MainWindow2* vv = qobject_cast<MainWindow2*>(itent);
    // cd /data/tmp;ftpget -uxxx -pxxx 172.16.70.13 %name%;tar zcvf app.tar.gz app;rm %name%
    QString cmd;
    cmd.append("cd ").append(dev[vv->dev_set].rootdir).append("&&");
    cmd.append("ftpget -uxxx -pxxx ").append(vv->_pcIP).append(" "+filename);
    cmd.append("&&tar xvf ").append(filename);
    cmd.append("&&sync;rm ").append(filename);
    vv->_tel->ExeCommond(cmd);
}

void MainWindow2::Do_copybin(QObject *itent, const QString &filename)
{
    MainWindow2* vv = qobject_cast<MainWindow2*>(itent);
    // cd /data/tmp;ftpget -uxxx -pxxx 172.16.70.13 %name%;tar zcvf app.tar.gz app;rm %name%
    QString cmd;
    cmd.append("cd ").append(dev[vv->dev_set].rootdir).append("/tmp&&");
    cmd.append("ftpget -uxxx -pxxx ").append(vv->_pcIP).append(" "+filename);
    cmd.append("&&cp ").append(filename).append(" ");
    cmd.append(dev[vv->dev_set].rootdir).append("/").append(plat[vv->plat_set].dir).append("_").append(dev[vv->dev_set].type).append("/app");
    cmd.append("&&sync;rm ").append(filename);
    vv->_tel->ExeCommond(cmd);
}

void MainWindow2::Do_copyispconf(QObject *itent, const QString &filename)
{
    // 输入文件夹
    MainWindow2* vv = qobject_cast<MainWindow2*>(itent);
    // cd /data/tmp;ftpget -uxxx -pxxx 172.16.70.13 %name%;tar zcvf app.tar.gz app;rm %name%
    QString cmd;
    cmd.append("cd /root").append("&&");
    cmd.append("ftpget -uxxx -pxxx ").append(vv->_pcIP).append(" "+filename);
    cmd.append("&&cp ").append(filename).append(" ").append("/etc/isp/ar0230_dvp_1920_1080_30.json");
    cmd.append("&&sync;rm ").append(filename);
    vv->_tel->ExeCommond(cmd);
}

void MainWindow2::Do_kernelup(QObject *itent, const QString &filename)
{
    MainWindow2* vv = qobject_cast<MainWindow2*>(itent);
    // dd if=/dev/zero of=/dev/mmcblk0p2 bs=1M count=5 conv=fsync;dd if=kernel.img of=/dev/mmcblk0p2 conv=fsync
    QString cmd;
    cmd.append("cd /tmp").append("&&");
    cmd.append("ftpget -uxxx -pxxx ").append(vv->_pcIP).append(" "+filename);
    cmd.append("&&dd if=/dev/zero of=/dev/mmcblk0p2 bs=1M count=5 conv=fsync;dd if=").append(filename).append("  of=/dev/mmcblk0p2 conv=fsync");
    cmd.append("&&sync;rm ").append(filename);
    vv->_tel->ExeCommond(cmd);
}

// 选择的文件，copy到file目录
void MainWindow2::SelectFile(QObject *itent, void (*do_some)(QObject *itent, const QString &))
{
    QFileDialog fdialog(this);
    int ret = fdialog.exec();
    if (QDialog::Rejected==ret)
        return ;

    const QStringList& filenames = fdialog.selectedFiles();
    if (filenames.length()<1)
        return ;

    const QString& filepath = filenames[0];
    qDebug() << "select file full path " << filepath;
    QFile sfile(filepath);
    QFileInfo sfinfo(sfile);
    qDebug() << "file name " << sfinfo.fileName();

    //
    const QString& destfile = QCoreApplication::applicationDirPath()+"\\file\\"+sfinfo.fileName();
    if (QFile::exists(destfile))
        QFile::remove(destfile);

    if (!sfile.copy(destfile))
    {
        qDebug() << "copy file faile";
    }

    // 再次确认文件，确定升级
    QMessageBox msgbox(this);
    msgbox.setText("确认下发文件 "+sfinfo.fileName()+" 升级吗？？");
    ret = msgbox.exec();
    if (QDialog::Rejected==ret)
        return ;

#if 1
    if (nullptr!=do_some)
        do_some(itent, sfinfo.fileName());
#endif
    // 删除文件
    if (QFile::exists(destfile))
    {
        qDebug() << "file " << destfile << " exist";
        //QFile::remove(QCoreApplication::applicationDirPath()+"\\file\\"+sfinfo.fileName());
    }

}

// ipIns 是否自增
void MainWindow2::reConnectIp(bool ipIns)
{
    // 处理ip地址
    unsigned int ip;
    const QStringList& ipstr = ui->dev_ip->text().split(".");

    if (4!=ipstr.count())
    {
        qDebug() << "ip is empty";
        return ;
    }

    unsigned char* pc = (unsigned char*)(&ip);
    pc[0] = ipstr[3].toUInt(); // 185
    pc[1] = ipstr[2].toUInt(); // 70
    pc[2] = ipstr[1].toUInt(); // 16
    pc[3] = ipstr[0].toUInt(); // 172

    printf("%d %d %d %d\n", pc[0],pc[1],pc[2],pc[3]);

    if (ipIns)
        ip++;
    else {
        ip--;
    }

    char newip[16] = {0};
    snprintf(newip, sizeof(newip), "%d.%d.%d.%d", pc[3],pc[2],pc[1],pc[0]);
    printf("%d %d %d %d\n", pc[0],pc[1],pc[2],pc[3]);

    // 修改ui显示
    ui->dev_ip->setText(newip);
}

void MainWindow2::on_next_ip_clicked()
{
    reConnectIp(true);
}

void MainWindow2::on_pre_ip_clicked()
{
    reConnectIp(false);
}
