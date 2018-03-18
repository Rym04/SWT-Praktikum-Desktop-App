#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "bearbeiter.h"
#include "sqlconnector.h"
#include "autor.h"
#include "person.h"

#include <QString>

using namespace std;

Bearbeiter::Bearbeiter()
{
    bearbeiterId=0;
    benutzername="";
    emailSignatur="";
}

Bearbeiter::Bearbeiter(const int &id, const QString &bn, const QString &es)
{
    bearbeiterId=id;
    benutzername=bn;
    emailSignatur=es;
}

int Bearbeiter::maxKatalogeintrag()
{
    int max;
    Connect conn;

    conn.connClose();
    conn.connOpen();
    QSqlQuery * qry = new QSqlQuery(conn.db);

    qry->prepare("SELECT `AUTO_INCREMENT` AS _max FROM  INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = 'swt_ws17_gruppe1' AND TABLE_NAME = 'dokument'");
    qry->exec();

    if (qry->next())
        max = qry->value(0).toInt();

    return max;
}

int Bearbeiter::maxAutorid()
{
    int max;
    Connect conn;

    conn.connClose();
    conn.connOpen();
    QSqlQuery * qry = new QSqlQuery(conn.db);

    qry->prepare("SELECT `AUTO_INCREMENT` AS _max FROM  INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = 'swt_ws17_gruppe1' AND TABLE_NAME = 'autor'");
    qry->exec();

    if (qry->next())
        max = qry->value(0).toInt();

    return max;
}

QList<Katalogeintrag> Bearbeiter::anzeigenKatalogeintrag()
{
    QList<Katalogeintrag> list;
    Connect conn;

    conn.connClose();
    conn.connOpen();
    QSqlQuery * qry = new QSqlQuery(conn.db);

    qry->prepare("SELECT * FROM dokument");
    qry->exec();

    while(qry->next())
    {
        Katalogeintrag k;
        k.dokumentId= qry->value(0).toInt();
        k.jahr= qry->value(1).toInt();
        k.revision= qry->value(2).toInt();
        k.buchband= qry->value(3).toInt();
        k.zustand=qry->value(4).toInt();
        k.titel=qry->value(5).toString();
        k.untertitel=qry->value(6).toString();
        k.beschreibung=qry->value(7).toString();
        k.copyright=qry->value(8).toString();
        k.dokumentart=qry->value(9).toString();
        k.auflage=qry->value(10).toInt();
        k.konferenz=qry->value(11).toString();
        k.titelSammelband=qry->value(12).toString();
        k.zeitschrift=qry->value(13).toString();
        k.erscheinungsort=qry->value(14).toString();
        k.verlag=qry->value(15).toString();
        k.seiten=qry->value(16).toString();
        k.bestand=qry->value(17).toInt();
        k.notizen=qry->value(18).toString();
        k.kommentar=qry->value(19).toString();
        k.aenderungsdatum=qry->value(20).toString();
        k.ordnerpfad=qry->value(21).toString();
        list.append(k);
    }
    return list;
}

QSqlQueryModel * Bearbeiter::anzeigenAutor(const int &id)
{
    Connect conn;
    QSqlQueryModel * mod = new QSqlQueryModel();

    conn.connClose();
    conn.connOpen();
    QSqlQuery * qry = new QSqlQuery(conn.db);

    qry->prepare("SELECT autor FROM dokument,autor,dokument_autor WHERE dokument.dokumentid=dokument_autor.dokumentid AND autor.autorid = dokument_autor.autorid AND dokument.dokumentid=:dokumentid");
    qry->bindValue(":dokumentid", id);
    qry->exec();
    mod->setQuery(*qry);
    return mod;
}

QList<QString> Bearbeiter::anzeigenAutor2(const int &id)
{
    Connect conn;

    conn.connClose();
    conn.connOpen();
    QSqlQuery * qry = new QSqlQuery(conn.db);
    QList<QString> erg;

    qry->prepare("SELECT autor FROM dokument,autor,dokument_autor WHERE dokument.dokumentid=dokument_autor.dokumentid AND autor.autorid = dokument_autor.autorid AND dokument.dokumentid=:dokumentid");
    qry->bindValue(":dokumentid", id);
    qry->exec();

    while(qry->next())
    {
        erg.append(qry->value(0).toString());
    }

    return erg;
}

