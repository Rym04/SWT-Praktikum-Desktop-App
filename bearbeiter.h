#ifndef BEARBEITER_H
#define BEARBEITER_H

#include <QString>
#include <QSqlQueryModel>
#include "katalogeintrag.h"
#include "autor.h"
#include "bearbeiter.h"
#include "person.h"

using namespace std;

class Bearbeiter
{
public:
    int bearbeiterId;
    QString benutzername;
    QString emailSignatur;

    Bearbeiter();
    Bearbeiter(const int&, const QString&, const QString&);

    int maxKatalogeintrag();
    int maxAutorid();

    QList<Katalogeintrag> anzeigenKatalogeintrag();
    QSqlQueryModel * anzeigenAutor(const int&);
    QList<Katalogeintrag> suchenKatalogeintragbyid(const int&);
    QList<Katalogeintrag> suchenKatalogeintragbytitel(const QString&);
    QList<Katalogeintrag> suchenKatalogeintragbyautor(const QString&);
    QSqlQueryModel * anzeigenBearbeiter();
    QList<Bearbeiter> anzeigenBearbeiter2();
    QList<Person> anzeigenPerson();
    QList<QString> anzeigenAutor2(const int&);
};

#endif // BEARBEITER_H
