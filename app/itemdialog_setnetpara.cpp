#include "itemdialog_setnetpara.h"
#include "ui_itemdialog_setnetpara.h"
#include <QProcess>
#include <QKeyEvent>
#include <QMessageBox>
#include <qinputdialog.h>
#include <qlineedit.h>
#include <QSettings>
#include <QWidget>
#include <QBitmap>
#include <QPixmapCache>
#include "public/publicfun.h"
#include "global.h"
#include "widget/widgetmessage.h"

QStringList NetParainfo;
QStringList NetParaData;

ItemDialog_SetNetPara::ItemDialog_SetNetPara(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ItemDialog_SetNetPara)
{
    //PRINTF("ItemDialog_SetNetPara 构造");
    ui->setupUi(this);
    //设置标题栏隐藏
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    //设置窗口最大化
    this->showMaximized();
    //设置字号
    ft.setPointSize(50);
    ft1.setPointSize(32);
    //设置颜色
    pa.setColor(QPalette::WindowText,Qt::red);

    //设置缓冲区内只能放一张图片
    QPixmapCache::setCacheLimit(1);
    QPixmap pixmap;
    QPalette palette;

    //设置整个界面背景
    pixmap.load(QString("%1/background_pic.jpg").arg(PROJECT_DIR_IMG));
    palette=this->palette();
    palette.setBrush(QPalette::Background,QBrush(pixmap));
    this->setPalette(palette);

    //主题
    ui->label_title->setAlignment(Qt::AlignCenter);
    ui->label_title->setFont(ft);
    ui->label_title->setStyleSheet("background:transparent;color:white;font-size:51px;");
    ui->label_title->setText(QString::fromUtf8("网络设置"));

    // 设置返回按键图片
    ui->bt_back->setStyleSheet(QString("border-image:url(%1/back.png);")
                               .arg(PROJECT_DIR_IMG));

    ui->cb_dhcp->setStyleSheet(QString("QCheckBox::indicator {width: 64px; height: 64px;}\
                                       QCheckBox::indicator:checked {image: url(%1/check_press.png);}").arg(PROJECT_DIR_IMG));

    QString button_style=QString("QPushButton:hover{border-image:url(%1/bt.png);}\
                                QPushButton:pressed{border-image:url(%1/bt_press.png);color:black;}\
                                QPushButton{border-image:url(%1/bt.png);color:white;text-align:center;font-size:51px;}").arg(PROJECT_DIR_IMG);

    ui->bt_ok->setStyleSheet(button_style);
    ui->bt_ok->setFont(ft);
    ui->bt_ok->setText(QString::fromUtf8("确定"));

    NetParainfo << QString::fromUtf8("服务器IP")
               << QString::fromUtf8("服务器端口")
               << QString::fromUtf8("本机IP")
               << QString::fromUtf8("子网掩码")
               << QString::fromUtf8("默认网关")
               << QString::fromUtf8("DNS")
               << QString::fromUtf8("DHCP模式");
}

ItemDialog_SetNetPara::~ItemDialog_SetNetPara()
{
    delete ui;
}

//设置所有网络参数信息
QStringList& ItemDialog_SetNetPara::setNetworkInfo(QStringList Input_Para, bool isHidden, bool *ok )
{
    bool ok_ = FALSE;
    NetParaData.clear();
    //是否隐藏确定按钮
    ui->bt_back->setHidden(isHidden);
    //参数显示初始化
    LineEdit_ShowInit(Input_Para,0);

    ok_ = this->exec() == QDialog::Accepted;
    if ( ok )
    {
        *ok = ok_;
    }

    if ( ok_ )
    {
        //PRINTF("按了确定键");

    }
    else
    {
        //PRINTF("按了取消键");
    }

    return NetParaData;
}


