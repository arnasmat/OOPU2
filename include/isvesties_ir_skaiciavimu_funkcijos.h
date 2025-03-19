//
// Created by User on 2025-02-19.
//

#ifndef ISVESTIES_IR_SKAICIAVIMU_FUNKCIJOS_H
#define ISVESTIES_IR_SKAICIAVIMU_FUNKCIJOS_H

#include "pagalbines.h"
#include "rusiavimo_funkcijos.h"
#include "ivesties_pagalbines.h"

void failu_generavimas(int studentu_kiekis);
void isvesties_meniu(std::vector<Studentas>& studentai, const std::string &isvesties_failo_pavadinimas);
void isvestis(std::vector<Studentas>& studentai, std::ostream& isvesties_metodas, const int rodyti_pasirinkimas);
void studentu_kategorizacija(std::vector<Studentas>& studentai, const int rodyti_pasirinkimas, const int rusiuoti_pagal);

#include "template/isvesties_ir_skaiciavimu_funkcijos.tpp"

#endif //ISVESTIES_IR_SKAICIAVIMU_FUNKCIJOS_H
