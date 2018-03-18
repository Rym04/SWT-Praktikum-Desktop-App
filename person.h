#ifndef PERSON_H
#define PERSON_H

#include <QString>

using namespace std;

class Person
{
    public:
        QString anrede;
        QString akademischerGrad;
        QString vorname;
        QString nachname;
        QString institut;
        QString universitaet;
        QString strasse;
        int hausnummer;
        int plz;
        QString ort;
        QString land;
        QString email;

    Person();
    Person(const QString&, const QString&, const QString&, const QString&, const QString&, const QString&, const QString&, const int&, const int&, const QString&, const QString&, const QString&);
};

#endif // PERSON_H
