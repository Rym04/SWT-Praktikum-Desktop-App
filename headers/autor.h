#ifndef AUTOR_H
#define AUTOR_H

#include <QString>

using namespace std;

class Autor
{
   private:
      int autorId;
      QString autor;

   public:
      Autor();
      Autor(const int, const QString&);
      int getautorId();
      void setautorId(const int);
      QString getautor();
      void setautor(const QString&);
      
};
#endif   // AUTOR_H
