#include <CLI/CLI.hpp>
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>

using json = nlohmann::json;

int main()
{
    // Hauptmenü anzeigen
    while (true)
    {
        std::cout << "1. JSON-Datei öffnen" << std::endl;
        std::cout << "2. JSON-Datei bearbeiten" << std::endl;
        std::cout << "3. JSON-Datei speichern" << std::endl;
        std::cout << "4. Programm beenden" << std::endl;

        std::cout << "Wählen Sie eine Option: ";
        int option;
        std::cin >> option;

        if (option == 1)
        {
            // Öffnen einer JSON-Datei
            std::string filename;
            std::cout << "Geben Sie den Dateinamen ein: ";
            std::cin >> filename;

            std::ifstream file(filename);
            if (!file.is_open())
            {
                std::cout << "Fehler beim Öffnen der Datei" << std::endl;
                continue;
            }

            json data;
            file >> data;
            file.close();

            std::cout << "Datei erfolgreich geöffnet" << std::endl;
        }
        else if (option == 2)
        {
            // Bearbeiten der JSON-Datei
            // (zum Beispiel Ändern einer bestimmten Eigenschaft)
            data["property"] = "new value";

            std::cout << "Datei bearbeitet" << std::endl;
        }
        else if (option == 3)
        {
            // Speichern der JSON-Datei
            std::string filename;
            std::cout << "Geben Sie den Dateinamen ein: ";
            std::cin >> filename;

            std::ofstream file(filename);
            if (!file.is_open())
            {
                std::cout << "Fehler beim Öffnen der Datei" << std::endl;
                continue;
            }

            file << data;
            file.close();

            std::cout << "Datei erfolgreich gespeichert" << std::endl;
        }
        else if (option == 4)
        {
            // Programm beenden
            break;
        }
    }
}
