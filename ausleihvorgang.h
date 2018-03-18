#ifndef AUSLEIHVORGANG_H
#define AUSLEIHVORGANG_H

#include <ctime>
#include <string>
#include <QList>
#include "ausleihender.h"
#include "katalogeintrag.h"

using namespace std;

class Ausleihvorgang
{
public:
    string bestellungsId;
    Ausleihender ausleihender;
    enum Status {angefragt, inBearbeitung, versendet, abgelehnt} status;
    QList<Katalogeintrag> medien;
    tm datum; //aus ctime, Date gibt es in C++ nicht
    tm datumFertig; //aus ctime, Date gibt es in C++ nicht

    Ausleihvorgang();

    Ausleihvorgang(string bestellungsId, Ausleihender ausleihender, Status status,
                                   QList<Katalogeintrag> medien, tm datum, tm datumFertig);
};

#endif // AUSLEIHVORGANG_H
