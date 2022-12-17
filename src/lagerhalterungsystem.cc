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

    //Irgendwie die options (oder flags) als "starter" für for(...) benennen? 
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

        std::exit(EXIT_FAILURE);
    }


    //Inhalt der Regale wird ausgegeben
    for (auto& element : database_object["Regale"])
    {
        int belegte_plaetze, anzahl_plaetze, leere_plaetze;

        belegte_plaetze = element["Inhalt"].size();

        anzahl_plaetze = element["Anzahl Lagerplätze"];

        leere_plaetze = anzahl_plaetze - belegte_plaetze;

        //Hier wird der Inhalt ausgegeben
        std::cout << "Das Regal " << element["Regal"] << " beinhaltet folgende dinge: " << element["Inhalt"] << std::endl;

        //Hier werden die restlichen Lagerplätze ausgegebnen
        std::cout << "Es sind " << leere_plaetze << " von " << anzahl_plaetze << " Plätze frei\n" << std::endl;
    }

    /*
    //Ändern des Inhaltes der eingelesenen Datei
    for (auto& change : database_object["Regale"])
    {
        std::cout << "Möchten Sie den Inhalt: " << change["Inhalt"] << " ändern?" << " Neuer Name: "  << std::endl;

        std::cin >> change["Inhalt"];

        std::cout << "\nDer geänderte Inhalt heißt: " << change["Inhalt"] << "\n" << std::endl;

    }
    */

    //Ändern des Inhaltes der eingelesenen Datei - Versuch den Inhalt einzeln zu verändern
    for (auto& change2 : database_object["Regale"])
    {
        std::cout << "Welchen Inhalt möchten Sie ändern?" << "\n";

        std::cout << change2["Inhalt"] << "\n";

        std::string vergleichsinhalt;

        std::cin >> vergleichsinhalt;

        for (auto& inhalt : change2["Inhalt"])
        {
            std::cout << "vergleichsinhalt = " << vergleichsinhalt << " inhalt = " << inhalt << std::endl;

            if(vergleichsinhalt == inhalt)
            {
                std::cout << "Hier bin ich" << std::endl;

                std::cin >> inhalt;

                std::cout << inhalt << std::endl;

                break;
            }

            std::cout << "Nach if abfrage: " << inhalt <<std::endl;



            
            /*
            if(inhalt == change2["Inhalt"])
            {
                std::cout << "Sie möchten den Inhalt Radios ändern? Neuer Name:" << std::endl;

                std::cin >> inhalt;
            }

            if(inhalt == change2["Inhalt"])
            {
                std::cout << "Sie möchten den Inhalt SAT-Anlage ändern? Neuer Name:" << std::endl;

                std::cin >> inhalt;
            }
            */

            std::cout << " Ende schleife inhalt \n" << std::endl;
        
        }

        std::cout << "Neuer Inhalt: " << change2["Inhalt"] << std::endl;

        std::cout << " Ende schleife member " << std::endl;

    }

    std::cout << " Ende " << std::endl;

    /*
    //Speichern des Inhaltes der geänderten, eingelesenen Datei
    std::string speicherpfad{};

    std::cout << "Name der Datei: ";

    std::cin >> speicherpfad;
    
    std::cout << "\nSpeicherpfad: /CLI11/" << speicherpfad << std::endl;    //Nur der Speicherpfad im Terminal ausgeben

    std::ofstream save_as{speicherpfad};

    save_as << database_object.dump(4);

    save_as.close();
    */

    return 0;
}