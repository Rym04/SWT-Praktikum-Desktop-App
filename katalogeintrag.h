#ifndef KATALOGEINTRAG_H
#define KATALOGEINTRAG_H

#include <QString>

using namespace std;

class Katalogeintrag
{
   public:
      int dokumentId;
      int jahr;
      int revision;
      int buchband;
      int auflage;
      int zustand;
      QString copyright;
      QString dokumentart;
      QString zeitschrift;
      QString erscheinungsort;
      QString konferenz;
      QString verlag;
      QString seiten;
      int bestand;
      QString titelSammelband;
      QString aenderungsdatum;
      QString titel;
      QString untertitel;
      QString beschreibung;
      QString notizen;
      QString kommentar;
      QString ordnerpfad;

      Katalogeintrag();
      Katalogeintrag(const int, const int&, const int&, const int&, const int&, const int&, const QString&, const QString&,
                     const QString&, const QString&, const QString&, const QString&, const QString&, const int&, const QString&,
                     const QString&, const QString&, const QString&, const QString&, const QString&, const QString&, const QString&);
};

#endif   // KATALOGEINTRAG_H
