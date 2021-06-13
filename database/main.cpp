
#include <QApplication>
#include "testsqlite3.h"
#include "listdatabaseview.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //TestSqlite3::getIntent();

    QWidget* list_database = new ListDatabaseView;
    list_database->show();

    return a.exec();
}
