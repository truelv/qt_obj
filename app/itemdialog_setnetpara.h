#ifndef ITEMDIALOG_SETNETPARA_H
#define ITEMDIALOG_SETNETPARA_H

#include <QDialog>

namespace Ui {
class ItemDialog_SetNetPara;
}

class ItemDialog_SetNetPara : public QDialog
{
    Q_OBJECT

public:
    explicit ItemDialog_SetNetPara(QWidget *parent = 0);
    ~ItemDialog_SetNetPara();

    //设置所有网络参数信息
    QStringList& setNetworkInfo(QStringList Input_Para, bool isHidden, bool *ok );

    //初始化LineEdit显示
    void LineEdit_ShowInit(QStringList Input_Para, int iMode);

    //判断IP是否合法
    int CheckIPValid();

private slots:
    void on_bt_ok_clicked();

    void on_bt_back_clicked();

private:
    Ui::ItemDialog_SetNetPara *ui;

    QFont ft1,ft;
    QPalette pa;
};

#endif // ITEMDIALOG_SETNETPARA_H
