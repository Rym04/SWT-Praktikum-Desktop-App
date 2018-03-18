#ifndef KATALOGLISTE_H
#define KATALOGLISTE_H

#include <vector>
#include "katalogeintrag.h"
using namespace std;

class Katalogliste
{
public:
    vector<Katalogeintrag> eintrag; //ArrayListe gibt es in C++ nicht, vector entspricht ArrayList

    Katalogliste();
    void hinzufuegen(Katalogeintrag katalogeintrag);
};

#endif // KATALOGLISTE_H
