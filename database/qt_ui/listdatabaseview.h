#ifndef LISTDATABASEVIEW_H
#define LISTDATABASEVIEW_H

#include <QWidget>
#include <testsqlite3.h>

namespace Ui {
class ListDatabaseView;
}

class ListDatabaseView : public QWidget
{
    Q_OBJECT

public:
    explicit ListDatabaseView(QWidget *parent = 0);
    ~ListDatabaseView();

private slots:
    void on_check_table_clicked();
    void slot_delete_item(bool);

    void on_pushButton_clicked();

private:
    Ui::ListDatabaseView *ui;
    TestSqlite3* _database;

    int insert_index;
};

#endif // LISTDATABASEVIEW_H
