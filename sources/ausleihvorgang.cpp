#include "../headers/ausleihvorgang.h"

Ausleihvorgang::Ausleihvorgang(string bestellungsId, Ausleihender ausleihender, Status status,
                               Katalogliste medien, tm datum, tm datumFertig)
{
        this->bestellungsId = bestellungsId;
        this->ausleihender = ausleihender;
        this->status = status;
        this->medien = medien;
        this->datum = datum;
        this->datumFertig = datumFertig;
}

