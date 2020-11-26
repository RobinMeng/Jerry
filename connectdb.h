#ifndef CONNECTDB_H
#define CONNECTDB_H

#include <QWidget>
#include "mainwindow.h"
#include <QSqlDatabase>

namespace Ui {
class ConnectDB;
}

class ConnectDB : public QWidget
{
    Q_OBJECT

public:
    explicit ConnectDB(QWidget *parent = nullptr);

    ~ConnectDB();

    /**
     * 连接数据库
     * @brief connect2DB
     * @param url
     * @param name
     * @param password
     * @param port
     * @param dbName
     * @return
     */
    QSqlDatabase* connect2DB(QSqlDatabase *base,QString* url,QString* name,QString* password,int port,QString* dbName);

    /**
     * 执行sql
     * @brief exec
     * @param sql
     * @return
     */
    bool exec(QSqlDatabase *base,const QString* sql);


    /**
     * 执行读取sql
     * @brief queryData
     * @param base
     * @param sql
     * @return
     */
    QList<QMap<QString,QString>>* queryData(QSqlDatabase *base,const QString* sql);




signals:
    /**
       更新ui
     * @brief update
     */
    void updateUi();




private slots:
    void on_testConnButton_clicked();

    void on_connButton_clicked();

private:
    Ui::ConnectDB *ui;
};

#endif // CONNECTDB_H