QList<Katalogeintrag> Bearbeiter::suchenKatalogeintragbyid(const int &id)
{
    QList<Katalogeintrag> list;
    Connect conn;

    conn.connClose();
    conn.connOpen();
    QSqlQuery * qry = new QSqlQuery(conn.db);

    qry->prepare("SELECT * FROM dokument WHERE dokument.dokumentid=:dokumentid");
    qry->bindValue(":dokumentid", id);
    qry->exec();

    while(qry->next())
    {
        Katalogeintrag k;
        k.dokumentId= qry->value(0).toInt();
        k.jahr= qry->value(1).toInt();
        k.revision= qry->value(2).toInt();
        k.buchband= qry->value(3).toInt();
        k.zustand=qry->value(4).toInt();
        k.titel=qry->value(5).toString();
        k.untertitel=qry->value(6).toString();
        k.beschreibung=qry->value(7).toString();
        k.copyright=qry->value(8).toString();
        k.dokumentart=qry->value(9).toString();
        k.auflage=qry->value(10).toInt();
        k.konferenz=qry->value(11).toString();
        k.titelSammelband=qry->value(12).toString();
        k.zeitschrift=qry->value(13).toString();
        k.erscheinungsort=qry->value(14).toString();
        k.verlag=qry->value(15).toString();
        k.seiten=qry->value(16).toString();
        k.bestand=qry->value(17).toInt();
        k.notizen=qry->value(18).toString();
        k.kommentar=qry->value(19).toString();
        k.aenderungsdatum=qry->value(20).toString();
        k.ordnerpfad=qry->value(21).toString();
        list.append(k);
    }
    return list;
}

QList<Katalogeintrag> Bearbeiter::suchenKatalogeintragbytitel(const QString &titel)
{
    QList<Katalogeintrag> list;
    Connect conn;

    conn.connClose();
    conn.connOpen();
    QSqlQuery * qry = new QSqlQuery(conn.db);

    qry->prepare("SELECT * FROM dokument WHERE dokument.titel LIKE CONCAT('%', :titel, '%')");
    qry->bindValue(":titel", titel);
    qry->exec();

    while(qry->next())
    {
        Katalogeintrag k;
        k.dokumentId= qry->value(0).toInt();
        k.jahr= qry->value(1).toInt();
        k.revision= qry->value(2).toInt();
        k.buchband= qry->value(3).toInt();
        k.zustand=qry->value(4).toInt();
        k.titel=qry->value(5).toString();
        k.untertitel=qry->value(6).toString();
        k.beschreibung=qry->value(7).toString();
        k.copyright=qry->value(8).toString();
        k.dokumentart=qry->value(9).toString();
        k.auflage=qry->value(10).toInt();
        k.konferenz=qry->value(11).toString();
        k.titelSammelband=qry->value(12).toString();
        k.zeitschrift=qry->value(13).toString();
        k.erscheinungsort=qry->value(14).toString();
        k.verlag=qry->value(15).toString();
        k.seiten=qry->value(16).toString();
        k.bestand=qry->value(17).toInt();
        k.notizen=qry->value(18).toString();
        k.kommentar=qry->value(19).toString();
        k.aenderungsdatum=qry->value(20).toString();
        k.ordnerpfad=qry->value(21).toString();
        list.append(k);
    }
    return list;
}

