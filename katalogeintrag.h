#ifndef KATALOGEINTRAG_H
#define KATALOGEINTRAG_H

#include <ctime>

class Katalogeintrag
{
public:
    string dokumentId;
    string dokumentAutoren[];
    int jahr;
    int revision;
    int buchband;
    int zustand;
    string titel;
    string untertitel;
    string beschreibung;
    string copyright;
    string dokumentart;
    int ausfertigung;
    string konferenz;
    string sammelbandAutoren[];
    string titel_sammelband;
    string zeitschrift;
    string ort;
    string verlag; //in ER-Diagramm "veroeffentlicher"
    string seiten;
    int bestand;
    string notizen;
    string kommentar;
    tm aenderungsdatum; //aus ctime, Date gibt es in C++ nicht

    Katalogeintrag(string dokumentId, string dokumentAutoren[], int jahr,
                                   int revision, int buchband, int zustand, string titel,
                                   string untertitel, string beschreibung, string copyright,
                                   string dokumentart, int ausfertigung, string konferenz,
                                   string sammelbandAutoren[], int anzahlSammelbandAutoren,
                                   string titel_sammelband, string zeitschrift, string ort,
                                   string verlag, string seiten, int bestand, string notizen,
                                   string kommentar, tm aenderungsdatum);

    Katalogeintrag(string dokumentId, string dokumentAutoren[],
                                   int anzahlDokumentAutoren, int jahr, int revision, int buchband,
                                   int zustand, string titel, string copyright, int ausfertigung,
                                   int bestand, string notizen, string kommentar, tm aenderungsdatum);
};

#endif // KATALOGEINTRAG_H
