#include "qdbutil.h"
#include <QSqlRecord>
#include <QVariant>
#include <QDebug>

QDBUtil::QDBUtil(QObject *parent) : QObject(parent)
{

}


QList<QMap<QString,QString>>* QDBUtil::query2Map(QSqlQuery *query){

    if(NULL ==query){
        qDebug()<<"query is Null";
        return NULL;
    }


    QSqlRecord record = (*query).record();
    if(record.isEmpty()){
        qDebug()<<"record is Null";
        return NULL;
    }
    QStringList fiedls;
    int count = record.count();
    for (int i = 0; i < count; ++i) {
        fiedls << record.fieldName(i);
    }


    QList<QMap<QString,QString>>*list=new QList<QMap<QString,QString>>();
    qDebug()<<"fiedls"<<fiedls;
    while((*query).next())
    {
        QMap<QString,QString> *map=new QMap<QString,QString>();
        for(int i=0;i<fiedls.length();i++){

            map->insert(fiedls.at(i),query->value(fiedls.at(i)).toString());

        }
        list->append(*map);
     }

    qDebug()<<"return list";
    return list;

}
