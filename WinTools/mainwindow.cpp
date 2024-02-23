#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "deviceInfo.h"
#include "device_prot.h"
#include "linkedlist/linkedlist.h"
#include <unistd.h>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <stdio.h>
#include <QCheckBox>
#include <QMessageBox>

typedef struct {
    LINK_NODE node;
    int index;
    DEVICE_INFO dinfo;
    char checked;
    char R1;
    char R2;
    char R3;
} DEVICE_INFO_NODE;
// 定义一个链表维护设备
static LINK_HEAD* hdevinfo = nullptr;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("多功能设备维护工具"));
    //表格充满布局
    ui->devinfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //
    ui->devinfo->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    updateScanButton();

    init_linkedlist(&hdevinfo);
}

MainWindow::~MainWindow()
{
    if (nullptr!=hdevinfo) {
        free_linkedlist(hdevinfo);
        hdevinfo = nullptr;
    }
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    updateScanButton();
}

void MainWindow::updateScanButton()
{
    // 扫描按键修改尺寸
    int width = ui->scanButton->width();
    if (width<=0)
        return ;
    QFont ft;
    ft.setPixelSize(static_cast<int>(width*0.2));
    //qDebug() << "width " << width;
    int height = static_cast<int>(width*0.4);

    ui->scanButton->setMinimumHeight(height);
    ui->scanButton->setMaximumHeight(height);
    ui->scanButton->setFont(ft);

    ui->updateButton->setMinimumHeight(height);
    ui->updateButton->setMaximumHeight(height);

    ui->logButton->setMinimumHeight(height);
    ui->logButton->setMaximumHeight(height);

    ui->shellButton->setMinimumHeight(height);
    ui->shellButton->setMaximumHeight(height);

    ui->rebootButton->setMinimumHeight(height);
    ui->rebootButton->setMaximumHeight(height);
#if 0
    width = ui->updateButton->width();
    ft.setPixelSize(static_cast<int>(width*0.2));
    ui->updateButton->setMinimumHeight(static_cast<int>(width*0.4));
    ui->updateButton->setFont(ft);

    ui->logButton->setMinimumHeight(height);
    ui->logButton->setFont(ft);

    ui->shellButton->setMinimumHeight(height);
    ui->shellButton->setFont(ft);
#endif
}

void MainWindow::updateTable()
{
    if (nullptr==hdevinfo)
        return ;
    DEVICE_INFO_NODE* pdinfo = nullptr;
    DEVICE_INFO* pinfo = nullptr;
    LINK_NODE* pnode = nullptr;

    ui->devinfo->setRowCount(hdevinfo->nodecount);
    FOREACH_LKLIST(hdevinfo, pnode) {
        pdinfo = (DEVICE_INFO_NODE*)pnode;
        pinfo = &pdinfo->dinfo;
        qDebug() << "index " << pdinfo->index;

        QCheckBox* checkbox = new QCheckBox;
        checkbox->setProperty("node", (int)pdinfo);
        connect(checkbox, SIGNAL(stateChanged(int)), this, SLOT(checkboxChange(int)));
        if (pdinfo->checked)
            checkbox->setChecked(true);
        ui->devinfo->setCellWidget(pdinfo->index, 0, checkbox);
        //ui->devinfo->item(pdinfo->index, 0)->seta;
        ui->devinfo->setItem(pdinfo->index, 1, new QTableWidgetItem(pinfo->sn));
        ui->devinfo->setItem(pdinfo->index, 2, new QTableWidgetItem(pinfo->ip));
    }

}

int MainWindow::handRsp(char *rsp, int len)
{
    qDebug() << "接收到消息 " << rsp << ", 长度" << len;
    // 拆解消息，格式化数据入链表
    DEVICE_INFO* dinfo = (DEVICE_INFO*)rsp;
    DEVICE_INFO_NODE* info = new DEVICE_INFO_NODE;
    memcpy(&info->dinfo, dinfo, sizeof(DEVICE_INFO));

    info->index = hdevinfo->nodecount;
    info->checked = 0;
    insert_tail(hdevinfo, &info->node);
    return 0;
}


