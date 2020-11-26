#ifndef QXMLUTILS_H
#define QXMLUTILS_H

#include <QObject>
#include <AccountXml.h>
#include <QList>
#include <QFile>

class QXmlUtils : public QObject
{
    Q_OBJECT
public:

    QFile *file;


    explicit QXmlUtils(QObject *parent = nullptr);


    /**
     * 添加一个账户
     * @brief addAccount
     * @param account
     */
    void addAccount(const AccountXml* account);

    /**
     * @brief readAccounts 读取所有账户信息
     * @return
     */
     QList<AccountXml> &readAccounts();


    /**
     * @brief deleteAccount 删除一个账户信息
     * @param dbName
     */
    void deleteAccount(QString *dbName);


    /**
     * @brief updateAccount 更新一个账户信息
     * @param account
     */
    void updateAccount(const AccountXml * account);


signals:

public slots:
};

#endif // QXMLUTILS_H
