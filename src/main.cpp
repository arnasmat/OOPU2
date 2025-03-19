//
// Created by User on 2025-02-10.
//

#include <pagalbines.h>
#include <ivesties_funkcijos.h>
#include <isvesties_ir_skaiciavimu_funkcijos.h>
#include <failu_pasirinkimo_funkcijos.h>
#include <ivesties_pagalbines.h>
#include <testavimo_funkcijos.h>

int main() {
    const std::string isvesties_failo_pavadinimas{"../data/output/rezultatai.txt"};
    fs::path ivesties_failas{"../data/input/kursiokai.txt"};

    std::vector<Studentas> studentai;
    while(true){
        int menu{meniu(ivesties_failas)};
        bool praejo{true};
        switch(menu) {
            case 1:
                studentu_ivestis(studentai);
            break;
            case 2:
                studentu_ivestis_random_2(studentai);
            break;
            case 3:
                studentu_ivestis_random_3(studentai);
            break;
            case 4:
                studentu_ivestis_is_failo(studentai, ivesties_failas, praejo);
            break;
            case 5:
                ivesties_failas = pasirinkti_faila_is_visu();
                praejo = false;
            break;
            case 6: {
                std::cout<<"Iveskite studentu kieki generuojame faile: \n";
                int studentu_kiekis{ivesties_patikrinimas(1,10000000)};
                failu_generavimas(studentu_kiekis);
                praejo = false;
                break;
            }
            case 7: {
                testavimo_rezimas(praejo);
                break;
            }
            default:
                return 0;
        }
        if(praejo)
            isvesties_meniu(studentai, isvesties_failo_pavadinimas);

    }

}

