#include "connectdb.h"
#include "ui_connectdb.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QPluginLoader>
#include <QMessageBox>
#include <qjerrysqllite.h>
#include "mainwindow.h"
#include "qdbutil.h"


ConnectDB::ConnectDB(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConnectDB)
{
    ui->setupUi(this);
    MainWindow *windows= (MainWindow *) parent;

}


ConnectDB::~ConnectDB()
{
    delete ui;
}


void ConnectDB::on_testConnButton_clicked()
{
    QString url=this->ui->lineEdit_address->text();
    QString name=this->ui->lineEdit_username->text();
    QString password=this->ui->lineEdit_password->text();
    int port=this->ui->lineEdit_port->text().toInt();
    QString dbName=this->ui->lineEdit_dbname->text();

    bool connectDB=this->connect2DB(new QSqlDatabase(),&url,&name,&password,port,&dbName);

    if(!connectDB){
        qDebug()<<"连接失败";
    }else{
        QMessageBox::information(NULL, "提示", "连接成功",QMessageBox::Ok);
    }





}

void ConnectDB::on_connButton_clicked()
{

    QString url=this->ui->lineEdit_address->text();
    QString name=this->ui->lineEdit_username->text();
    QString password=this->ui->lineEdit_password->text();
    int port=this->ui->lineEdit_port->text().toInt();
    QString dbName=this->ui->lineEdit_dbname->text();

    QJerrySqlLite sqllitel;
    QString *sql=new QString();
    sql->append("insert into account values");
    sql->append(" (");
    sql->append(" NULL,");
    sql->append(" '"+name+"' ,");
    sql->append(" '"+password+"' ,");
    sql->append(" '"+url.trimmed()+"',");
    sql->append(" 3306 ,");
    sql->append(" '"+dbName+"')");

    qDebug()<<"sql:"<<*sql;

    bool isSave=sqllitel.execSQl(sql);

    if(!isSave){
        qDebug()<<"保存失败";
        return;
    }

    emit updateUi();
}


QSqlDatabase* ConnectDB::connect2DB(QSqlDatabase *database,QString *url, QString *name, QString *password, int port,QString * dbName){

    QSqlDatabase::database(*dbName);

    if (QSqlDatabase::contains(*dbName))//判断testConnect连接是否存在并连接
    {
      *database= QSqlDatabase::database(*dbName);


    }
    else //未连接则新建数据库连接
    {
        *database=QSqlDatabase::addDatabase("QMYSQL",*dbName);//创建数据库连接，并为其命名testConnect

        (*database).setHostName(*url);      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
        (*database).setPort(port);                 //连接数据库端口号，与设置一致
        (*database).setUserName(*name);          //数据库用户名，与设置一致
        (*database).setPassword(*password);    //数据库密码，与设置一致

    }
    if(!database->open())
    {
        qDebug()<<"fail to connect mysql:" << database->lastError();
        return NULL;
    }

    return database;
}



bool ConnectDB::exec(QSqlDatabase *database,const QString* sql){
    qDebug()<<"isOpen" << database;
    QSqlQuery query(*database);
    if(!query.exec(*sql)){
           qDebug()<<query.lastError();
    }

    while(query.next())
       {
           qDebug()<<query.value(0).toString();

       }

}

QList<QMap<QString,QString>>* ConnectDB::queryData(QSqlDatabase *database,const QString* sql){


    QSqlQuery query(*database);
    if(!query.exec(*sql)){
           qDebug()<<query.lastError();
    }
    QList<QMap<QString,QString>> *list=QDBUtil::query2Map(&query);
    qDebug()<<"return list 2" <<  list<<" "<< list->length();
    return list;
}





