string bestellungsId;
string dokumentId;

SELECT * FROM bestellung, ausleihender WHERE bestellung.bestellungid = bestellungsId AND bestellung.ausleihenderid = ausleihender.ausleihenderid; 

switch (SELECT bearbeitungsstatus FROM bestellung WHERE bestellungid = bestellungsId;)
{
    //Wie lauten die jeweiligen Werte innerhalb der Datenbank?
    case : status = angefragt;
    case : status = inBearbeitung; 
    case : status = versendet;
    case : status = abgelehnt;   
}

SELECT * FROM dokument WHERE documentid = dokumentID;

/*dokumentAutoren*/ SELECT autor FROM document_autor, autor WHERE dokumentid = dokumentId AND dokument_autor.autorid = autor,autorid; 

/*sammelbandAutoren*/ SELECT autor FROM sammelband_autor, autor WHERE dokumentid = dokumentId AND sammelband_autor.autorid = autor.autorid; 
