#ifndef SYSTEMINFO_H
#define SYSTEMINFO_H
#include <QString>
#include <QStringList>
#include "lineitem.h"

class SystemInfo : LineItem
{
public:
    SystemInfo();
    void getSelect(QSqlQuery& sqlquery);
    QList<QStringList>& getSelectValue();

    void setDelKey(QString& key);
    void setKeyValue(QString& k, QString& v);

    QString& del();
    QString& insert();


private:

    QList<QStringList> retstr;
    QStringList _del_keys;
    QString _sqlstr;
    QString _tableName;
    QString _key;
    QString _value;
};

#endif // SYSTEMINFO_H
