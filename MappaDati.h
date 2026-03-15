//
// Created by gvnnp on 15/03/2026.
//

#ifndef PERUZZI_TESTPREVERIFICATHREAD2_MAPPADATI_H
#define PERUZZI_TESTPREVERIFICATHREAD2_MAPPADATI_H
#include <map>
#include <mutex>
#include <vector>

#include "SingoloDato.h"


class MappaDati {
public:
    MappaDati(int numDroni);

    void InserisciDato(int nDrone, float latitudine, float longitudine, float altitudine);
    SingoloDato LeggiDati(int nDrone);
private:
    std::mutex mutex_dati;
    //evito di usare una std::map in casi come questi dove la dimensione è fissa, avrei potuto usare un array o un vector
    std::map<int, SingoloDato> dati;
};


#endif //PERUZZI_TESTPREVERIFICATHREAD2_MAPPADATI_H