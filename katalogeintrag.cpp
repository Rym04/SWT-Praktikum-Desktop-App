#include "katalogeintrag.h"

Katalogeintrag::Katalogeintrag(string dokumentId, string dokumentAutoren[], int jahr,
                               int revision, int buchband, int zustand, string titel,
                               string untertitel, string beschreibung, string copyright,
                               string dokumentart, int ausfertigung, string konferenz,
                               string sammelbandAutoren[], int anzahlSammelbandAutoren,
                               string titel_sammelband, string zeitschrift, string ort,
                               string verlag, string seiten, int bestand, string notizen,
                               string kommentar, tm aenderungsdatum)
{
    this->dokumentId = dokumentId;

    this->dokumentAutoren = new string[anzahlDokumentAutoren];
    for (int i = 0; i<anzahlDokumentAutoren, i++)
    {
        this->dokumentAutoren[i] = dokumentAutoren[i];
    }

    this->jahr = jahr;
    this->revision = revision;
    this->buchband = buchband;
    this->zustand = zustand;
    this->titel = titel;
    this->untertitel = untertitel;
    this->beschreibung = beschreibung;
    this->copyright = copyright;
    this->dokumentart = dokumentart;
    this->ausfertigung = ausfertigung;
    this->konferenz = konferenz;

    this->sammelbandAutoren = new string [anzahlSammelbandAutoren];
    for (int i = 0; i<anzahlSammelbandAutoren; i++)
        this->sammelbandAutoren[i] = sammelbandAutoren[i];
    }

    this->titel_sammelband = titel_sammelband;
    this->zeitschrift = zeitschrift;
    this->ort = ort;
    this->verlag = verlag; //in ER-Diagramm "veroeffentlicher"
    this->seiten = seiten;
    this->bestand = bestand;
    this->notizen = notizen;
    this->kommentar = kommentar;
    this->aenderungsdatum = aenderungsdatum;
}


Katalogeintrag::Katalogeintrag(string dokumentId, string dokumentAutoren[],
                               int anzahlDokumentAutoren, int jahr, int revision, int buchband,
                               int zustand, string titel, string copyright, int ausfertigung,
                               int bestand, string notizen, string kommentar, tm aenderungsdatum)
{
    this->dokumentId = dokumentId;

    this->dokumentAutoren = new string[anzahlDokumentAutoren];
    for (int i = 0; i<anzahlDokumentAutoren, i++)
    {
        this->dokumentAutoren[i] = dokumentAutoren[i];
    }

    this->jahr = jahr;
    this->revision = revision;
    this->buchband = buchband;
    this->zustand = zustand;
    this->titel = titel;
    this->copyright = copyright;
    this->ausfertigung = ausfertigung;
    this->bestand = bestand;
    this->notizen = notizen;
    this->kommentar = kommentar;
    this->aenderungsdatum = aenderungsdatum;
}
