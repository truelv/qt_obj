#ifndef LINEITEM_H
#define LINEITEM_H
#include <QSqlQuery>
#include <QStringList>

class LineItem
{
public:
    LineItem();

    virtual void getSelect(QSqlQuery& sqlquery) = 0;
    virtual QList<QStringList>& getSelectValue() = 0;
    virtual QString& del() = 0;
    virtual QString& insert() = 0;
};

#endif // LINEITEM_H