void MainWindow::on_splitter_splitterMoved(int pos, int index)
{
    Q_UNUSED(pos)
    Q_UNUSED(index)
    updateScanButton();
}

void MainWindow::on_scanButton_clicked()
{
    // 扫描局域网内设备
    qDebug() << "点击扫描";
    CLEAR_LKLIST(hdevinfo, DEVICE_INFO_NODE, node);
    scanDevice(handRsp);
    // 扫描完成后，更新表
    updateTable();
}

void MainWindow::on_updateButton_clicked()
{
    QFileDialog fdialog(this);
    fdialog.exec();
    const QStringList& filenames = fdialog.selectedFiles();

    //qDebug() << filenames << " " << filenames.length();

    if (filenames.length()<1) {
        msgbox.setText(tr("没有选择文件"));
        msgbox.exec();
        return ;
    }

    if (hdevinfo->nodecount<=0) {
        msgbox.setText(tr("没有找到设备"));
        msgbox.exec();
        return ;
    }

    DEVICE_INFO_NODE* pdinfo = nullptr;
    LINK_NODE* pnode = nullptr;
    char flag = 0;
    FOREACH_LKLIST(hdevinfo, pnode) {
        pdinfo = (DEVICE_INFO_NODE*)pnode;
        if (0==pdinfo->checked)
            continue;
        flag = 1;
        updateDevice(filenames[0].toUtf8(), &pdinfo->dinfo);
        //
        usleep(30000);
    }

    if (0==flag) {
        msgbox.setText(tr("没有选中设备"));
        msgbox.exec();
    }
}

void MainWindow::checkboxChange(int state)
{
    QObject* ob = sender();
    int nodeaddr = ob->property("node").toInt();
    DEVICE_INFO_NODE* dinfo = (DEVICE_INFO_NODE*)nodeaddr;
    dinfo->checked = dinfo->checked?0:1;
    qDebug() << "选中";
}

void MainWindow::on_logButton_clicked()
{
    QFileDialog fdialog(this);
    fdialog.setFileMode(QFileDialog::Directory);
    fdialog.exec();
    const QStringList& filenames = fdialog.selectedFiles();
    qDebug() << filenames << " " << filenames.length();

    if (filenames.length()<1) {
        msgbox.setText(tr("没有选择文件夹"));
        msgbox.exec();
        return ;
    }

    if (hdevinfo->nodecount<=0) {
        msgbox.setText(tr("没有找到设备"));
        msgbox.exec();
        return ;
    }

    DEVICE_INFO_NODE* pdinfo = nullptr;
    LINK_NODE* pnode = nullptr;
    char flag = 0;
    FOREACH_LKLIST(hdevinfo, pnode) {
        pdinfo = (DEVICE_INFO_NODE*)pnode;
        if (0==pdinfo->checked)
            continue;
        flag = 1;
        getDevlog(filenames[0].toUtf8(), &pdinfo->dinfo);
        //
        usleep(30000);
    }

    if (0==flag) {
        msgbox.setText(tr("没有选中设备"));
        msgbox.exec();
    }
}

void MainWindow::on_rebootButton_clicked()
{
    if (hdevinfo->nodecount<=0) {
        msgbox.setText(tr("没有找到设备"));
        msgbox.exec();
        return ;
    }

    DEVICE_INFO_NODE* pdinfo = nullptr;
    LINK_NODE* pnode = nullptr;
    char flag = 0;
    FOREACH_LKLIST(hdevinfo, pnode) {
        pdinfo = (DEVICE_INFO_NODE*)pnode;
        if (0==pdinfo->checked)
            continue;
        flag = 1;
        devReboot(&pdinfo->dinfo);
        //
        usleep(30000);
    }

    if (0==flag) {
        msgbox.setText(tr("没有选中设备"));
        msgbox.exec();
    }
}
