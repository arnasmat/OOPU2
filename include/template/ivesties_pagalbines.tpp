template <typename Container>
void vardu_ivestis(const Container& studentai, Studentas &laikinas_studentas) {
    try {
        std::cout<<"Iveskit studento varda ir pavarde (noredami baigti iveskite 'n'): ";
        std::string temp_string{};
        std::cin>>temp_string;
        laikinas_studentas.setVardas(temp_string);

        while (laikinas_studentas.getVardas() == "n" && studentai.empty()) {
            std::cout<<"Iveskite bent viena studenta: \n";
            std::cin>>temp_string;
            laikinas_studentas.setVardas(temp_string);
        }

        if(laikinas_studentas.getVardas() == "n" && !studentai.empty()) {
            return;
        }

        std::cin>>temp_string;
        laikinas_studentas.setVardas(temp_string);

    } catch(std::exception& e) {
        std::cerr<<"Ivyko klaida ivedant varda ir pavarde: "<<e.what()<<"\n";
        laikinas_studentas.setVardas("Vardas");
        laikinas_studentas.setPavarde("Pavarde");
    }
}