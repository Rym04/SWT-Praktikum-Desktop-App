#include "katalogeintrag.h"

Katalogeintrag::Katalogeintrag(string id)
{
    this->dokumentId = id;

    //SQL-Abfragen
    dokumentId;
    dokumentAutoren; //Schleife bauen
    jahr;
    revision;
    buchband;
    zustand;
    titel;
    untertitel;
    beschreibung;
    copyright;
    dokumentart;
    ausfertigung;
    konferenz;
    sammelbandAutoren; //Schleife bauen
    titel_sammelband;
    zeitschrift;
    ort;
    verlag; //in ER-Diagramm "veroeffentlicher"
    seiten;
    bestand;
    notizen;
    kommentar;
    aenderungsdatum;
}

