#include <CLI/CLI.hpp>
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>

using json = nlohmann::json;

int main(int argc, char** argv){

    std::cout << "Moin! Hier ist ein Lagerhalterungssystem" << "\n" << std::endl;

    CLI::App app{"Schreibe: -r src/lagerhalterung.json \n"};

    std::string filepath, inhalt, zaehlen, aendern;

    //Irgendwie die options als "starter" für for(...) benennen? 
    app.add_option("-i,--inhalt", inhalt, "Zeug"); //Inhalt ausgeben lassen

    app.add_option("-z,--zählen", zaehlen, "mehr Zeug"); //Inhalt zählen lassen

    app.add_option("-s,--ändern", aendern, "ganz viel Zeug"); //Inhalt ändern und in neuer Datei Speichern


    app.add_option("-r,--read", filepath, "Path to config file")
        ->required()
        ->check(CLI::ExistingFile);

    try
    {
        app.parse(argc, argv);
    }
    catch(const CLI::ParseError &e)
    {
        return app.exit(e);
    }

    std::ifstream file{filepath};
    if(!file.is_open())
    {
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

    //Inhalt der Regale wird ausgegeben
    for (auto& element : database_object["Regale"])
    {
        std::cout << "Das Regal " << element["Regal"] << " beinhaltet folgende dinge: " << element["Inhalt"] << std::endl;
        std::cout << "Es sind " << element["Leere Plätze"] << " von " << element["Anzahl Lagerplätze"] << " Plätze frei" << "\033[1;31m (Ausgebenen)\033[0m\n" << std::endl;
    }

    /*
    //Freie Plätze sollen gezählt werden, anhand Stückgut des Inhaltes (1)
    for (auto zaehlen = database_object["Inhalt"].begin(); zaehlen != database_object["Inhalt"].end(); ++zaehlen)
    {
        int num = stoi(zaehlen["Inhalt"]);

        std::cout << "Es sind " << *zaehlen << " Plätze frei" <<  "\033[1;31mRechnerisch: \033[0m\n" << std::endl;
    }
    */
    
    /*
    //Freie Plätze sollen gezählt werden, anhand Stückgut des Inhaltes (2)
    for (auto count = database_object("Inhalt"))
    {
        std::cout << "Es sind " << count << " Plätze frei" << "\033[1;31mRechnerisch: \033[0m\n" << std::endl;
    }
    */

    //Ändern des Inhaltes der eingelesenen Datei
    for (auto& change : database_object["Regale"])
    {
        std::cout << "Möchten Sie den Inhalt: " <<change["Inhalt"] << " ändern?" << " Neuer Name: "  << std::endl; 
        std::cin >> change["Inhalt"];
        std::cout << "\nDer geänderte Inhalt heißt: " << change["Inhalt"] << "\n" << std::endl;
    }

    //Speichern des Inhaltes der geänderten, eingelesenen Datei
    std::string speicherpfad{};
    std::cout << "Name der Datei: ";
    std::cin >> speicherpfad;
    std::cout << "\nSpeicherpfad: /CLI11/" << speicherpfad << std::endl;
    std::ofstream save_as{speicherpfad};
    save_as << database_object.dump();
    save_as.close();

    return 0;
}