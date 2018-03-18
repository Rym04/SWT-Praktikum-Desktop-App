#include "sqlconnector.h"

void Connect::connClose()
{
    db.close();
    db.removeDatabase(QSqlDatabase::defaultConnection);
}

bool Connect::connOpen()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("son1i-server-h31m.strangled.net");
    db.setDatabaseName("swt_ws17_gruppe1");
    db.setUserName("swt_ws17_gruppe1");
    db.setPassword("OjQ42RwpYnRMIYZN");
    db.open();

    if (!db.open())
    {
        qDebug() << ("No Connection");
        return false;
    }
    else
    {
        qDebug() << ("Connected");
        return true;
    }
}

Connect::~Connect()
{

}
