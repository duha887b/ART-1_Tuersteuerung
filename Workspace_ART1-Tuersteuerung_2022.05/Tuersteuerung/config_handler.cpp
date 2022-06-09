//
// Created by supertrooper on 07.06.2022.
//

#include <fstream>


void config_handler::run() {

    std::ifstream input(config.txt);

    if (!input) {
        std::cerr << "Keine config Datei gefunden";
        return;
    }

    std::string line;

    while (std::getline(input, line)) {
        std::cout << line << "/n";

    }

}