#ifndef QJERRYSQLLITE_H
#define QJERRYSQLLITE_H

#include <QObject>
#include <qdebug.h>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class QJerrySqlLite : public QObject
{
    Q_OBJECT
public:
    explicit QJerrySqlLite(QObject *parent = nullptr);
    /**
     * 连接DB
     * @brief connectDB
     * @return
     */
    bool connectDB();

    /**
     *  执行写操作
     * @brief execSQl
     * @param sql
     * @return
     */
    bool execSQl(const QString* sql);

    /**
     * 关闭数据库
     * @brief closeDB
     * @return
     */
    bool closeDB();

    /**
     * 执行读操作
     * @brief queryData
     * @param sql
     * @return
     */
    QList<QMap<QString,QString>>& queryData(const QString* sql);



    /**
     * 初始化表结构
     * @brief initTable
     * @return
     */
    bool initTable();



signals:

};

#endif // QJERRYSQLLITE_H
