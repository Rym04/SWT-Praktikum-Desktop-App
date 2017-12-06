#ifndef AUSLEIHLISTE_H
#define AUSLEIHLISTE_H

#include <vector>
using namespace std;

class Ausleihliste
{
public:
    vector<Ausleihvorgang> vorgang; //ArrayListe gibt es in C++ nicht, vector entspricht ArrayList

    Ausleihliste();
    void hinzufuegen(Ausleihvorgang ausleihvorgang);
};

#endif // AUSLEIHLISTE_H
