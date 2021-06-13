#include "listdatabaseview.h"
#include "ui_listdatabaseview.h"
#include "systeminfo.h"
#include <QDebug>

ListDatabaseView::ListDatabaseView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListDatabaseView)
{
    ui->setupUi(this);

    _database = TestSqlite3::getIntent();

    insert_index = 0;
    ui->table_name->setText(tr("systeminfo"));
    on_check_table_clicked();
}

ListDatabaseView::~ListDatabaseView()
{
    delete _database;
    delete ui;

}

/** 查询 */
void ListDatabaseView::on_check_table_clicked()
{
#if 1
    SystemInfo list;
    QString tableName = ui->table_name->text();

    if (tableName.isEmpty()) {
        qDebug() << "table name is empty \n";
        return;
    }

    _database->find((LineItem*)&list, tableName);

    QList<QStringList> &liststr = list.getSelectValue();

    qDebug() << "qlist lenght "<< liststr.length();

    ui->table_view->setRowCount(liststr.length());
    foreach (QStringList item, liststr) {
        //qDebug() << "show item ";

        ui->table_view->setItem(insert_index, 0, new QTableWidgetItem(item.at(0)));
        ui->table_view->setItem(insert_index, 1, new QTableWidgetItem(item.at(1)));
        QPushButton* bt = new QPushButton("delete");
        bt->setProperty("id", insert_index);
        connect(bt, SIGNAL(clicked(bool)), this, SLOT(slot_delete_item(bool)));
        ui->table_view->setCellWidget(insert_index, 2, bt);

        insert_index++;
    }

    insert_index = 0;
#endif
}

/** 删除 */
void ListDatabaseView::slot_delete_item(bool)
{
#if 1
    SystemInfo list;
    int index = sender()->property("id").toInt();
    qDebug() << "index "<< index;
    QString key = ui->table_view->item(index, 0)->text();
    qDebug() << "key "<< key;
    list.setDelKey(key);
    _database->del((LineItem*)&list);

    on_check_table_clicked();
#endif
}

/** 插入 */
void ListDatabaseView::on_pushButton_clicked()
{
#if 1
    QString key = ui->insert_key->text();
    QString value = ui->insert_v->text();
    if (key.isEmpty()) {
        qDebug() << "primary key must valid \n";
        return ;
    }

    SystemInfo list;

    list.setKeyValue(key, value);
    _database->insert((LineItem*)&list);

    on_check_table_clicked();
#endif
}
