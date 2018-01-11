#include "../headers/sqlconnector.h"
#include "../headers/autor.h"

//Baut die Verbindung zum MySQL Server auf
SQLController::SQLController()
{
   try{
      driver=get_driver_instance();
      connection=driver->connect("son1i-server-h31m.strangled.net","swt_ws17_gruppe1","OjQ42RwpYnRMIYZN");
      //connection=driver->connect("localhost","swt_ws17_gruppe1","OjQ42RwpYnRMIYZN");
      connection->setAutoCommit(0);
      connection->setSchema("swt_ws17_gruppe1");
   }catch(SQLException &ex)
   {
      cout<<"Exception occurred"<<ex.getErrorCode()<<endl;
   }
}
//Hilfsvariable zum erstellen eines neuen Katalogeintrags
int SQLController::maxKatalogeintrag()
{
    int max=0;
    PreparedStatement *pstmt=connection->prepareStatement("SELECT MAX(dokumentid) AS _max FROM dokument");
    ResultSet *resultSet=NULL;
    try {
        resultSet=pstmt->executeQuery();
        while(resultSet->next()) {
            max=resultSet->getInt("_max");
            max=max+1;
        }

    } catch(SQLException &ex)
    {
        cout<<"Exception occurred"<<ex.getErrorCode()<<endl;
    }
resultSet->close();
pstmt->close();
delete pstmt;
delete resultSet;
return max;
}
//Hilfsvariable zum erstellen eines neuen Autors
int SQLController::maxAutorid()
{
    int max=0;
    PreparedStatement *pstmt=connection->prepareStatement("SELECT MAX(autorid) AS _max FROM autor");
    ResultSet *resultSet=NULL;
    try {
        resultSet=pstmt->executeQuery();
        while(resultSet->next()) {
            max=resultSet->getInt("_max");
            max=max+1;
        }

    } catch(SQLException &ex)
    {
        cout<<"Exception occurred"<<ex.getErrorCode()<<endl;
    }
resultSet->close();
pstmt->close();
delete pstmt;
delete resultSet;
return max;
}
//Abfrage für den Screen Katalogeintrag editieren (Katalogeintrag)
QList<Katalogeintrag> SQLController::anzeigenKatalogeintrag()
{
   QList<Katalogeintrag> list;
   PreparedStatement *pstmt=connection->prepareStatement("SELECT * FROM dokument");
   ResultSet *resultSet=NULL;
   try
   {
      resultSet=pstmt->executeQuery();
      while(resultSet->next())
      {
         Katalogeintrag k;
         k.setdokumentId(resultSet->getInt("dokumentid"));
         k.setjahr(resultSet->getInt("jahr"));
         k.setrevision(resultSet->getInt("revision"));
         k.setbuchband(resultSet->getInt("buchband"));
         k.setauflage(resultSet->getInt("ausfertigung"));
         k.setzustand(resultSet->getInt("zustand"));
         k.setcopyright(QString::fromStdString(resultSet->getString("copyright")));
         k.setdokumentart(QString::fromStdString(resultSet->getString("dokumentart")));
         k.setzeitschrift(QString::fromStdString(resultSet->getString("zeitschrift")));
         k.seterscheinungsort(QString::fromStdString(resultSet->getString("ort")));
         k.setkonferenz(QString::fromStdString(resultSet->getString("konferenz")));
         k.setverlag(QString::fromStdString(resultSet->getString("verlag")));
         k.setseiten(QString::fromStdString(resultSet->getString("seiten")));
         k.setbestand(resultSet->getInt("bestand"));
         k.settitelSammelband(QString::fromStdString(resultSet->getString("titel_sammelband")));
         k.setaenderungsdatum(QString::fromStdString(resultSet->getString("aenderungsdatum")));
         k.settitel(QString::fromStdString(resultSet->getString("titel")));
         k.setuntertitel(QString::fromStdString(resultSet->getString("untertitel")));
         k.setbeschreibung(QString::fromStdString(resultSet->getString("beschreibung")));
         k.setnotizen(QString::fromStdString(resultSet->getString("notizen")));
         k.setkommentar(QString::fromStdString(resultSet->getString("kommentar")));
         list.append(k);
      }
   }catch(SQLException &ex)
   {
      cout<<"Exception occurred"<<ex.getErrorCode()<<endl;
   }
   resultSet->close();
   pstmt->close();
   delete pstmt;
   delete resultSet;
   return list;
}
//Abfrage für den View Katalogeintrag editieren (Autor)
QString SQLController::anzeigenAutor(int nr)
{
   QString autor="";
   string str="";
   PreparedStatement *pstmt=connection->prepareStatement("SELECT autor.autor AS _msg FROM dokument,autor,dokument_autor WHERE dokument.dokumentid = dokument_autor.dokumentid AND autor.autorid = dokument_autor.autorid AND dokument.dokumentid=?");
   ResultSet *resultSet=NULL;
   try
   {
      pstmt->setInt(1,nr);
      resultSet=pstmt->executeQuery();
      while(resultSet->next())
      {
            str=resultSet->getString("_msg");
            autor=QString::fromStdString(str);
      }
   }catch(SQLException &ex)
   {
      cout<<"Exception occurred"<<ex.getErrorCode()<<endl;
   }
   resultSet->close();
   pstmt->close();
   delete pstmt;
   delete resultSet;
   return autor;
}
//Abfrage für den Screen Katalogeintrag neu (Katalogeintrag)
int SQLController::hinzufuegenKatalogeintrag(Katalogeintrag &k)
{
   int result=0;
   PreparedStatement *pstmt=connection->prepareStatement
      ("INSERT INTO dokument ( jahr, revision, buchband, ausfertigung, zustand, copyright, dokumentart, zeitschrift, ort, konferenz, verlag, seiten, bestand, titel_sammelband, aenderungsdatum, titel, untertitel, beschreibung, notizen, kommentar )VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
   try
   {
       pstmt->setInt(1,k.getjahr());
       pstmt->setInt(2,k.getrevision());
       pstmt->setInt(3,k.getbuchband());
       pstmt->setInt(4,k.getauflage());
       pstmt->setInt(5,k.getzustand());
       pstmt->setString(6,k.getcopyright().toStdString());
       pstmt->setString(7,k.getdokumentart().toStdString());
       pstmt->setString(8,k.getzeitschrift().toStdString());
       pstmt->setString(9,k.geterscheinungsort().toStdString());
       pstmt->setString(10,k.getkonferenz().toStdString());
       pstmt->setString(11,k.getverlag().toStdString());
       pstmt->setString(12,k.getseiten().toStdString());
       pstmt->setInt(13,k.getbestand());
       pstmt->setString(14,k.gettitelSammelband().toStdString());
       pstmt->setString(15,k.getaenderungsdatum().toStdString());
       pstmt->setString(16,k.gettitel().toStdString());
       pstmt->setString(17,k.getuntertitel().toStdString());
       pstmt->setString(18,k.getbeschreibung().toStdString());
       pstmt->setString(19,k.getnotizen().toStdString());
       pstmt->setString(20,k.getkommentar().toStdString());
      result=pstmt->executeUpdate();
      connection->commit();
   }catch(SQLException &ex)
   {
      cout<<"Exception occurred"<<ex.getErrorCode()<<endl;
   }
   pstmt->close();
   delete pstmt;
   return result;
}
//Abfrage für den Screen Katalogeintrag neu (Autor)
int SQLController::hinzufuegenAutor(Autor &a)
{
   int result=0;
   PreparedStatement *pstmt=connection->prepareStatement
      ("INSERT INTO autor ( autor ) SELECT * FROM (SELECT ?) AS tmp WHERE NOT EXISTS (SELECT autor FROM autor WHERE autor = ?) LIMIT 1");
   try
   {
      pstmt->setString(1,a.getautor().toStdString());
      pstmt->setString(2,a.getautor().toStdString());

      result=pstmt->executeUpdate();
      connection->commit();
   }catch(SQLException &ex)
   {
      cout<<"Exception occurred"<<ex.getErrorCode()<<endl;
   }
   pstmt->close();
   delete pstmt;
   return result;
}
//Abfrage für den Screen Katalogeintrag neu (Dokument_Autor)
int SQLController::hinzufuegenKatalogeintragAutor(Katalogeintrag &k, Autor &a)
{
   int result=0;
   PreparedStatement *pstmt=connection->prepareStatement
      ("INSERT INTO dokument_autor ( dokumentid, autorid ) SELECT ?, ? FROM dokument_autor WHERE NOT EXISTS (SELECT dokumentid,autorid FROM dokument_autor WHERE dokumentid = ? AND autorid=?) LIMIT 1");
   try
   {
      pstmt->setInt(1,k.getdokumentId());
      pstmt->setInt(2,a.getautorId());
      pstmt->setInt(3,k.getdokumentId());
      pstmt->setInt(4,a.getautorId());

      result=pstmt->executeUpdate();
      connection->commit();
   }catch(SQLException &ex)
   {
      cout<<"Exception occurred"<<ex.getErrorCode()<<endl;
   }
   pstmt->close();
   delete pstmt;
   return result;
}
//Abfrage für den Screen Katalogeintrag editieren, das eigentliche editieren
int SQLController::editierenKatalogeintrag(Katalogeintrag &k)
{
   int result=0;
   PreparedStatement *pstmt=connection->prepareStatement
      ("UPDATE dokument SET jahr=?, revision=?, buchband=?,ausfertigung=?,zustand=?,copyright=?,dokumentart=?,zeitschrift=?,ort=?,konferenz=?,verlag=?,seiten=?,bestand=?,titel_sammelband=?,aenderungsdatum=?,titel=?,untertitel=?,beschreibung=?,notizen=?,kommentar=? WHERE dokumentid=?");
   try
   {
      pstmt->setInt(1,k.getjahr());
      pstmt->setInt(2,k.getrevision());
      pstmt->setInt(3,k.getbuchband());
      pstmt->setInt(4,k.getauflage());
      pstmt->setInt(5,k.getzustand());
      pstmt->setString(6,k.getcopyright().toStdString());
      pstmt->setString(7,k.getdokumentart().toStdString());
      pstmt->setString(8,k.getzeitschrift().toStdString());
      pstmt->setString(9,k.geterscheinungsort().toStdString());
      pstmt->setString(10,k.getkonferenz().toStdString());
      pstmt->setString(11,k.getverlag().toStdString());
      pstmt->setString(12,k.getseiten().toStdString());
      pstmt->setInt(13,k.getbestand());
      pstmt->setString(14,k.gettitelSammelband().toStdString());
      pstmt->setString(15,k.getaenderungsdatum().toStdString());
      pstmt->setString(16,k.gettitel().toStdString());
      pstmt->setString(17,k.getuntertitel().toStdString());
      pstmt->setString(18,k.getbeschreibung().toStdString());
      pstmt->setString(19,k.getnotizen().toStdString());
      pstmt->setString(20,k.getkommentar().toStdString());
      pstmt->setInt(21,k.getdokumentId());
      pstmt->executeUpdate();
      connection->commit();
   }catch(SQLException &ex)
   {
      cout<<"Exception occurred"<<ex.getErrorCode()<<endl;
   }
   pstmt->close();
   delete pstmt;
   return result;
}
//Abfrage für den Screen Katalogeintrag editieren, löschen eines Katalogeintrages
int SQLController::loeschenKatalogeintrag(int id)
{
   int result=0;
   PreparedStatement *pstmt=connection->prepareStatement
      ("DELETE FROM dokument WHERE dokumentid=?");
   try
   {
      pstmt->setInt(1,id);
      result=pstmt->executeUpdate();
      connection->commit();
   }catch(SQLException &ex)
   {
      cout<<"Exception occurred"<<ex.getErrorCode()<<endl;
   }
   pstmt->close();
   delete pstmt;
   return result;
}
//Abfrage für den Screen Katalogeintrag editieren, suchen nach dokumentid
QList<Katalogeintrag> SQLController::suchenKatalogeintragbyid(const int &id)
{
   QList<Katalogeintrag> list;
   ResultSet *resultSet=NULL;
   PreparedStatement *pstmt=connection->prepareStatement
      ("SELECT * FROM dokument WHERE dokumentid = ?");
   try
   {
      pstmt->setInt(1,id);
      resultSet=pstmt->executeQuery();
      while(resultSet->next()){
         Katalogeintrag k;
         k.setdokumentId(resultSet->getInt("dokumentid"));
         k.setjahr(resultSet->getInt("jahr"));
         k.setrevision(resultSet->getInt("revision"));
         k.setbuchband(resultSet->getInt("buchband"));
         k.setauflage(resultSet->getInt("ausfertigung"));
         k.setzustand(resultSet->getInt("zustand"));
         k.setcopyright(QString::fromStdString(resultSet->getString("copyright")));
         k.setdokumentart(QString::fromStdString(resultSet->getString("dokumentart")));
         k.setzeitschrift(QString::fromStdString(resultSet->getString("zeitschrift")));
         k.seterscheinungsort(QString::fromStdString(resultSet->getString("ort")));
         k.setkonferenz(QString::fromStdString(resultSet->getString("konferenz")));
         k.setverlag(QString::fromStdString(resultSet->getString("verlag")));
         k.setseiten(QString::fromStdString(resultSet->getString("seiten")));
         k.setbestand(resultSet->getInt("bestand"));
         k.settitelSammelband(QString::fromStdString(resultSet->getString("titel_sammelband")));
         k.setaenderungsdatum(QString::fromStdString(resultSet->getString("aenderungsdatum")));
         k.settitel(QString::fromStdString(resultSet->getString("titel")));
         k.setuntertitel(QString::fromStdString(resultSet->getString("untertitel")));
         k.setbeschreibung(QString::fromStdString(resultSet->getString("beschreibung")));
         k.setnotizen(QString::fromStdString(resultSet->getString("notizen")));
         k.setkommentar(QString::fromStdString(resultSet->getString("kommentar")));
         list.append(k);
      }
   }catch(SQLException &ex)
   {
      cout<<"Exception occurred"<<ex.getErrorCode()<<endl;
   }
   resultSet->close();
   pstmt->close();
   delete pstmt;
   delete resultSet;
   return list;
}
//Abfrage für den Screen Katalogeintrag editieren, suchen nach titel
QList<Katalogeintrag> SQLController::suchenKatalogeintragbytitel(const QString &t)
{
   QList<Katalogeintrag> list;
   ResultSet *resultSet=NULL;
   PreparedStatement *pstmt=connection->prepareStatement
      ("SELECT * FROM dokument WHERE titel LIKE CONCAT('%', ?, '%')");
   try
   {

      pstmt->setString(1,t.toStdString());
      resultSet=pstmt->executeQuery();
      while(resultSet->next()){
         Katalogeintrag k;
         k.setdokumentId(resultSet->getInt("dokumentid"));
         k.setjahr(resultSet->getInt("jahr"));
         k.setrevision(resultSet->getInt("revision"));
         k.setbuchband(resultSet->getInt("buchband"));
         k.setauflage(resultSet->getInt("ausfertigung"));
         k.setzustand(resultSet->getInt("zustand"));
         k.setcopyright(QString::fromStdString(resultSet->getString("copyright")));
         k.setdokumentart(QString::fromStdString(resultSet->getString("dokumentart")));
         k.setzeitschrift(QString::fromStdString(resultSet->getString("zeitschrift")));
         k.seterscheinungsort(QString::fromStdString(resultSet->getString("ort")));
         k.setkonferenz(QString::fromStdString(resultSet->getString("konferenz")));
         k.setverlag(QString::fromStdString(resultSet->getString("verlag")));
         k.setseiten(QString::fromStdString(resultSet->getString("seiten")));
         k.setbestand(resultSet->getInt("bestand"));
         k.settitelSammelband(QString::fromStdString(resultSet->getString("titel_sammelband")));
         k.setaenderungsdatum(QString::fromStdString(resultSet->getString("aenderungsdatum")));
         k.settitel(QString::fromStdString(resultSet->getString("titel")));
         k.setuntertitel(QString::fromStdString(resultSet->getString("untertitel")));
         k.setbeschreibung(QString::fromStdString(resultSet->getString("beschreibung")));
         k.setnotizen(QString::fromStdString(resultSet->getString("notizen")));
         k.setkommentar(QString::fromStdString(resultSet->getString("kommentar")));
         list.append(k);
      }
   }catch(SQLException &ex)
   {
      cout<<"Exception occurred"<<ex.getErrorCode()<<endl;
   }
   resultSet->close();
   pstmt->close();
   delete pstmt;
   delete resultSet;
   return list;
}
//Abfrage für den Screen Katalogeintrag editieren, suchen nach autor
QList<Katalogeintrag> SQLController::suchenKatalogeintragbyautor(const QString &t)
{
   QList<Katalogeintrag> list;
   ResultSet *resultSet=NULL;
   PreparedStatement *pstmt=connection->prepareStatement
      ("SELECT * FROM dokument,autor,dokument_autor WHERE dokument.dokumentid=dokument_autor.dokumentid AND autor.autorid = dokument_autor.autorid AND autor.autor LIKE CONCAT('%', ?, '%')");
   try
   {
      pstmt->setString(1,t.toStdString());
      resultSet=pstmt->executeQuery();
      while(resultSet->next()){
         Katalogeintrag k;
         k.setdokumentId(resultSet->getInt("dokumentid"));
         k.setjahr(resultSet->getInt("jahr"));
         k.setrevision(resultSet->getInt("revision"));
         k.setbuchband(resultSet->getInt("buchband"));
         k.setauflage(resultSet->getInt("ausfertigung"));
         k.setzustand(resultSet->getInt("zustand"));
         k.setcopyright(QString::fromStdString(resultSet->getString("copyright")));
         k.setdokumentart(QString::fromStdString(resultSet->getString("dokumentart")));
         k.setzeitschrift(QString::fromStdString(resultSet->getString("zeitschrift")));
         k.seterscheinungsort(QString::fromStdString(resultSet->getString("ort")));
         k.setkonferenz(QString::fromStdString(resultSet->getString("konferenz")));
         k.setverlag(QString::fromStdString(resultSet->getString("verlag")));
         k.setseiten(QString::fromStdString(resultSet->getString("seiten")));
         k.setbestand(resultSet->getInt("bestand"));
         k.settitelSammelband(QString::fromStdString(resultSet->getString("titel_sammelband")));
         k.setaenderungsdatum(QString::fromStdString(resultSet->getString("aenderungsdatum")));
         k.settitel(QString::fromStdString(resultSet->getString("titel")));
         k.setuntertitel(QString::fromStdString(resultSet->getString("untertitel")));
         k.setbeschreibung(QString::fromStdString(resultSet->getString("beschreibung")));
         k.setnotizen(QString::fromStdString(resultSet->getString("notizen")));
         k.setkommentar(QString::fromStdString(resultSet->getString("kommentar")));
         list.append(k);
      }
   }catch(SQLException &ex)
   {
      cout<<"Exception occurred"<<ex.getErrorCode()<<endl;
   }
   resultSet->close();
   pstmt->close();
   delete pstmt;
   delete resultSet;
   return list;
}
//Verbindung zum Server beenden
void SQLController::closeConnection()
{
   connection->close();
}
//Destruktor
SQLController::~SQLController()
{
   delete connection;
}
