#include <CLI/CLI.hpp>
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>

using json = nlohmann::json;
//nlohmann::json database_object;
//                                          zum starten       ./build/lagerhalterungsystem.cc -r src/lagerhalterung.json      ausgeben lassen! 
struct statemachine {
    //statemachine(json& database_object);
    //    : mein_json{database_object};
    json& mein_json;

    statemachine(json& database_object)
        :mein_json{database_object} {
        //std::cout << "Konstruktor called with Initilizerlist!\n";
    }

    void aendern() {

        ausgeben();

            int regalnummer; //Integer für die Options

            std::string neuerinhalt,alterinhalt,wahl;

            std::cout << "In welchem Regal möchetn Sie etwas ändern?" << "\n";

            std::cin>> regalnummer;

            for (auto& change : mein_json["Regale"])
            {
                if(change ["Regal"] == regalnummer)
                {          
                    std::cout << change["Inhalt"] << "\n"; 

                    std::cout << "Welcher Inhalt soll geändert werden?" << "\n"; 

                    std::cin>> alterinhalt;

                    for (auto& aktuellinhalt : change["Inhalt"] )
                    {
                        if (aktuellinhalt==alterinhalt)
                        {   
                            std::cout << aktuellinhalt << "\n"; 

                            std::cout << "Neuer Inhalt:" << "\n"; 

                            std::cin >> neuerinhalt;

                            aktuellinhalt =neuerinhalt;

                            return;
                        }                                                                                      
                    }

                    std::cout <<"Leider wurde der Inhalt " << alterinhalt <<" nicht gefunden!!! Soll er hinzugefügt werden?? [J/N]" << "\n";

                    std::cin >> wahl;

                    if (wahl == "J")
                    {
                        change ["Inhalt"].push_back(alterinhalt);
                        break;
                    }
                    
                    else
                    {
                        std::cout << "Dann eben nicht!" << "\n";
                        break;
                    }                          
                }
            }
    }

    void ausgeben() {
        for (auto& element : mein_json["Regale"])
        {
            int belegte_plaetze, anzahl_plaetze, leere_plaetze;

            //Hier wird durch die Funktion ".size" der Inhalt gezählt und dieser als Integer gesetzt
            belegte_plaetze = element["Inhalt"].size();

            //Hier wird "Anzahl Lagerplätze" aufgerufen und auch als Integer gesetzt
            anzahl_plaetze = element["Anzahl Lagerplätze"];

            //Hier wird er Aktuelle Inhalt, der "Anzahl Lagerplätze" abgezogen. Die zuvor deklarierten Integer werden verrechnet
            leere_plaetze = anzahl_plaetze - belegte_plaetze;

            //Hier wird der Inhalt ausgegeben -Aufgabe 1
            std::cout << "Das Regal " << element["Regal"] << " beinhaltet folgende dinge: " << element["Inhalt"] << std::endl;

            //Hier werden die restlichen Lagerplätze ausgegebnen -Aufgabe 2
            std::cout << "Es sind " << leere_plaetze << " von " << anzahl_plaetze << " Plätze frei\n" << std::endl;
        }
    }

    void speichern() {
        std::string speicherpfad{};

        std::cout << "Name der Datei: ";

        std::cin >> speicherpfad;

        std::cout << "\nSpeicherpfad: /CLI11/" << speicherpfad << std::endl;    //Optional. Gibt nur im Terminal den Speicherpfad aus, damit es "schön" aussieht!
        //Dieser muss je nach dem geändert werden, sollte euer Ordner "wo anders liegen"
        std::ofstream save_as{speicherpfad};                                    //bzw. sollte die Datei "anders heißen"
        //Beispiel: "\nSpeicherpfad: Server/maxmustermann/Projekte/Lagersysteme/" usw.
        save_as << mein_json.dump(4);
        //Warum auch immer wird die Reihenfolge bei neuem Speichern nicht eingehalten --Gerne Lösungen dazu Teilen!
        save_as.close();
    }

    void exit() {
        std::exit(EXIT_FAILURE); 
    }
};

int main(int argc, char** argv) {

    nlohmann::json database_object;

    std::cout << "Moin! Hier ist ein Lagerhalterungssystem" << "\n" << std::endl;

    CLI::App app{"Schreibe: -r src/lagerhalterung.json \n"};

    std::string filepath; //Strings für die Options

    app.add_option("-r,--read", filepath, "Path to config file")
    ->required()
    ->check(CLI::ExistingFile);

    //try & catch Funktion, sollte ein Parse Error auftreten, so wird die "app" geschlossen
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

    //try & catch Funktion, sollte die file nicht dem "database_object" übergeben werden, so schreibe den Fehler und exit mit Fehler
    try
    {
        database_object = nlohmann::json::parse(file);
    }
    catch (nlohmann::json::parse_error& ex)
    {
        std::cerr << "parse error at byte " << ex.byte << std::endl;

        std::exit(EXIT_FAILURE);
    }

    //statemachine lagerhaltung_statemachine();
    statemachine lagerhaltung_statemachine{database_object};

    std::cout << "Hallo und Willkommen in unserem Lagersytem!" << std::endl;

    while(true)
    {
        //std::cout << "Hallo und Willkommen in unserem Lagersytem!" << std::endl;

        int aktueller_state = 0;

        while((aktueller_state < 1) || (aktueller_state > 4 ))
        {
            std::cout <<    "Du kannst wählen zwischen: \n"
                      <<    "(1) für Inhalt Ändern \n"
                      <<    "(2) für Inhalt Ausgeben \n"
                      <<    "(3) für Inhalt Speichern \n" 
                      <<    "(4) für Exit"  <<std::endl;

            std::cin >> aktueller_state;

            if((aktueller_state < 1) || (aktueller_state > 4 ))
            {
                std::cout << "Keine gültige Auswahl!" << std::endl;
            }
        }

        if(aktueller_state == 1)//Funktion/State Inhalt Ändern
        {
            lagerhaltung_statemachine.aendern();
        }
        else if(aktueller_state == 2)//Funktion/State Inhalt Ausgeben
        {
            lagerhaltung_statemachine.ausgeben();
        }
        else if(aktueller_state == 3)//Funktion/State Inhalt Speichern
        {
            lagerhaltung_statemachine.speichern();
        }
        else if(aktueller_state == 4)
        {
            lagerhaltung_statemachine.exit();
        }
    }
}