#include "../headers/autor.h"

Autor::Autor()
{
   autorId=0;
   autor="";
}
Autor::Autor(const int id, const QString &a)
{
   autorId=id;
   autor=a;
}
int Autor::getautorId()
{
   return autorId;
}
void Autor::setautorId(const int id)
{
   autorId=id;
}
QString Autor::getautor()
{
   return autor;
}
void Autor::setautor(const QString &a)
{
   autor=a;
}

