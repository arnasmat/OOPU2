//
// Created by User on 2025-02-19.
//

#include <isvesties_ir_skaiciavimu_funkcijos.h>

//globalus kintamieji testavimo laikams
extern std::chrono::duration<double> testavimo_laikas;

void failu_generavimas(int studentu_kiekis){
    // std::vector<Studentas> studentai{};
    // studentai.reserve(studentu_kiekis);

    std::ostringstream output{""};
    std::uniform_int_distribution<int> random_kiekis(5, 15);

    int isvesties_vardo_ilgis{static_cast<int>(("Vardas"+ std::to_string(studentu_kiekis)).length() > 6 ? ("Vardas"+ std::to_string(studentu_kiekis)).length() + 2 : 8)};
    int isvesties_pavardes_ilgis{static_cast<int>(("Pavarde"+ std::to_string(studentu_kiekis)).length() > 7 ? ("Pavarde"+ std::to_string(studentu_kiekis)).length() + 2 : 8)};

    int pazymiu_kiekis = random_kiekis(mt);
    output<<std::left<<std::setw(isvesties_vardo_ilgis)
        <<"Vardas"
        <<std::left<<std::setw(isvesties_pavardes_ilgis)
        <<"Pavarde";
    for(int i=0; i<pazymiu_kiekis; i++) {
        //jei netingesiu paziuret kaip cia padaryt be to_str nes kazkaip negraziai kodas atrodo, bet su << susimaiso ju layoutas
        output<<std::left<<std::setw(5)<<"ND"+std::to_string(i+1);
    }
    output<<"Egz.\n";

    std::uniform_int_distribution<int> random_pazymys(1, 10);

    for(int i=0; i<studentu_kiekis; i++) {
        //Vardo ir pavardes generavimas failui
        output<<std::left<<std::setw(isvesties_vardo_ilgis)<<"Vardas" + std::to_string(i+1)
            <<std::left<<std::setw(isvesties_pavardes_ilgis)<<"Pavarde" + std::to_string(i+1);
        //Namu darbu ivertinimu generavimas
        for(int j=0; j<pazymiu_kiekis; j++) {
            output<<std::left<<std::setw(5)<< random_pazymys(mt);
        }
        //Egzamino rezultato generavimas
        output<<random_pazymys(mt)<<"\n";
    }

    std::ofstream isvesties_failas("../data/input/studentai_isvestis" + std::to_string(studentu_kiekis) + ".txt");
    isvesties_failas<<output.str();
    isvesties_failas.close();
}

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



void isvesties_meniu(std::vector<Studentas>& studentai, const std::string &isvesties_failo_pavadinimas) {

    std::cout<<"Kaip norite isvesti gautus rezultatus: \n"
            <<"1. I terminala\n"
            <<"2. I faila\n"
            <<"3. I du failus: islaike_studentai ir neislaike_studentai\n";
    int isvesties_pasirinkimas{ivesties_patikrinimas(1, 3)};

    std::cout<<"Pasirinkite ka norite matyti isvedant studentus: "<<"\n"
        <<"1. Vidurki\n"
        <<"2. Mediana\n"
        <<"3. Abu (ir vidurki, ir mediana)\n";
    int rodyti_pasirinkimas{ivesties_patikrinimas(1,3)};

    std::cout<<"Pasirinkite kaip norite rusiuoti: \n"
        <<"1. Rusiuoti pagal varda\n"
        <<"2. Rusiuoti pagal pavarde\n"
        <<"3. Rusiuoti pagal galutini pazymi pagal vidurki mazejanciai\n"
        <<"4. Rusiuoti pagal galutini pazymi pagal vidurki didejanciai\n"
        <<"5. Rusiuoti pagal galutini pazymi pagal mediana mazejanciai\n"
        <<"6. Rusiuoti pagal galutini pazymi pagal mediana didejanciai\n";

    int rusiavimo_pasirinkimas{ivesties_patikrinimas(1,6)};
    if(isvesties_pasirinkimas==1) {
        studentu_galutiniu_pazymiu_skaiciavimas(studentai);
        studentu_rusiavimas(studentai, rusiavimo_pasirinkimas);
        isvestis(studentai, std::cout, rodyti_pasirinkimas);
    } else if(isvesties_pasirinkimas==2){
        std::ofstream file(isvesties_failo_pavadinimas);
        if (file.is_open()) {
            studentu_galutiniu_pazymiu_skaiciavimas(studentai);
            studentu_rusiavimas(studentai, rusiavimo_pasirinkimas);
            isvestis(studentai, file, rodyti_pasirinkimas);
            file.close();
        } else {
            std::cerr << "Nepavyko atidaryti isvesties failo \n";
        }
    } else if(isvesties_pasirinkimas==3) {
        studentu_kategorizacija(studentai, rodyti_pasirinkimas, rusiavimo_pasirinkimas);
    }
}

