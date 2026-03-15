//
// Created by gvnnp on 15/03/2026.
//

#include "MappaDati.h"

MappaDati::MappaDati(int nDroni) {
    for (int i = 0; i<nDroni; i++)
        dati[i] = SingoloDato();
}


void MappaDati::InserisciDato(int nDrone, float latitudine, float longitudine, float altitudine) {
    mutex_dati.lock();
    SingoloDato * sd = &dati.at(nDrone); //meglio at - evita di creare un nuovo oggetto se esso non è presente con quella chiave, il che porta raramente a crash
    //SingoloDato * sd = &dati[nDrone];
    sd->SetMeasures(latitudine, longitudine, altitudine);
    mutex_dati.unlock();
}

SingoloDato MappaDati::LeggiDati(int nDrone) {
    mutex_dati.lock();
    SingoloDato sd = dati.at(nDrone);
    //SingoloDato sd = dati[nDrone];
    mutex_dati.unlock();
    return sd;
}