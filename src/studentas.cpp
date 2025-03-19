//
// Created by User on 2025-03-19.
//

#include "studentas.h"

void Studentas::calculateGalutinisVidurkis() {
    int pazymiu_suma{0};
    if(this->getPazymiai().empty()) {
        this->galutinis_vidurkis_ = 0;
        return;
    }
    for(const auto &i: this->getPazymiai()) {
        pazymiu_suma+=i;
    }
    this->galutinis_vidurkis_ = pazymiu_suma / this->getPazymiai().size() * 0.4f + this->egzamino_rezultatas_ * 0.6f;
}

void Studentas::calculateGalutinisMediana() {
    float mediana{0};
    std::vector<int> pazymiai = this->getPazymiai();
    std::sort(pazymiai.begin(), pazymiai.end());

    if (pazymiai.size() % 2 == 0) {
        mediana = static_cast<float>(pazymiai[pazymiai.size() / 2] + pazymiai[pazymiai.size() / 2 - 1]) / 2.0f;
    } else {
        mediana = static_cast<float>(pazymiai[pazymiai.size() / 2]);
    }

    this->galutinis_mediana_ = mediana * 0.4f + static_cast<float>(this->getEgzaminoRezultatas()) * 0.6f;
}
