
#include <QApplication>
#include "testsqlite3.h"
#include "listdatabaseview.h"
#include "testscreenpush.h"
#include "uicontroler.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //TestSqlite3::getIntent();

#if 0
    QWidget* list_database = new ListDatabaseView;
    list_database->show();
#endif

    UiControler* uiControler = UiControler::getInstance();
    uiControler->showHomeView();

    return a.exec();
}
