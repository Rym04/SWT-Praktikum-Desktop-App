#include "../headers/katalogeintrag.h"

Katalogeintrag::Katalogeintrag()
{
   dokumentId=0;
   jahr=0;
   revision=0;
   buchband=0;
   auflage=0;
   zustand=0;
   copyright="";
   dokumentart="";
   zeitschrift="";
   erscheinungsort="";
   konferenz="";
   verlag="";
   seiten="";
   bestand=0;
   titelSammelband="";
   aenderungsdatum="";
   titel="";
   untertitel="";
   beschreibung="";
   notizen="";
   kommentar="";
}
Katalogeintrag::Katalogeintrag(const int id, const int &j, const int &r, const int &b, const int &a, const int &zu, const QString &c,
                               const QString &d, const QString &ze, const QString &er, const QString &k, const QString& v,
                               const QString &s, const int &be, const QString &ts, const QString &ad, const QString& t,
                               const QString &ut, const QString &bg, const QString &n, const QString &kr)
{
   dokumentId=id;
   jahr=j;
   revision=r;
   buchband=b;
   auflage=a;
   zustand=zu;
   copyright=c;
   dokumentart=d;
   zeitschrift=ze;
   erscheinungsort=er;
   konferenz=k;
   verlag=v;
   seiten=s;
   bestand=be;
   titelSammelband=ts;
   aenderungsdatum=ad;
   titel=t;
   untertitel=ut;
   beschreibung=bg;
   notizen=n;
   kommentar=kr;
}
int Katalogeintrag::getdokumentId()
{
   return dokumentId;
}
void Katalogeintrag::setdokumentId(const int id)
{
   dokumentId=id;
}
int Katalogeintrag::getjahr()
{
   return jahr;
}
void Katalogeintrag::setjahr(const int &j)
{
   jahr=j;
}
int Katalogeintrag::getrevision()
{
   return revision;
}
void Katalogeintrag::setrevision(const int &r)
{
   revision=r;
}
int Katalogeintrag::getbuchband()
{
   return buchband;
}
void Katalogeintrag::setbuchband(const int &b)
{
   buchband=b;
}
int Katalogeintrag::getauflage()
{
   return auflage;
}
void Katalogeintrag::setauflage(const int &a)
{
   auflage=a;
}
int Katalogeintrag::getzustand()
{
    return zustand;
}
void Katalogeintrag::setzustand(const int &zu)
{
    zustand=zu;
}
QString Katalogeintrag::getcopyright()
{
    return copyright;
}
void Katalogeintrag::setcopyright(const QString &c)
{
    copyright=c;
}
QString Katalogeintrag::getdokumentart()
{
    return dokumentart;
}
void Katalogeintrag::setdokumentart(const QString &d)
{
    dokumentart=d;
}
QString Katalogeintrag::getzeitschrift()
{
    return zeitschrift;
}
void Katalogeintrag::setzeitschrift(const QString &ze)
{
    zeitschrift=ze;
}
QString Katalogeintrag::geterscheinungsort()
{
    return erscheinungsort;
}
void Katalogeintrag::seterscheinungsort(const QString &er)
{
    erscheinungsort=er;
}
QString Katalogeintrag::getkonferenz()
{
    return konferenz;
}
void Katalogeintrag::setkonferenz(const QString &k)
{
    konferenz=k;
}
QString Katalogeintrag::getverlag()
{
    return verlag;
}
void Katalogeintrag::setverlag(const QString &v)
{
    verlag=v;
}
QString Katalogeintrag::getseiten()
{
    return seiten;
}
void Katalogeintrag::setseiten(const QString &s)
{
    seiten=s;
}
int Katalogeintrag::getbestand()
{
    return bestand;
}
void Katalogeintrag::setbestand(const int &be)
{
    bestand=be;
}
QString Katalogeintrag::gettitelSammelband()
{
    return titelSammelband;
}
void Katalogeintrag::settitelSammelband(const QString &ts)
{
    titelSammelband=ts;
}
QString Katalogeintrag::getaenderungsdatum()
{
    return aenderungsdatum;
}
void Katalogeintrag::setaenderungsdatum(const QString &ad)
{
    aenderungsdatum = ad;
}
QString Katalogeintrag::gettitel()
{
    return titel;
}
void Katalogeintrag::settitel(const QString &t)
{
    titel=t;
}
QString Katalogeintrag::getuntertitel()
{
    return untertitel;
}
void Katalogeintrag::setuntertitel(const QString & ut)
{
    untertitel=ut;
}
QString Katalogeintrag::getbeschreibung()
{
    return beschreibung;
}
void Katalogeintrag::setbeschreibung(const QString &bg)
{
    beschreibung=bg;
}
QString Katalogeintrag::getnotizen()
{
    return notizen;
}
void Katalogeintrag::setnotizen(const QString &n)
{
    notizen=n;
}
QString Katalogeintrag::getkommentar()
{
    return kommentar;
}
void Katalogeintrag::setkommentar(const QString &kr)
{
    kommentar=kr;
}