QList<Katalogeintrag> Bearbeiter::suchenKatalogeintragbyautor(const QString &autor)
{
    QList<Katalogeintrag> list;
    Connect conn;

    conn.connClose();
    conn.connOpen();
    QSqlQuery * qry = new QSqlQuery(conn.db);

    qry->prepare("SELECT * FROM dokument, autor, dokument_autor WHERE dokument.dokumentid = dokument_autor.dokumentid AND autor.autorid = dokument_autor.autorid AND autor.autor LIKE CONCAT('%', :autor, '%')");
    qry->bindValue(":autor", autor);
    qry->exec();

    while(qry->next())
    {
        Katalogeintrag k;
        k.dokumentId= qry->value(0).toInt();
        k.jahr= qry->value(1).toInt();
        k.revision= qry->value(2).toInt();
        k.buchband= qry->value(3).toInt();
        k.zustand=qry->value(4).toInt();
        k.titel=qry->value(5).toString();
        k.untertitel=qry->value(6).toString();
        k.beschreibung=qry->value(7).toString();
        k.copyright=qry->value(8).toString();
        k.dokumentart=qry->value(9).toString();
        k.auflage=qry->value(10).toInt();
        k.konferenz=qry->value(11).toString();
        k.titelSammelband=qry->value(12).toString();
        k.zeitschrift=qry->value(13).toString();
        k.erscheinungsort=qry->value(14).toString();
        k.verlag=qry->value(15).toString();
        k.seiten=qry->value(16).toString();
        k.bestand=qry->value(17).toInt();
        k.notizen=qry->value(18).toString();
        k.kommentar=qry->value(19).toString();
        k.aenderungsdatum=qry->value(20).toString();
        k.ordnerpfad=qry->value(21).toString();
        list.append(k);
    }
    return list;
}

QSqlQueryModel * Bearbeiter::anzeigenBearbeiter()
{
    Connect conn;
    QSqlQueryModel * mod = new QSqlQueryModel();

    conn.connClose();
    conn.connOpen();
    QSqlQuery * qry = new QSqlQuery(conn.db);

    qry->prepare("SELECT nachname FROM bearbeiter");
    qry->exec();
    mod->setQuery(*qry);
    return mod;
}

QList<Bearbeiter> Bearbeiter::anzeigenBearbeiter2()
{
    QList<Bearbeiter> list;
    Connect conn;

    conn.connClose();
    conn.connOpen();
    QSqlQuery * qry = new QSqlQuery(conn.db);

    qry->prepare("SELECT * FROM bearbeiter");
    qry->exec();

    while(qry->next())
    {
        Bearbeiter b;
        Person p;
        b.bearbeiterId= qry->value(0).toInt();
        p.anrede= qry->value(1).toString();
        p.akademischerGrad= qry->value(2).toString();
        p.vorname= qry->value(3).toString();
        p.nachname=qry->value(4).toString();
        p.institut=qry->value(5).toString();
        p.universitaet=qry->value(6).toString();
        p.strasse=qry->value(7).toString();
        p.hausnummer=qry->value(8).toInt();
        p.plz=qry->value(9).toInt();
        p.ort=qry->value(10).toString();
        p.land=qry->value(11).toString();
        p.email=qry->value(12).toString();
        b.benutzername=qry->value(13).toString();
        b.emailSignatur=qry->value(14).toString();
        list.append(b);
    }
    return list;
}

QList<Person> Bearbeiter::anzeigenPerson()
{
    QList<Person> list;
    Connect conn;

    conn.connClose();
    conn.connOpen();
    QSqlQuery * qry = new QSqlQuery(conn.db);

    qry->prepare("SELECT * FROM bearbeiter");
    qry->exec();

    while(qry->next())
    {
        Bearbeiter b;
        Person p;
        b.bearbeiterId= qry->value(0).toInt();
        p.anrede= qry->value(1).toString();
        p.akademischerGrad= qry->value(2).toString();
        p.vorname= qry->value(3).toString();
        p.nachname=qry->value(4).toString();
        p.institut=qry->value(5).toString();
        p.universitaet=qry->value(6).toString();
        p.strasse=qry->value(7).toString();
        p.hausnummer=qry->value(8).toInt();
        p.plz=qry->value(9).toInt();
        p.ort=qry->value(10).toString();
        p.land=qry->value(11).toString();
        p.email=qry->value(12).toString();
        b.benutzername=qry->value(13).toString();
        b.emailSignatur=qry->value(14).toString();
        list.append(p);
    }
    return list;
}
