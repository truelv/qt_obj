#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "deviceInfo.h"
#include "device_prot.h"
#include "linkedlist/linkedlist.h"
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <stdio.h>
#include <QCheckBox>

typedef struct {
    LINK_NODE node;
    int index;
    DEVICE_INFO dinfo;
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

        ui->devinfo->setCellWidget(pdinfo->index, 0, new QCheckBox);
        //ui->devinfo->item(pdinfo->index, 0)->seta;
        ui->devinfo->setItem(pdinfo->index, 1, new QTableWidgetItem(pinfo->sn));
        ui->devinfo->setItem(pdinfo->index, 2, new QTableWidgetItem(pinfo->ip));
    }

}

void MainWindow::handRsp(char *rsp, int len)
{
    qDebug() << "接收到消息 " << rsp << ", 长度" << len;
    // 拆解消息，格式化数据入链表
    DEVICE_INFO_NODE* info = new DEVICE_INFO_NODE;
    int ret = paser_device_info(rsp, &info->dinfo);
    if (ret<0) {
        delete info;
        return ;
    }
    info->index = hdevinfo->nodecount;
    insert_tail(hdevinfo, &info->node);
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
    QStringList filenames;
    filenames = fdialog.selectedFiles();

    qDebug() << filenames << " " << filenames.length();

    if (filenames.length()<=1)
        return ;
    updateDevice(filenames[0].toUtf8());
}
