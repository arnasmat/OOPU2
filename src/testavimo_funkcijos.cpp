//
// Created by User on 2025-03-06.
//

#include <testavimo_funkcijos.h>


void testavimo_rezimas(bool& praejo) {
        std::cout<<"Ka noretumete testuoti: \n"
                <<"1. Failu kurimo greiti\n"
                <<"2. Failu nuskaitymo greiti (su senos versijos testiniais failais)\n"
                <<"3. Failu nuskaitymo, rusiavimo, kategorizavimo ir isvesties greiti\n";
        praejo=false;
        int testavimo_pasirinkimas{ivesties_patikrinimas(1,3)};
        std::vector<int> kiekiai = {1000, 10000, 100000, 1000000, 10000000};
        switch(testavimo_pasirinkimas) {
            case 1:
                failu_kurimo_testavimas(kiekiai);
            break;
            case 2:
                ivesties_testavimas(praejo);
            break;
            case 3:
                konteineriu_pasirinkimas_testavimui(kiekiai, praejo);
            break;
            default:
                break;
        }
}

void ivesties_testavimas(bool& praejo) {
    try {
    fs::path testavimo_failas{pasirinkti_faila_is_testiniu()};
    std::cout<<"Iveskite kiek testu norite daryti (nuo 1 iki 100): \n";
    int testu_kiekis{ivesties_patikrinimas(1,100)};
    praejo=false;

    std::chrono::duration<double> nuskaitymo_laiku_suma{0};

        std::vector<Studentas> test_studentai;
        for(int i=0; i<testu_kiekis; i++) {
            auto nuskaitymo_laikas = std::chrono::high_resolution_clock::now();
            studentu_ivestis_is_failo(test_studentai, testavimo_failas, praejo);
            std::chrono::duration<double> sugaistas_laikas = std::chrono::high_resolution_clock::now() - nuskaitymo_laikas;
            nuskaitymo_laiku_suma+=sugaistas_laikas;
            std::cout<<"Failo nuskaitymas uztruko: "<<sugaistas_laikas.count()<<"\n";
            test_studentai.clear();
        }
        std::cout<<"Vidutinis failo skaitymo laikas: "<<nuskaitymo_laiku_suma.count()/testu_kiekis<<"\n";
    } catch(std::exception& e) {
        std::cerr<<"Ivyko klaida testuojant nuskaityma: "<<e.what()<<"\n";
    }
}

void failu_kurimo_testavimas(const std::vector<int>& kiekiai) {
    for(auto &i: kiekiai) {
        std::chrono::duration<double> testavimo_laikas{0};
        for(int j=0; j<3; j++) {
            auto nuskaitymo_laikas = std::chrono::high_resolution_clock::now();
            failu_generavimas(i);
            auto sugaistas_laikas = std::chrono::high_resolution_clock::now() - nuskaitymo_laikas;
            std::cout<<"Failo su "<<i<<" studentais generavimas truko: "<<std::chrono::duration<double>(sugaistas_laikas).count()<<"\n";
            testavimo_laikas+=sugaistas_laikas;
        }
        std::cout<<i << " vidurkis: " << testavimo_laikas.count()/3 <<"\n";
    }
}

void konteineriu_pasirinkimas_testavimui(const std::vector<int>& kiekiai, bool& praejo) {
    std::vector<Studentas> temp_studentai{};
    nuskaitymo_ir_isvesties_testavimas(temp_studentai, kiekiai, praejo);
}


