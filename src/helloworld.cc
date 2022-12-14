#include <CLI/CLI.hpp>
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>

using json = nlohmann::json;

int main(int argc, char** argv){

    std::cout << "Moin! Hier ist ein kleiber Addierer" << "\n" << std::endl;

    CLI::App app{"...\n"};

    std::cout << "Moin! Hier ist ein kleiner Summierer mit CLI11!" << "\n" << std::endl;

    CLI::App app{"Schreibe: -r test.json ,um den Inhalt einzulesen und ausgeben zu lassen \nUm einen filename einzugeben schreibe: -f ... \nUm eine Rechung durchzuführen schreibe: -e .. -z .."};

    int erste = 0, zweite = 0, summe = 0;

    std::string filename = "default";

    app.add_option("-f,--file", filename, "A help string"); //Lese einen filename ein

    app.add_option("-e,--erste_zahl", erste, "A help string"); //Füge eine Zahl hinzu

    app.add_option("-z,--zweite_zahl", zweite, "A help string"); //Füge eine zweite Zahl hinzu

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

    summe = erste + zweite;

    std::cout << erste << " + " << zweite << " = " << summe << "\n" << std::endl; //Addiere die beiden hinzugefügten Zahlen

    std::cout << filename << "\n"<< std::endl;
}