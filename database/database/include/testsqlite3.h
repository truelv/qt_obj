#ifndef TESTSQLITE3_H
#define TESTSQLITE3_H
#include <QSqlDatabase>
#include "lineitem.h"

class TestSqlite3
{
public:

    static TestSqlite3* getIntent();

    void insert(LineItem *item);
    void find(LineItem *item, QString &tableName);
    void update();
    void del(LineItem *item);
    bool hasTable(QString& tableName);

private:
    QSqlDatabase db;

    static TestSqlite3* _database;
    TestSqlite3();

};

#endif // TESTSQLITE3_H
