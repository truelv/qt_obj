#include "testsqlite3.h"
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#ifdef __cplusplus
extern "C" {
#endif
#include <stdlib.h>
#include <stdio.h>
#ifdef __cplusplus
}
#endif

TestSqlite3* TestSqlite3::_database = NULL;
TestSqlite3::TestSqlite3()
{
    db = QSqlDatabase::addDatabase("QSQLITE", "app");
    db.setDatabaseName("penson_info.db");
}

TestSqlite3 *TestSqlite3::getIntent()
{
    if (_database==NULL)
        _database = new TestSqlite3;
    return _database;
}

void TestSqlite3::insert(LineItem *item)
{
    if (!db.isOpen()) {
        if (!db.open()) {
            printf("open database failed \n");
            return ;
        }
    }

    QString& sqlstr = item->insert();
    QSqlQuery sqlquery(db);

    if (!sqlquery.prepare(sqlstr)) {
        printf("prepare sql failed \n");
        db.close();
    }

    if (!sqlquery.exec()) {
        printf("exec sql failed \n");
    }

    db.close();
}

void TestSqlite3::find(LineItem *item, QString &tableName)
{
    if (!db.isOpen()) {
        if (!db.open()) {
            printf("open database failed \n");
            return ;
        }
    }

    QString sqlstr = QString("select * from %1").arg(tableName);
    QSqlQuery sqlquery(db);

    if (!sqlquery.prepare(sqlstr)) {
        printf("prepare sql failed \n");
        db.close();
    }

    if (!sqlquery.exec()) {
        printf("exec sql failed \n");
    }

    while (sqlquery.next()) {
        QVariant var = sqlquery.value(0);
        qDebug()<< "find " << var.toString();

        var = sqlquery.value(1);
        qDebug()<< "find " << var.toString();

        item->getSelect(sqlquery);
    }


    db.close();
}

void TestSqlite3::update()
{
    if (!db.isOpen()) {
        if (!db.open()) {
            printf("open database failed \n");
            return ;
        }
    }

    QString sqlstr = "update systeminfo set value = 'xxxx' where key='database_name'";
    QSqlQuery sqlquery(db);

    if (!sqlquery.prepare(sqlstr)) {
        printf("prepare sql failed \n");
        db.close();
    }

    if (!sqlquery.exec()) {
        printf("exec sql failed \n");
    }

    while (sqlquery.next()) {
        QVariant var = sqlquery.value(0);
        qDebug()<< "find " << var.toString();

        var = sqlquery.value(1);
        qDebug()<< "find " << var.toString();
    }


    db.close();
}

void TestSqlite3::del(LineItem *item)
{
    if (!db.isOpen()) {
        if (!db.open()) {
            printf("open database failed \n");
            return ;
        }
    }

    QString& sqlstr = item->del();
    QSqlQuery sqlquery(db);

    if (!sqlquery.prepare(sqlstr)) {
        printf("prepare sql failed \n");
        db.close();
    }

    if (!sqlquery.exec()) {
        printf("exec sql failed \n");
    }

    db.close();
}

