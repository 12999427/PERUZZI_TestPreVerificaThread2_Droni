//
// Created by gvnnp on 15/03/2026.
//

#include "SingoloDato.h"


SingoloDato::SingoloDato() {
    isReady = false;
}

float SingoloDato::GetLatitudine() const {
    return Latitudine;
}
float SingoloDato::GetLongitudine() const {
    return Longitudine;
}
float SingoloDato::GetAltitudine() const {
    return Altitudine;
}

bool SingoloDato::GetIsDatoReady() const {
    return isReady;
}

void SingoloDato::SetMeasures(float latitudine, float longitudine, float altitudine) {
    Altitudine = altitudine;
    Longitudine = longitudine;
    Latitudine = latitudine;
    isReady = true;
}

std::string SingoloDato::ToString() const {
    return std::to_string(Latitudine) + ", " + std::to_string(Longitudine) + ", " + std::to_string(Altitudine);
}
