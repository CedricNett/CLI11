#include <CLI/CLI.hpp>
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>

using json = nlohmann::json;

int main(int argc, char** argv){

    std::cout << "Moin! Hier ist ein Lagerhalterungssystem" << "\n" << std::endl;

    CLI::App app{"Schreibe: -r src/lagerhalterung.json \n"};

    std::string filepath;

    app.add_option("-r,--read", filepath,"Path to config file")
        ->required()
        ->check(CLI::ExistingFile);

    try{
        app.parse(argc, argv);
    }
    catch(const CLI::ParseError &e){
        return app.exit(e);
    }

    std::ifstream file{filepath};
    if(!file.is_open()){
        std::cout << "Error opening file!\n" << std::endl;
        exit(0);
    }

    nlohmann::json database_object;

    try
    {
        database_object = nlohmann::json::parse(file);
    }
    catch (nlohmann::json::parse_error& ex)
    {
        std::cerr << "parse error at byte " << ex.byte << std::endl;
    }

    for (auto& element : database_object["Regale"]){
    
        std::cout << "Das Regal " << element["Regal"] << " beinhaltet folgende dinge: " << element["Inhalt"] << std::endl;
        std::cout << "\033[1;31mAllgemein: \033[0m" << "Es sind " << element["Leere Plätze"] << " von " << element["Anzahl Lagerplätze"] << " Plätze frei \n" << std::endl;
    }

    /**********************************/
    std::cout << "\033[1;31mPlatzhalter\n\033[0m" << std::endl;
    
    for (auto& element : database_object["Regale: Inhalt"]){

        std::cout <<  "\033[1;31mRechnerisch: \033[0m\n" << "Es sind " << element["Fernseher"] << element["Radio"] << element["SAT-Anlage"] << " von " << element["Anzahl Lagerplätze"] << " Plätze frei \n" << std::endl;
    }

    for (auto& element : database_object["Inhalt"]){

        std::cout <<  "\033[1;31mRechnerisch: \033[0m\n" << "Es sind " << element["Fernseher"] << element["Radio"] << element["SAT-Anlage"] << " von " << element["Anzahl Lagerplätze"] << " Plätze frei \n" << std::endl;
    }
    /**********************************/

    return 0;
}