void isvestis(std::vector<Studentas>& studentai, std::ostream& isvesties_metodas, const int rodyti_pasirinkimas) {
    int longest_name{0};
    int longest_surname{0};
    for(auto &i: studentai) {
        if(i.getVardas().length() > longest_name) {
            longest_name = static_cast<int>(i.getVardas().length());
        }
        if(i.getPavarde().length() > longest_surname) {
            longest_surname = static_cast<int>(i.getPavarde().length());
        }
    }

    int isvesties_pavardes_ilgis{((longest_surname > 7 ? longest_surname + 2 : 8))};
    int isvesties_vardo_ilgis{((longest_name > 6 ? longest_name + 2 : 8))};

    //Konvertuoti visa isvesti i viena eilute, kad ji butu greitesne.
    std::stringstream isvestis{};

    isvestis<<std::left<<std::setw(isvesties_pavardes_ilgis)<<"Pavarde"
    <<std::left<<std::setw(isvesties_vardo_ilgis)<<"Vardas";
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
            isvestis << std::setw(isvesties_pavardes_ilgis) << i.getPavarde()
                   << std::setw(isvesties_vardo_ilgis) << i.getVardas()
                   << std::setw(17) << std::left << i.getGalutinisVidurkis() << "\n";
        }
    } else if (rodyti_pasirinkimas == 2) {
        for (auto& i : studentai) {
            isvestis << std::setw(isvesties_pavardes_ilgis) << i.getPavarde()
                   << std::setw(isvesties_vardo_ilgis) << i.getVardas()
                   << std::setw(17) << std::left << i.getGalutinisMediana() << "\n";
        }
    } else if (rodyti_pasirinkimas == 3) {
        for (auto& i : studentai) {
            isvestis << std::setw(isvesties_pavardes_ilgis) << i.getPavarde()
                   << std::setw(isvesties_vardo_ilgis) << i.getVardas()
                   << std::setw(17) << std::left << i.getGalutinisVidurkis() << "   "
                   << std::setw(17) << std::left << i.getGalutinisMediana() << "\n";
        }
    }
    try {
        isvesties_metodas << isvestis.str();
    } catch(std::exception& e) {
        std::cerr<<"Ivyko klaida isvedant duomenis: "<<e.what()<<"\n";
    }
}


void studentu_kategorizacija(std::vector<Studentas>& studentai, const int rodyti_pasirinkimas, const int rusiuoti_pagal) {
    //ekvivalentu "kietekams" ir "vargsiukams", tiesiog formaliau pavadinta
    std::vector<Studentas> islaike_studentai{};
    std::vector<Studentas> neislaike_studentai{};

    studentu_galutiniu_pazymiu_skaiciavimas(studentai);
    if(rusiuoti_pagal==1 || rusiuoti_pagal==2) {
        std::cout<<"Studentu kategorizacija automatiskai vykdoma pagal vidurki, nes jusu pasirinkimas netinkamas kategorizacijai";
        studentu_rusiavimas(studentai, 3);
    } else {
        studentu_rusiavimas(studentai, rusiuoti_pagal);
    }

    if(rusiuoti_pagal == 3) {
        auto partition_iteratorius = std::partition_point(
            studentai.begin(), studentai.end(),
            [](const Studentas& studentas) {return studentas.getGalutinisVidurkis()>=5.0f;}
            );
            islaike_studentai.assign(studentai.begin(), partition_iteratorius);
            neislaike_studentai.assign(partition_iteratorius, studentai.end());
    } else if(rusiuoti_pagal == 4) {
        auto partition_iteratorius = std::partition_point(
            studentai.begin(), studentai.end(),
            [](const Studentas& studentas) {return studentas.getGalutinisVidurkis()<=5.0f;}
            );
        neislaike_studentai.assign(studentai.begin(), partition_iteratorius);
        islaike_studentai.assign(partition_iteratorius, studentai.end());
    }else if(rusiuoti_pagal==5){
        auto partition_iteratorius = std::partition_point(
            studentai.begin(), studentai.end(),
            [](const Studentas& studentas) {return studentas.getGalutinisMediana()>=5.0f;}
            );
            islaike_studentai.assign(studentai.begin(), partition_iteratorius);
            neislaike_studentai.assign(partition_iteratorius, studentai.end());
    } else if(rusiuoti_pagal==6){
        auto partition_iteratorius = std::partition_point(
            studentai.begin(), studentai.end(),
            [](const Studentas& studentas) {return studentas.getGalutinisMediana()<=5.0f;}
            );
        neislaike_studentai.assign(studentai.begin(), partition_iteratorius);
        islaike_studentai.assign(partition_iteratorius, studentai.end());
        neislaike_studentai.shrink_to_fit();
        islaike_studentai.shrink_to_fit();
        studentai.clear();
    }

    try {
        std::ofstream islaike_output("../data/output/islaike_studentai.txt");
        isvestis(islaike_studentai, islaike_output, rodyti_pasirinkimas);
        islaike_output.close();
        std::ofstream neislaike_output("../data/output/neislaike_studentai.txt");
        isvestis(neislaike_studentai, neislaike_output, rodyti_pasirinkimas);
        neislaike_output.close();
    } catch(std::exception& e) {
        std::cerr<<"Ivyko klaida isvedant i failus failus: "<<e.what()<<"\n";
    }
}
//Void isvestis ir isvesties_meniu implementuota .tpp faile
