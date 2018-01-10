#ifndef SQLCONNECTOR_H
#define SQLCONNECTOR_H

#include <QList>
#include <QString>
#include <cppconn/connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include "../headers/katalogeintrag.h"
#include "../headers/autor.h"

using namespace std;
using namespace sql;

class SQLController
{
   private:
      Driver *driver;
      Connection *connection;
   public:
      SQLController();
      QList<Katalogeintrag> anzeigenKatalogeintrag();
      QString anzeigenAutor(int);
      int maxKatalogeintrag();
      int maxAutorid();
      int hinzufuegenKatalogeintrag(Katalogeintrag&);
      int hinzufuegenAutor(Autor&);
      int hinzufuegenKatalogeintragAutor(Katalogeintrag&, Autor&);
      int editierenKatalogeintrag(Katalogeintrag&);
      int loeschenKatalogeintrag(int);
      QList<Katalogeintrag> suchenKatalogeintragbyid(const int& );
      QList<Katalogeintrag> suchenKatalogeintragbytitel(const QString& );
      QList<Katalogeintrag> suchenKatalogeintragbyautor(const QString& );
      void closeConnection();
      ~SQLController();
};
#endif   // SQLCONNECTOR_H