//初始化LineEdit显示
void ItemDialog_SetNetPara::LineEdit_ShowInit(QStringList Input_Para, int iMode)
{
    Q_UNUSED(iMode)
    //IP规则
    QString pattern=QString::fromUtf8("^((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)$");
    QRegExp RegExp(pattern);
    //端口号规则
    QString pattern1=QString::fromUtf8("^(?!0)(?:[0-9]{1,5}|65535)$");//(0-65535)
    QRegExp RegExp1(pattern1);

    //服务器IP
    ui->label_1->setStyleSheet("background:transparent;color:white;font-size:30px;");
    ui->label_1->setText(NetParainfo.at(0));
    ui->label_1->setFont(ft1);
    ui->lineEdit_1->setValidator(new QRegExpValidator(RegExp, ui->lineEdit_1));
    ui->lineEdit_1->setText(Input_Para.at(0));
    ui->lineEdit_1->setFont(ft1);
    ui->lineEdit_1->show();
    ui->lineEdit_1->setFocus();

    //服务器端口
    ui->label_2->setStyleSheet("background:transparent;color:white;font-size:30px;");
    ui->label_2->setText(NetParainfo.at(1));
    ui->label_2->setFont(ft1);
    ui->lineEdit_2->setValidator(new QRegExpValidator(RegExp1, ui->lineEdit_2));
    ui->lineEdit_2->setText(Input_Para.at(1));
    ui->lineEdit_2->setFont(ft1);
    ui->lineEdit_2->show();

    //本机IP
    ui->label_3->setStyleSheet("background:transparent;color:white;font-size:30px;");
    ui->label_3->setText(NetParainfo.at(2));
    ui->label_3->setFont(ft1);
    ui->lineEdit_3->setValidator(new QRegExpValidator(RegExp, ui->lineEdit_3));
    ui->lineEdit_3->setText(Input_Para.at(2));
    ui->lineEdit_3->setFont(ft1);
    ui->lineEdit_3->show();

    //子网掩码
    ui->label_4->setStyleSheet("background:transparent;color:white;font-size:30px;");
    ui->label_4->setText(NetParainfo.at(3));
    ui->label_4->setFont(ft1);
    ui->lineEdit_4->setValidator(new QRegExpValidator(RegExp, ui->lineEdit_4));
    ui->lineEdit_4->setText(Input_Para.at(3));
    ui->lineEdit_4->setFont(ft1);
    ui->lineEdit_4->show();

    //默认网关
    ui->label_5->setStyleSheet("background:transparent;color:white;font-size:30px;");
    ui->label_5->setText(NetParainfo.at(4));
    ui->label_5->setFont(ft1);
    ui->lineEdit_5->setValidator(new QRegExpValidator(RegExp, ui->lineEdit_5));
    ui->lineEdit_5->setText(Input_Para.at(4));
    ui->lineEdit_5->setFont(ft1);
    ui->lineEdit_5->show();

    //DNS
    ui->label_6->setStyleSheet("background:transparent;color:white;font-size:30px;");
    ui->label_6->setText(NetParainfo.at(5));
    ui->label_6->setFont(ft1);
    ui->lineEdit_6->setValidator(new QRegExpValidator(RegExp, ui->lineEdit_6));
    ui->lineEdit_6->setText(Input_Para.at(5));
    ui->lineEdit_6->setFont(ft1);
    ui->lineEdit_6->show();

    //DHCP模式
    ui->label_dhcp->setStyleSheet("background:transparent;color:white;font-size:30px;");
    ui->label_dhcp->setText(NetParainfo.at(6));
    ui->label_dhcp->setFont(ft1);
    ui->cb_dhcp->setChecked((Input_Para.at(6)=="1")?TRUE:FALSE);


}

//判断IP是否合法
int ItemDialog_SetNetPara::CheckIPValid()
{
    QString StrTemp;

    //PRINTF("判断IP是否合法");
    NetParaData.clear();

    //服务器IP
    StrTemp=ui->lineEdit_1->text();
    NetParaData.append(StrTemp);
    if(Publicfun::NetParamCheck(StrTemp))
    {
        ui->lineEdit_1->setFocus();
        return 1;
    }

    //服务器端口
    StrTemp=ui->lineEdit_2->text();
    NetParaData.append(StrTemp);
    if(StrTemp.toInt()<1||StrTemp.toInt()>65535)
    {
        ui->lineEdit_2->setFocus();
        return 2;
    }

    //本机IP
    StrTemp=ui->lineEdit_3->text();
    NetParaData.append(StrTemp);
    if(Publicfun::NetParamCheck(StrTemp))
    {
        ui->lineEdit_3->setFocus();
        return 3;
    }

    //子网掩码
    StrTemp=ui->lineEdit_4->text();
    NetParaData.append(StrTemp);
    if(Publicfun::NetParamCheck(StrTemp))
    {
        ui->lineEdit_4->setFocus();
        return 4;
    }

    //默认网关
    StrTemp=ui->lineEdit_5->text();
    NetParaData.append(StrTemp);
    if(Publicfun::NetParamCheck(StrTemp))
    {
        ui->lineEdit_5->setFocus();
        return 5;
    }

    //DNS
    StrTemp=ui->lineEdit_6->text();
    NetParaData.append(StrTemp);
    if(Publicfun::NetParamCheck(StrTemp))
    {
        ui->lineEdit_6->setFocus();
        return 6;
    }

    //DHCP
    bool isDhcp = ui->cb_dhcp->isChecked();
    NetParaData.append((isDhcp == TRUE)?"1":"0");

    return 0;
}


//按了确定键
void ItemDialog_SetNetPara::on_bt_ok_clicked()
{
    int ret = CheckIPValid();
    if(ret != 0)
    {
        // 弹框提示
        WidgetMessage::GetInstance()->ShowMessageHide(tr("IP格式异常"), false, NULL, 1);
    }
    else
    {
        this->accept();
    }

}

//按了返回键
void ItemDialog_SetNetPara::on_bt_back_clicked()
{
    this->close();
}
