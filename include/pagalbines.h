#ifndef PAGALBINES_H
#define PAGALBINES_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <fstream>
#include <chrono>
#include <filesystem>
#include <list>
#include <deque>
namespace fs = std::filesystem;

class Studentas {
private:
    std::string vardas_{}, pavarde_{};
    std::vector<uint8_t> pazymiai_{};
    uint8_t egzamino_rezultatas_{};
    float galutinis_vidurkis_{};
    float galutinis_mediana_{};
public:
    // Konstruktorius ir Destrultorius
    Studentas(std::string vardas, std::string pavarde, std::vector<uint8_t> pazymiai, uint8_t egzamino_rezultatas)
    : vardas_(std::move(vardas)), pavarde_(std::move(pavarde)), pazymiai_(std::move(pazymiai)), egzamino_rezultatas_(egzamino_rezultatas) {}
    Studentas() = default;
    ~Studentas() {
        pazymiai_.clear();
    }

    // Seteriai
    void setVardas(const std::string& vardas) {vardas_ = vardas;}
    void setPavarde(const std::string& pavarde) {pavarde_ = pavarde;}
    void setEgzaminoRezultatas(const unsigned int egzamino_rezultatas) {egzamino_rezultatas_ = egzamino_rezultatas;}
    void setGalutinisVidurkis(const float galutinis_vidurkis) {galutinis_vidurkis_ = galutinis_vidurkis;}
    void setGalutinisMediana(const float galutinis_mediana) {galutinis_mediana_ = galutinis_mediana;}

    // Geteriai
    [[nodiscard]] std::string getVardas () const {return vardas_;}
    [[nodiscard]] std::string getPavarde () const {return pavarde_;}
    [[nodiscard]] std::vector<uint8_t> getPazymiai() const {return pazymiai_;}
    [[nodiscard]] uint8_t getEgzaminoRezultatas() const {return egzamino_rezultatas_;}
    [[nodiscard]] float getGalutinisVidurkis() const {return galutinis_vidurkis_;}
    [[nodiscard]] float getGalutinisMediana() const {return galutinis_mediana_;}

    // Kitos reikalingos funkcijos
    void addPazymys(const uint8_t pazymys) {pazymiai_.push_back(pazymys);}
    void removePaskutinisPazymys() {pazymiai_.pop_back();}};
};

extern std::random_device rd;
extern std::mt19937 mt;

#endif // PAGALBINES_H