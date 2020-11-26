#include "qxmlutils.h"

#include <QtXml>
#include <QDomDocument>
#include <QDebug>
#include <QDir>

QXmlUtils::QXmlUtils(QObject *parent) : QObject(parent)
{


}

void QXmlUtils::addAccount(const AccountXml *account)
{

    qDebug() << QDir().currentPath() << "当前路径";
    QFile *file =new QFile(":/account/account/account.xml");
    file->open(QIODevice::ReadWrite | QIODevice::Text);

    QDomDocument *doc =new QDomDocument();
    doc->setContent(file);

    QDomElement rootElement= doc->documentElement();

    QDomElement accountElement=doc->createElement("account");

    accountElement.setAttribute("url","http://test.com");
    accountElement.setAttribute("name","hello");
    accountElement.setAttribute("password","123");
    accountElement.setAttribute("port","3306");
    rootElement.appendChild(accountElement);

    QTextStream outStream(file);
    doc->save(outStream,4);
    outStream.flush();
    file->flush();
    file->close();

}


void QXmlUtils::deleteAccount(QString *dbName)
{

}

void QXmlUtils::updateAccount(const AccountXml *account)
{


}


QList<AccountXml> & QXmlUtils::readAccounts()
{
    QFile *file =new QFile(":/account/account/account.xml");
    file->open(QIODevice::ReadWrite | QIODevice::Text);

    QList<AccountXml>* list= new  QList<AccountXml>();

    QDomDocument *doc =new QDomDocument();
    doc->setContent(file);
    QDomElement rootElement= doc->documentElement();

    QDomNodeList nodeList= rootElement.childNodes();

    for(int i=0;i<nodeList.size();i++){
        qDebug() << nodeList.at(i).toElement().elementsByTagName("url").at(0).toElement().text();
        qDebug() << nodeList.at(i).toElement().elementsByTagName("name").at(0).toElement().text();
        qDebug() << nodeList.at(i).toElement().elementsByTagName("password").at(0).toElement().text();
        qDebug() << nodeList.at(i).toElement().elementsByTagName("dbname").at(0).toElement().text();
        qDebug() << nodeList.at(i).toElement().elementsByTagName("port").at(0).toElement().text();

        AccountXml *xmlAccount = new AccountXml();
        QString name=nodeList.at(i).toElement().elementsByTagName("name").at(0).toElement().text();
        QString password=nodeList.at(i).toElement().elementsByTagName("password").at(0).toElement().text();
        QString url=nodeList.at(i).toElement().elementsByTagName("url").at(0).toElement().text();
        QString dbName=nodeList.at(i).toElement().elementsByTagName("dbname").at(0).toElement().text();
        QString port=nodeList.at(i).toElement().elementsByTagName("port").at(0).toElement().text();
        xmlAccount->name=&name;
        xmlAccount->pwd=&password;
        xmlAccount->url=&url;
        xmlAccount->port=port.toInt();
        list->append(*xmlAccount);
    }

    file->flush();
    file->close();
    return *list;
}






