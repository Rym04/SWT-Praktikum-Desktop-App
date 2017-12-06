#ifndef AUSLEIHVORGANG_H
#define AUSLEIHVORGANG_H

#include <ctime>


class Ausleihvorgang
{
public:
    string bestellungsId;
    Ausleihender ausleihender;
    enum Status {angefragt, inBearbeitung, versendet, abgelehnt} status;
    Katalogliste medien;
    tm datum; //aus ctime, Date gibt es in C++ nicht
    tm datumFertig; //aus ctime, Date gibt es in C++ nicht

    Ausleihvorgang(string bestellung);
};

#endif // AUSLEIHVORGANG_H
