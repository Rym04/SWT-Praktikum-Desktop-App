#include "katalogeintrag.h"

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
   ordnerpfad="";
}
Katalogeintrag::Katalogeintrag(const int id, const int &j, const int &r, const int &b, const int &a, const int &zu, const QString &c,
                               const QString &d, const QString &ze, const QString &er, const QString &k, const QString& v,
                               const QString &s, const int &be, const QString &ts, const QString &ad, const QString& t,
                               const QString &ut, const QString &bg, const QString &n, const QString &kr, const QString &op)
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
   ordnerpfad=op;
}
