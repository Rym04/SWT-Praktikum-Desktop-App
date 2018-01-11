#ifndef KATALOGEINTRAG_H
#define KATALOGEINTRAG_H

#include <QString>
#include <QDateTime>

using namespace std;

class Katalogeintrag
{
   private:
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

   public:
      Katalogeintrag();
      Katalogeintrag(const int, const int&, const int&, const int&, const int&, const int&, const QString&, const QString&,
                     const QString&, const QString&, const QString&, const QString&, const QString&, const int&, const QString&,
                     const QString&, const QString&, const QString&, const QString&, const QString&, const QString&);
      int getdokumentId();
      void setdokumentId(const int);
      int getjahr();
      void setjahr(const int&);
      int getrevision();
      void setrevision(const int&);
      int getbuchband();
      void setbuchband(const int&);
      int getauflage();
      void setauflage(const int&);
      int getzustand();
      void setzustand(const int&);
      QString getcopyright();
      void setcopyright(const QString&);
      QString getdokumentart();
      void setdokumentart(const QString&);
      QString getzeitschrift();
      void setzeitschrift(const QString&);
      QString geterscheinungsort();
      void seterscheinungsort(const QString&);
      QString getkonferenz();
      void setkonferenz(const QString&);
      QString getverlag();
      void setverlag(const QString&);
      QString getseiten();
      void setseiten(const QString&);
      int getbestand();
      void setbestand(const int&);
      QString gettitelSammelband();
      void settitelSammelband(const QString&);
      QString getaenderungsdatum();
      void setaenderungsdatum(const QString&);
      QString gettitel();
      void settitel(const QString&);
      QString getuntertitel();
      void setuntertitel(const QString&);
      QString getbeschreibung();
      void setbeschreibung(const QString&);
      QString getnotizen();
      void setnotizen(const QString&);
      QString getkommentar();
      void setkommentar(const QString&);
};
#endif   // KATALOGEINTRAG_H
