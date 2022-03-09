#include "dialog_modesetting.h"
#include "ui_dialog_modesetting.h"
#include "DB/dbyt.h"
#ifdef __cplusplus
extern "C" {
#endif
#include "signalsender_interface.h"
#include "globalData_interface.h"
#ifdef __cplusplus
}
#endif


Dialog_ModeSetting::Dialog_ModeSetting(Dialog_Base *parent, const QString &title) :
    Dialog_Base(parent, title),
    ui(new Ui::Dialog_ModeSetting)
{
    ui->setupUi(&_w);
    setContentWidget(&_w);
    _w.setStyleSheet("border: 0px solid black;");

    setCancelText(tr("退出"));
#if (DEVICE_USE_TYPE==READER)
    int mode = g_contrljoint.transferMode;
#else
    int mode = 0;
#endif
    ui->tabWidget->setCurrentIndex(mode);//89,119,176
    this->setStyleSheet("QLabel#rs485_devid, QLabel#daili, QLabel#kehu, QLabel#daili2, QLabel#kehu2 {"
                                 "font-size: 37px;"
                                 "color: rgb(255, 255, 255);"
                                 "margin-right:10px;"
                                " font-weight: bold;}"
                             "QTabBar::tab {font-size:35px;color:rgb(0,0,0);width:195px;height:60px;background-color: rgb(0, 0, 0,0);}"
                             "QTabBar::tab:selected {font-size:40px;color:rgb(255,255,255);}"
                             "#tabWidget {background-color: rgb(0, 0, 0, 0);}"
                             "#uart,#weigen,#rs485 {border-image: url(" PROJECT_DIR_IMG"/mode_setting_bk.png);}");
    ui->wg_agentid->setText(QString("%1").arg(g_qrinfo.agentID));
    ui->wg_iguestid->setText(QString("%1").arg(g_qrinfo.guestID));
    ui->uart_agentid->setText(QString("%1").arg(g_qrinfo.agentID));
    ui->uart_iguestid->setText(QString("%1").arg(g_qrinfo.guestID));
#if (DEVICE_USE_TYPE==READER)
    ui->device_id->setText(QString("%1").arg(g_contrljoint.terminalNum));
#endif

    this->showFullScreen();
}

Dialog_ModeSetting::~Dialog_ModeSetting()
{
    delete ui;
}

void Dialog_ModeSetting::on_bt_confirm_clicked()
{
#if (DEVICE_USE_TYPE==READER)
    int index = ui->tabWidget->currentIndex();
    // 通信模式保存，保存相应的配置
    switch (index)
    {
    // 韦根
    case 0:
    {
        g_contrljoint.transferMode = SENDMODE_WG;
        g_qrinfo.agentID = ui->wg_agentid->text().toInt();
        g_qrinfo.guestID = ui->wg_iguestid->text().toInt();
        db_set_localinfo2("transferMode",g_LoaclInfo.transferMode);
        db_set_localinfo2("agentID",g_qrinfo.agentID);
        db_set_localinfo2("guestID",g_qrinfo.guestID);
        rs485_svc_stop();
        sendSignalRs485Online(1);
        break;
    }
    // 485
    case 1:
        g_LoaclInfo.transferMode = SENDMODE_485;
        g_LoaclInfo.terminalNum = ui->device_id->text().toInt();
        db_set_localinfo2("transferMode",g_LoaclInfo.transferMode);
        db_set_localinfo2("terminalNum",g_LoaclInfo.terminalNum);
        sendSignalRs485Online(0);
        g_CommInfo.cOnline = 0;
        rs485_svc_start();
        break;
    // uart
    case 2:
        g_LoaclInfo.transferMode = SENDMODE_UART;
        g_qrinfo.agentID = ui->wg_agentid->text().toInt();
        g_qrinfo.guestID = ui->wg_iguestid->text().toInt();
        db_set_localinfo2("transferMode",g_LoaclInfo.transferMode);
        db_set_localinfo2("agentID",g_qrinfo.agentID);
        db_set_localinfo2("guestID",g_qrinfo.guestID);
        rs485_svc_stop();
        sendSignalRs485Online(1);
        break;
    default:
        break;
    }
    Dialog_Base::on_bt_confirm_clicked();
#endif
}
