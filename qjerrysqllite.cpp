#include "qjerrysqllite.h"
#include <QtDebug>
#include <QSqlRecord>
#include <QList>
QJerrySqlLite::QJerrySqlLite(QObject *parent) : QObject(parent)
{


}



bool QJerrySqlLite::connectDB(){
       QSqlDatabase db;

       if(QSqlDatabase::contains("qt_sql_default_connection")){
           db = QSqlDatabase::database("qt_sql_default_connection");
       }else {
           db= QSqlDatabase::addDatabase("QSQLITE");

       }

       db.setDatabaseName("Jerry.db");
       if(!db.isOpen()){
           db.open();
       }else{
           qDebug()<<"success to connet db";
       }

       return db.isOpen();
}

bool QJerrySqlLite::execSQl(const QString* sql){
    if(this->connectDB()){
        QSqlQuery query;
        if(!query.exec("create  table account(id Integer primary key autoincrement, name, pwd, url, port int, dbname)")){
                qDebug()<<"create failed"<<   query.lastError();
        }

//        if(!query.exec("insert into account values(NULL,'2','1','1',3306)")){
//            qDebug()<<"insert failed" << query.lastError();
//        }




        if(!query.exec(*sql)){
             qDebug()<<"exec failed" << query.lastError();
             return false;
        }
    }

    return true;
}

bool QJerrySqlLite::closeDB()
{
     if(this->connectDB()){
         QSqlDatabase db;
         db.close();
     }
     return true;
}

QList<QMap<QString,QString>>& QJerrySqlLite::queryData(const QString *sql){

    QSqlQuery query;
    if(!query.exec(*sql)){
           qDebug()<<query.lastError();
    }

    QList<QMap<QString,QString>> *list= new QList<QMap<QString,QString>>();

    while (query.next()) {
        QString id=query.value("id").toString();
        QString name=query.value("name").toString();
        QString password=query.value("pwd").toString();
        QString port=query.value("port").toString();
        QString url=query.value("url").toString();
        QString dbName=query.value("dbname").toString();

        QMap<QString,QString>* map= new QMap<QString,QString>();
        map->insert("id",id);
        map->insert("name",name);
        map->insert("password",password);
        map->insert("port",port);
        map->insert("url",url);
        map->insert("dbname",dbName);
        list->append(*map);
    }
    return *list;
}


bool QJerrySqlLite::initTable(){

    if(this->connectDB()){
        QSqlQuery query;
        if(!query.exec("create  table account(id Integer primary key autoincrement, name, pwd, url, port int, dbname)")){
                qDebug()<<"create failed"<<   query.lastError();

                return false;
        }

    }
    return true;

}


