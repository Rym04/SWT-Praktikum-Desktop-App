#include "person.h"

#include <QString>

using namespace std;

Person::Person()
{
    anrede="";
    akademischerGrad="";
    vorname="";
    nachname="";
    institut="";
    universitaet="";
    strasse="";
    hausnummer=0;
    plz=0;
    ort="";
    land="";
    email="";
}

Person::Person(const QString& a, const QString &ag, const QString &vn, const QString &nn, const QString &i, const QString &u, const QString &s,
                               const int &hnr, const int &p, const QString &o, const QString &l, const QString &e)
{
   anrede=a;
   akademischerGrad=ag;
   vorname=vn;
   nachname=nn;
   institut=i;
   universitaet=u;
   strasse=s;
   hausnummer=hnr;
   plz=p;
   ort=o;
   land=l;
   email=e;
}