void studentu_kategorizacija_testavimas(std::vector<Studentas>& studentai, const int rodyti_pasirinkimas, const int rusiuoti_pagal, std::chrono::duration<double>& testavimo_laikas, const int i) {
    //ekvivalentu "kietekams" ir "vargsiukams", tiesiog formaliau pavadinta
    std::vector<Studentas> islaike_studentai{};
    std::vector<Studentas> neislaike_studentai{};

    auto nuskaitymo_laikas = std::chrono::high_resolution_clock::now();
    studentu_galutiniu_pazymiu_skaiciavimas(studentai);
    studentu_rusiavimas(studentai, rusiuoti_pagal);
    auto sugaistas_laikas = std::chrono::high_resolution_clock::now() - nuskaitymo_laikas;
    // std::cout<<i<<" Irasu rusiavimas truko: "<<std::chrono::duration<double>(sugaistas_laikas).count()<<"\n";
    testavimo_laikas+=sugaistas_laikas;


    nuskaitymo_laikas = std::chrono::high_resolution_clock::now();
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

    sugaistas_laikas = std::chrono::high_resolution_clock::now() - nuskaitymo_laikas;
    // std::cout<<i<<" Irasu kategorizavimas istrinant originalu vektoriu truko: "<<std::chrono::duration<double>(sugaistas_laikas).count()<<"\n";
    testavimo_laikas+=sugaistas_laikas;

    try {
        nuskaitymo_laikas = std::chrono::high_resolution_clock::now();
        std::ofstream islaike_output("../data/output/islaike_studentai.txt");
        isvestis(islaike_studentai, islaike_output, rodyti_pasirinkimas);
        islaike_output.close();
        sugaistas_laikas = std::chrono::high_resolution_clock::now() - nuskaitymo_laikas;
        std::cout<<i<<" Irasu islaikiusiuju irasymo i faila laikas: "<<std::chrono::duration<double>(sugaistas_laikas).count()<<"\n";
        testavimo_laikas+=sugaistas_laikas;

        nuskaitymo_laikas = std::chrono::high_resolution_clock::now();
        std::ofstream neislaike_output("../data/output/neislaike_studentai.txt");
        isvestis(neislaike_studentai, neislaike_output, rodyti_pasirinkimas);
        neislaike_output.close();
        sugaistas_laikas = std::chrono::high_resolution_clock::now() - nuskaitymo_laikas;
        std::cout<<i<<" Irasu neislaikiusiuju irasymo i faila laikas: "<<std::chrono::duration<double>(sugaistas_laikas).count()<<"\n";
        testavimo_laikas+=sugaistas_laikas;
    } catch(std::exception& e) {
        std::cerr<<"Ivyko klaida isvedant i failus failus: "<<e.what()<<"\n";
    }
}

void nuskaitymo_ir_isvesties_testavimas(std::vector<Studentas>& temp_studentai, const std::vector<int>& kiekiai, bool& praejo){
    try {
        for(auto &i: kiekiai) {
            std::chrono::duration<double> testavimo_laiku_suma{0};
            for(int j=0; j<3; j++) {
                std::chrono::duration<double> testavimo_laikas{0};
                fs::path failo_pavadinimas{"../data/input/studentai_isvestis" + std::to_string(i) + ".txt"};
                auto nuskaitymo_laikas = std::chrono::high_resolution_clock::now();
                studentu_ivestis_is_failo(temp_studentai, failo_pavadinimas, praejo);
                auto sugaistas_laikas = std::chrono::high_resolution_clock::now() - nuskaitymo_laikas;
                // std::cout<<"Failo su "<<i<<" studentais nuskaitymas truko: "<<std::chrono::duration<double>(sugaistas_laikas).count()<<"\n";
                testavimo_laikas+=sugaistas_laikas;
                //Greiciausias vis tiek senas metodas lol
                studentu_kategorizacija_testavimas(temp_studentai, 3, 3,testavimo_laikas, i);
                // studentu_kategorizacija_1_strategija_testavimas(temp_studentai, 3, 3,testavimo_laikas, i);
                // studentu_kategorizacija_2_strategija_testavimas(temp_studentai, 3, 3,testavimo_laikas, i);
                // studentu_kategorizacija_3_strategija_testavimas(temp_studentai, 3, 3,testavimo_laikas, i);
                // std::cout<<i<<" irasu testavimo laikas: "<<testavimo_laikas.count()<<"\n";
                testavimo_laiku_suma +=testavimo_laikas;
                temp_studentai.clear();
            }
            std::cout<<i << " vidurkis: " << testavimo_laiku_suma.count()/3 <<"\n";
            // std::cout<<"\n---------------------------------------------------\n";
        }
    }
    catch(std::exception &e) {
        std::cerr<<"Ivyko klaida testuojant "<<e.what()<<"\n";
        std::cerr<<"Galbut testavimo failai nesugeneruoti? Pabandykite paleisti testavimo failu kurima. \n";
    }
}
