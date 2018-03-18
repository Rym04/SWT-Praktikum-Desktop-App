#include "autor.h"

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

