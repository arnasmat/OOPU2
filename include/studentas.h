//
// Created by User on 2025-03-19.
//

#ifndef STUDENTAS_H
#define STUDENTAS_H

#include "pagalbines.h"

class Studentas {
private:
    std::string vardas_{}, pavarde_{};
    std::vector<int> pazymiai_{};
    int egzamino_rezultatas_{};
    float galutinis_vidurkis_{};
    float galutinis_mediana_{};
public:
    // Konstruktorius ir Destrultorius
    Studentas(std::string vardas, std::string pavarde, std::vector<int> pazymiai, int egzamino_rezultatas)
    : vardas_(std::move(vardas)), pavarde_(std::move(pavarde)), pazymiai_(std::move(pazymiai)), egzamino_rezultatas_(egzamino_rezultatas) {}
    Studentas() = default;
    ~Studentas() {
        pazymiai_.clear();
    }

    // Seteriai
    void setVardas(const std::string& vardas) {vardas_ = vardas;}
    void setPavarde(const std::string& pavarde) {pavarde_ = pavarde;}
    void setEgzaminoRezultatas(const unsigned int egzamino_rezultatas) {egzamino_rezultatas_ = egzamino_rezultatas;}
    /*void setGalutinisVidurkis(const float galutinis_vidurkis) {galutinis_vidurkis_ = galutinis_vidurkis;}
    void setGalutinisMediana(const float galutinis_mediana) {galutinis_mediana_ = galutinis_mediana;}*/

    // Geteriai
    [[nodiscard]] std::string getVardas () const {return vardas_;}
    [[nodiscard]] std::string getPavarde () const {return pavarde_;}
    [[nodiscard]] std::vector<int> getPazymiai() const {return pazymiai_;}
    [[nodiscard]] int getEgzaminoRezultatas() const {return egzamino_rezultatas_;}
    [[nodiscard]] float getGalutinisVidurkis() const {return galutinis_vidurkis_;}
    [[nodiscard]] float getGalutinisMediana() const {return galutinis_mediana_;}

    // Kitos reikalingos funkcijos
    void addPazymys(const int pazymys) {pazymiai_.push_back(pazymys);}
    void removePaskutinisPazymys() {pazymiai_.pop_back();}

    void calculateGalutinisVidurkis();
    void calculateGalutinisMediana();
};




#endif //STUDENTAS_H
