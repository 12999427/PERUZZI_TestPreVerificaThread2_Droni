//
// Created by gvnnp on 15/03/2026.
//

#ifndef PERUZZI_TESTPREVERIFICATHREAD2_SINGOLODATO_H
#define PERUZZI_TESTPREVERIFICATHREAD2_SINGOLODATO_H

#include <string>

class SingoloDato {
public:
    SingoloDato();
    float GetLatitudine() const;
    float GetLongitudine() const;
    float GetAltitudine() const;
    bool GetIsDatoReady() const;
    void SetMeasures(float latitudine, float longitudine, float altitudine);
    std::string ToString() const;
private:
    float Latitudine;
    float Longitudine;
    float Altitudine;
    bool isReady;
};


#endif //PERUZZI_TESTPREVERIFICATHREAD2_SINGOLODATO_H