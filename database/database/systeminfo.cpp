#include "systeminfo.h"
#include <QVariant>
#include <QDebug>

SystemInfo::SystemInfo()
{
    _tableName = "systeminfo";
    _key.clear();
}

void SystemInfo::getSelect(QSqlQuery &sqlquery)
{
    QStringList line_valeu;
    line_valeu.append(sqlquery.value(0).toString());
    line_valeu.append(sqlquery.value(1).toString());

    retstr.append(line_valeu);
}

QList<QStringList> &SystemInfo::getSelectValue()
{
    return retstr;
}

void SystemInfo::setDelKey(QString &key)
{
    _del_keys.append(key);
}

void SystemInfo::setKeyValue(QString &k, QString &v)
{
    _key = k;
    _value = v;
}

QString &SystemInfo::del()
{
     _sqlstr.clear();

    if (_del_keys.length()==0) {
        qDebug() << "has no delete condition";
        return _sqlstr;
    }

    _sqlstr.append("delete from systeminfo where ");

    foreach (QString item, _del_keys) {
        _sqlstr.append(QString("key='%1'").arg(item));
    }

    return _sqlstr;
}

QString &SystemInfo::insert()
{
    _sqlstr.clear();

   if (_key.isEmpty()) {
       qDebug() << "key is empty \n";
       return _sqlstr;
   }

   if (_value.isEmpty()) {
       _value = "null";
   }

   _sqlstr.append("insert into systeminfo values ");
   _sqlstr.append(QString("(%1, %2)").arg(_key, _value));

   return _sqlstr;
}

