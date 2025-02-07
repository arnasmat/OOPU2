#include "pagalbines.h"

void studentu_ivestis(std::vector<Studentas>& studentai) {
    while(true) {
        std::cout<<"Iveskite studentus arba noredami baigti iveskite 'n': "<<std::endl;
        Studentas laikinas_studentas{};
        std::cout<<"Iveskit studento varda ir pavarde: ";
        std::cin>>laikinas_studentas.vardas;
        if(laikinas_studentas.vardas == "n") {
            break;
        }
        std::cin>>laikinas_studentas.pavarde;
        std::cout<<"Iveskite kiek pazymiu gavo studentas: ";
        int pazymiu_kiekis{};
        std::cin>>pazymiu_kiekis;
        std::cout<<"Iveskite pazymius: ";
        for(int j=0; j<pazymiu_kiekis; j++) {
            int pazymys{0};
            while(pazymys < 1 || pazymys > 10) {
                std::cin>>pazymys;
                if(pazymys < 1 || pazymys > 10) {
                    std::cout<<"Ivestas netinkamas pazymys. Iveskite pazymi is naujo: ";
                }
            }
            laikinas_studentas.pazymiai.push_back(pazymys);
        }
        std::cout<<"Iveskite egzamino rezultata: ";
        std::cin>>laikinas_studentas.egzamino_rezultatas;
        studentai.push_back(laikinas_studentas);
    }
}

void studentu_atspausdinimas(std::vector<Studentas>& studentai) {
    for(auto i: studentai) {
        std::cout<<i.vardas<<" "<<i.pavarde<<std::endl;
        for(int j=0; j<i.pazymiai.size(); j++) {
            std::cout<<i.pazymiai[j]<<" ";
        }
        std::cout<<std::endl;
        std::cout<<i.egzamino_rezultatas<<std::endl;
    }
}

unsigned int galutinis_pazymys_vidurkis(Studentas &studentas) {
    unsigned int pazymiu_suma{0};
    for(const auto i: studentas.pazymiai) {
        pazymiu_suma+=i;
    }
    return static_cast<int>(round(pazymiu_suma / studentas.pazymiai.size() * 0.4 + studentas.egzamino_rezultatas * 0.6));
}

unsigned int galutinis_pazymys_mediana(Studentas &studentas) {
    unsigned int mediana{0};
    if(studentas.pazymiai.size()%2==0) {
        mediana = round((studentas.pazymiai[studentas.pazymiai.size()/2.0] + studentas.pazymiai[studentas.pazymiai.size()/2.0-1])/2.0);
    } else {
        mediana = studentas.pazymiai[(studentas.pazymiai.size()/2.0)];
    }
    return static_cast<int>(mediana*0.4 + studentas.egzamino_rezultatas*0.6);
}

void isvestis(std::vector<Studentas>& studentai) {
    char pasirinkimas{};
    std::cout<<"Pasirinkite ka norite matyti: v - vidurkis, m - mediana, a - abu: ";
    while(pasirinkimas != 'v' && pasirinkimas != 'm' && pasirinkimas != 'a') {
        std::cin>>pasirinkimas;
        if(pasirinkimas != 'v' && pasirinkimas !=  'm' && pasirinkimas != 'a') {
            std::cout<<"Neteisingas pasirinkimas. Prasome ivesti v, m arba a.";
        }
    }

    std::cout<<"Vardas    Pavarde    ";
    if(pasirinkimas=='v' || pasirinkimas=='a') {
        std::cout<<"Galutinis (Vid.)  ";
    }
    if(pasirinkimas=='a') std::cout<<"  ";
    if(pasirinkimas=='m' || pasirinkimas=='a') {
        std::cout<<"Galutinis (Med.)";
    }
    std::cout<<std::endl;
    std::cout<<"------------------------------------------------------------"<<std::endl;
    for(auto i: studentai) {
        std::cout<<i.vardas<<" "<<i.pavarde<<" ";
        if(pasirinkimas=='v' || pasirinkimas=='a') {
            std::cout<<galutinis_pazymys_vidurkis(i);
        }
        if(pasirinkimas=='a') std::cout<<"/  ";
        if(pasirinkimas=='m' || pasirinkimas=='a') {
            std::cout<<galutinis_pazymys_mediana(i);
        }
        std::cout<<std::endl;
    }
}


int main() {
    std::vector<Studentas> studentai{};
    studentu_ivestis(studentai);
    studentu_atspausdinimas(studentai);
    isvestis(studentai);
}