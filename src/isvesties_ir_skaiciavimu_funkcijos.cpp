//
// Created by User on 2025-02-19.
//

#include "../include/isvesties_ir_skaiciavimu_funkcijos.h"
#include "../include/ivesties_pagalbines.h"

float galutinis_pazymys_vidurkis(Studentas &studentas) {
    unsigned int pazymiu_suma{0};
    if(studentas.pazymiai.empty()) return 0;;
    for(const auto &i: studentas.pazymiai) {
        pazymiu_suma+=i;
    }
    return pazymiu_suma / studentas.pazymiai.size() * 0.4 + studentas.egzamino_rezultatas * 0.6;
}

float galutinis_pazymys_mediana(Studentas &studentas) {
    float mediana{0};
    if(studentas.pazymiai.empty()) return 0;
    std::sort(studentas.pazymiai.begin(), studentas.pazymiai.end());
    if(studentas.pazymiai.size()%2==0) {
        mediana = (studentas.pazymiai[studentas.pazymiai.size()/2.0] + studentas.pazymiai[studentas.pazymiai.size()/2.0-1])/2.0;
    } else {
        mediana = studentas.pazymiai[(studentas.pazymiai.size()/2.0)];
    }
    return mediana*0.4 + studentas.egzamino_rezultatas*0.6;
}

void isvesties_meniu(std::vector<Studentas>& studentai, const std::string &isvesties_failo_pavadinimas) {
    std::cout<<"Kaip norite isvesti gautus rezultatus: \n"
            <<"1. I terminala\n"
            <<"2. I faila\n";
    int isvesties_pasirinkimas{ivesties_patikrinimas(1, 2)};
    if(isvesties_pasirinkimas==1) {
        isvestis(studentai, std::cout);
    } else {
        std::ofstream file(isvesties_failo_pavadinimas);
        if (file.is_open()) {
            isvestis(studentai, file);
            file.close();
        } else {
            std::cerr << "Nepavyko atidaryti isvesties failo \n";
        }
    }
}

void isvestis(std::vector<Studentas>& studentai, std::ostream& isvesties_metodas) {
    std::cout<<"Pasirinkite ka norite matyti isvedant studentus: "<<"\n"
            <<"1. Vidurki\n"
            <<"2. Mediana\n"
            <<"3. Abu (ir vidurki, ir mediana)\n";
    int rodyti_pasirinkimas{ivesties_patikrinimas(1,3)};

    std::cout<<"------------------------------------------------------------\n";

    for(auto &i: studentai) {
        i.galutinis_vidurkis = galutinis_pazymys_vidurkis(i);
        i.galutinis_mediana = galutinis_pazymys_mediana(i);
    }

    std::cout<<"Pasirinkite kaip norite rusiuoti: \n"
            <<"1. Rusiuoti pagal varda\n"
            <<"2. Rusiuoti pagal pavarde\n"
            <<"3. Rusiuoti pagal galutini pazymi pagal vidurki mazejanciai\n"
            <<"4. Rusiuoti pagal galutini pazymi pagal vidurki didejanciai\n"
            <<"5. Rusiuoti pagal galutini pazymi pagal mediana mazejanciai\n"
            <<"6. Rusiuoti pagal galutini pazymi pagal mediana didejanciai\n";
    int rusiavimo_pasirinkimas{ivesties_patikrinimas(1,6)};

    switch(rusiavimo_pasirinkimas) {
        case 1:
            std::sort(studentai.begin(), studentai.end(), [](const Studentas &a, const Studentas &b) {
                return a.vardas < b.vardas;
            }); break;
        case 2:
            std::sort(studentai.begin(), studentai.end(), [](const Studentas &a, const Studentas &b) {
                return a.pavarde < b.pavarde;
            }); break;
        case 3:
            std::sort(studentai.begin(), studentai.end(), [](const Studentas &a, const Studentas &b) {
                return a.galutinis_vidurkis > b.galutinis_vidurkis;
            }); break;
        case 4:
            std::sort(studentai.begin(), studentai.end(), [](const Studentas &a, const Studentas &b) {
                return a.galutinis_vidurkis < b.galutinis_vidurkis;
            }); break;
        case 5:
            std::sort(studentai.begin(), studentai.end(), [](const Studentas &a, const Studentas &b) {
            return a.galutinis_mediana > b.galutinis_mediana;
            }); break;
        case 6:
            std::sort(studentai.begin(), studentai.end(), [](const Studentas &a, const Studentas &b) {
            return a.galutinis_mediana < b.galutinis_mediana;
            }); break;
    }

    int longest_name{0};
    int longest_surname{0};
    for(auto &i: studentai) {
        if(i.vardas.length() > longest_name) {
            longest_name = i.vardas.length();
        }
        if(i.pavarde.length() > longest_surname) {
            longest_surname = i.pavarde.length();
        }
    }

    //Konvertuoti visa isvesti i viena eilute, kad ji butu greitesne.
    std::stringstream isvestis{};

    isvestis<<std::left<<std::setw(longest_surname > 7 ? longest_surname+2 : 8)<<"Pavarde"
    <<std::left<<std::setw(longest_name > 6 ? longest_name+2 : 8)<<"Vardas";
    if(rodyti_pasirinkimas==1 || rodyti_pasirinkimas==3) {
        isvestis<<std::setw(17)<<std::left<<"Galutinis (Vid.)";
    }
    if(rodyti_pasirinkimas==2 || rodyti_pasirinkimas==3) {
        isvestis<<std::setw(17)<<std::left<<"Galutinis (Med.)";
    }
    isvestis<<"\n"
              "------------------------------------------------------------\n";

    isvestis << std::left<<std::fixed << std::setprecision(2);

    if (rodyti_pasirinkimas == 1) {
        for (auto& i : studentai) {
            isvestis << std::setw(longest_surname > 7 ? longest_surname + 2 : 8) << i.pavarde
                   << std::setw(longest_name > 6 ? longest_name + 2 : 8) << i.vardas
                   << std::setw(17) << std::left << i.galutinis_vidurkis << "\n";
        }
    } else if (rodyti_pasirinkimas == 2) {
        for (auto& i : studentai) {
            isvestis << std::setw(longest_surname > 7 ? longest_surname + 2 : 8) << i.pavarde
                   << std::setw(longest_name > 6 ? longest_name + 2 : 8) << i.vardas
                   << std::setw(17) << std::left << i.galutinis_mediana << "\n";
        }
    } else if (rodyti_pasirinkimas == 3) {
        for (auto& i : studentai) {
            isvestis << std::setw(longest_surname > 7 ? longest_surname + 2 : 8) << i.pavarde
                   << std::setw(longest_name > 6 ? longest_name + 2 : 8) << i.vardas
                   << std::setw(17) << std::left << i.galutinis_vidurkis << "   "
                   << std::setw(17) << std::left << i.galutinis_mediana << "\n";
        }
    }
    try {
        isvesties_metodas << isvestis.str();
    } catch(std::exception& e) {
        std::cerr<<"Ivyko klaida isvedant duomenis: "<<e.what()<<"\n";
    }
}