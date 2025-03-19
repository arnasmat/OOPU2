
inline void studentu_rusiavimas(std::vector<Studentas>& studentai, int rusiavimo_pasirinkimas) {
    auto comparator_vardas = [](const Studentas &a, const Studentas &b) {
        return a.getVardas() < b.getVardas();
    };
    auto comparator_pavarde = [](const Studentas &a, const Studentas &b) {
        return a.getPavarde() < b.getPavarde();
    };
    auto comparator_vidurkis_asc = [](const Studentas &a, const Studentas &b) {
        return a.getGalutinisVidurkis() < b.getGalutinisVidurkis();
    };
    auto comparator_vidurkis_desc = [](const Studentas &a, const Studentas &b) {
        return a.getGalutinisVidurkis() > b.getGalutinisVidurkis();
    };
    auto comparator_mediana_asc = [](const Studentas &a, const Studentas &b) {
        return a.getGalutinisMediana() < b.getGalutinisMediana();
    };
    auto comparator_mediana_desc = [](const Studentas &a, const Studentas &b) {
        return a.getGalutinisMediana() > b.getGalutinisMediana();
    };

    switch(rusiavimo_pasirinkimas) {
        case 1:
                std::sort(studentai.begin(), studentai.end(), comparator_vardas);
            break;
        case 2:
                std::sort(studentai.begin(), studentai.end(), comparator_pavarde);
            break;
        case 3:
                std::sort(studentai.begin(), studentai.end(), comparator_vidurkis_desc);
            break;
        case 4:
                std::sort(studentai.begin(), studentai.end(), comparator_vidurkis_asc);
            break;
        case 5:
                std::sort(studentai.begin(), studentai.end(), comparator_mediana_desc);
            break;
        case 6:
                std::sort(studentai.begin(), studentai.end(), comparator_mediana_asc);
            break;
        default:
            break;
    }
}

inline void studentu_galutiniu_pazymiu_skaiciavimas(std::vector<Studentas>& studentai) {
    //Patikrina, ar paskutinio studento galutinis pazymys apskaiciuotas, kad nebutu pertekliniu skaiciavimu
    if(studentai.back().getGalutinisVidurkis() == 0 || studentai.back().getGalutinisMediana() == 0) {
        for(auto &i: studentai) {
            i.calculateGalutinisVidurkis();
            i.calculateGalutinisMediana();
        }
    }
}
