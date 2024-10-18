#ifndef VIEWDB_H
#define VIEWDB_H

#include <QWidget>
#include <QSqlDatabase>
#include <QDialog>
#include <QSqlQueryModel>

namespace Ui {
class ViewDb;
}

class ViewDb : public QDialog
{
    Q_OBJECT

public:
    explicit ViewDb(QWidget *parent = nullptr, const QString& dbname="", int devtyp=0);
    ~ViewDb();

protected:
    void closeEvent(QCloseEvent *event);
    // devtype 设备类型，dev 设备，加了平台区别的
    void InitSql(int devtype, int dev);

private slots:
    void on_s_tb_currentIndexChanged(int index);

    void on_bt_check_clicked();

    void on_bt_export_clicked();

    void on_s_condition_currentIndexChanged(int index);

private:
    Ui::ViewDb *ui;

    // 实际选中的序号
    int stbs_index;
    int condition_index;
    // ui选中的序号
    int stbs_select;
    int condition_select;

    // db
    QSqlDatabase m_db;
    QSqlQueryModel* m_model;
};

#endif // VIEWDB_H
