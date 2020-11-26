#ifndef QDBUTIL_H
#define QDBUTIL_H

#include <QObject>
#include <QMap>
#include <QSqlQuery>

/***
 *
 *  数据库操作工具类
 *
**/
class QDBUtil : public QObject
{
    Q_OBJECT
public:
    explicit QDBUtil(QObject *parent = nullptr);

    /**
     * 执行sql
     * @brief queryData
     * @param query
     * @param sql
     * @return
     */
    static QList<QMap<QString,QString>>* query2Map(QSqlQuery* query);

signals:

public slots:
};

#endif // QDBUTIL_H
