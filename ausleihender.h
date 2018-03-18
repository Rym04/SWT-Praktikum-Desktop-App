#ifndef AUSLEIHENDER_H
#define AUSLEIHENDER_H

#include <string>
#include <ctime>
#include "person.h"

using namespace std;

class Ausleihender
{
public:
    string ausleihenderId; //muss per SQL-Abfrage festgestellt werden
    Person person;
    string grund;

    Ausleihender();
    Ausleihender(Person p, string g);
};

#endif // AUSLEIHENDER_H
