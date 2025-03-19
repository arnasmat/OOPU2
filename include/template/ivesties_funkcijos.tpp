
template <typename Container>
void studentu_ivestis(Container& studentai) {
    while(true) {
        Studentas laikinas_studentas;

        vardu_ivestis(studentai, laikinas_studentas);

        if(laikinas_studentas.getVardas() == "n" && !studentai.empty()) {
            return;
        }

        std::cout<<"Iveskite pazymius (jeigu norite baigti pazymiu ivedima, iveskite -1): ";
        uint8_t pazymys{0};
        std::vector<uint8_t> pazymiai{};
        while(true) {
            pazymys = ivesties_patikrinimas(1,10, -1);
            while(pazymys == -1 && pazymiai.empty()) {
                std::cout << "Iveskite bent viena pazymi: ";
                pazymys = ivesties_patikrinimas(1, 10);
            }
            if(pazymys == -1)
                break;
            laikinas_studentas.addPazymys(pazymys);
        }
        std::cout<<"Iveskite egzamino rezultata: ";
        laikinas_studentas.setEgzaminoRezultatas(ivesties_patikrinimas(1, 10));
        studentai.push_back(laikinas_studentas);
    }
}

template <typename Container>
void studentu_ivestis_random_2(Container& studentai) {
    while(true) {
        Studentas laikinas_studentas{};

        vardu_ivestis(studentai, laikinas_studentas);

        if(laikinas_studentas.getVardas() == "n" && !studentai.empty()) {
            return;
        }

        random_pazymiu_generavimas(laikinas_studentas);

        studentai.push_back(laikinas_studentas);
    }
}

template <typename Container>
void studentu_ivestis_random_3(Container& studentai) {
    try {
        //Random vardu generavimas
        std::vector<std::string> vyriski_vardai = {"Jonas", "Petras", "Antanas", "Kazys", "Tomas", "Darius", "Marius", "Rokas", "Mantas", "Mantas"};
        std::vector<std::string> moteriski_vardai = {"Ona", "Petra", "Antanina", "Kazyte", "Toma", "Darija", "Marija", "Rokas", "Mante", "Mante"};

        std::vector<std::string> vyriskos_pavardes = {"Jonaitis", "Petraitis", "Antanaitis", "Kazaitis", "Tomaitis", "Dariukaitis", "Mariukaitis", "Rokaitis", "Mantaitis"};
        std::vector<std::string> moteriskos_pavardes = {"Jonaitiene", "Petraitiene", "Antanaitiene", "Kazaitiene", "Tomaitiene", "Dariukaite", "Mariukaite", "Rokaite", "Mantaite"};

        std::uniform_int_distribution<int> random(1, 10);
        //Inicializuoju random reiskme kiekvienam, jeigu keisis ju dydziai ateityje.
        //Pasiklausti, ar teisingai esu padares, nes kazkaip labai daznai generuoja identiska varda kelis kartus is eiles.
        std::uniform_int_distribution<int> random_vyriskas_vardas(0, static_cast<int>(vyriski_vardai.size())-1);
        std::uniform_int_distribution<int> random_moteriskas_vardas(0, static_cast<int>(moteriski_vardai.size())-1);
        std::uniform_int_distribution<int> random_vyriska_pavarde(0, static_cast<int>(vyriskos_pavardes.size())-1);
        std::uniform_int_distribution<int> random_moteriska_pavarde(0, static_cast<int>(moteriskos_pavardes.size())-1);

        int zmoniu_kiekis = random(mt);
        for(int i=0; i<zmoniu_kiekis; i++) {
            Studentas laikinas_studentas{};
            if(random(mt)%2 == 1) {
                laikinas_studentas.setVardas(vyriski_vardai[random_vyriskas_vardas(mt)]);
                laikinas_studentas.setPavarde(vyriskos_pavardes[random_vyriska_pavarde(mt)]);
            } else {
                laikinas_studentas.setVardas(moteriski_vardai[random_moteriskas_vardas(mt)]);
                laikinas_studentas.setPavarde(moteriskos_pavardes[random_moteriska_pavarde(mt)]);
            }

            random_pazymiu_generavimas(laikinas_studentas);

            studentai.push_back(laikinas_studentas);
        }
    } catch(std::exception& e){
        std::cerr<<"Ivyko klaida generuojant studentus: "<<e.what()<<"\n";
    }
}

template <typename Container>
void studentu_ivestis_is_failo(Container& studentai, const fs::path& ivesties_failo_pavadinimas, bool& praejo) {
        std::ifstream ivesties_failas(ivesties_failo_pavadinimas);
        std::stringstream buffer{};
            if(!ivesties_failas || !ivesties_failas.is_open()) {
                praejo = false;
                throw std::runtime_error("Failas nerastas. ");
            }
            buffer << ivesties_failas.rdbuf();
            ivesties_failas.close();

        std::vector<std::string> split_linijos{};
        std::string linija{};

        //Skips the first line of ivesties_failas as it stores the information about each column.
        std::getline(buffer, linija);

        while (std::getline(buffer, linija)) {
            Studentas laikinas_studentas{};
            //pakeiciau i istringstreama, nes pratestavus atrodo greiciau xd, jeigu sukels bedu - pakeist atgal
            std::istringstream ivestis(linija);
            std::string vardas{}, pavarde{};
            ivestis>>vardas;
            laikinas_studentas.setVardas(vardas);
            ivestis>>pavarde;
            laikinas_studentas.setPavarde(pavarde);
            uint8_t pazymys{0};
            while(ivestis>>pazymys) {
                laikinas_studentas.addPazymys(pazymys);
            }
            laikinas_studentas.setEgzaminoRezultatas(laikinas_studentas.getPazymiai().back());
            laikinas_studentas.removePaskutinisPazymys();
            studentai.push_back(laikinas_studentas);
        }
}