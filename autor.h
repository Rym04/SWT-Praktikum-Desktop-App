#ifndef AUTOR_H
#define AUTOR_H

#include <QString>

using namespace std;

class Autor
{
   private:

   public:
      int autorId;
      QString autor;

      Autor();
      Autor(const int, const QString&);

};
#endif   // AUTOR_H
