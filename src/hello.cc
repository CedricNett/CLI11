#include <CLI/CLI.hpp>
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>

using json = nlohmann::json;

int main(int argc, char** argv) {

    std::cout << "Moin! Hier ist ein Lagerhalterungssystem" << "\n" << std::endl;

    CLI::App app{"Schreibe: -r src/lagerhalterung.json \n"};

    /*
    std::cout << "Moin! Hier ist ein kleiner Summierer mit CLI11!" << "\n" << std::endl;

    CLI::App app{"Schreibe: -r test.json ,um den Inhalt einzulesen und ausgeben zu lassen \nUm einen filename einzugeben schreibe: -f ... \nUm eine Rechung durchzuführen schreibe: -e .. -z .."};

    int erste = 0, zweite = 0, summe = 0;

    std::string filename = "default";

    app.add_option("-f,--file", filename, "A help string"); //Lese einen filename ein

    app.add_option("-e,--erste_zahl", erste, "A help string"); //Füge eine Zahl hinzu

    app.add_option("-z,--zweite_zahl", zweite, "A help string"); //Füge eine zweite Zahl hinzu
    */

    std::string filepath;

    app.add_option("-r,--read", filepath,"Path to config file") //Lese eine Datei ein
        ->required()
        ->check(CLI::ExistingFile);

    try{
        app.parse(argc, argv);
    }
    catch(const CLI::ParseError &e){
        return app.exit(e);
    }

    /*
    summe = erste + zweite;

    std::cout << erste << " + " << zweite << " = " << summe << "\n" << std::endl; //Addiere die beiden hinzugefügten Zahlen

    std::cout << filename << "\n"<< std::endl;
    */

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

    std::cout << "\033[1;31m Platzhalter \033[0m\n" << std::endl;
/***********************************************************************************************************************************************/
    for (auto& element : database_object["Regal"]){
        std::string rest;

        for( rest = element["Inhalt"]; rest < element["Inhalt"];){
            std::cout << rest << std::endl;
        }

        std::cout << "Im Regal " << element["Regal"] << " liegen " << rest << " von " << element["Anzahl Lagerplätze"] << std::endl;
    }
/***********************************************************************************************************************************************/
    std::cout << "\033[1;31m Platzhalter \033[0m\n" << std::endl;

    for (auto& element : database_object["Regale"]){
        //std::cout << "Im Regal "<< element["Regal"] << " liegen " << element[("Anzahl Lagerplätze") - ("Leere Plätze")] << " Waren" << std::endl; det funtzt so net
        std::cout << "Das Regal " << element["Regal"] << " beinhaltet folgende dinge: " << element["Inhalt"] << std::endl;
        std::cout << "Es sind " << element["Leere Plätze"] << " von " << element["Anzahl Lagerplätze"] << " Plätze frei \n" << std::endl;
    }

    return 0;
}