#ifndef ACCOUNTXML_H
#define ACCOUNTXML_H
#include <QObject>

class AccountXml{

public :
   QString * url;
   QString * name;
   QString * pwd;
   qint8 port;

   AccountXml();

};


#endif // ACCOUNTXML_H
