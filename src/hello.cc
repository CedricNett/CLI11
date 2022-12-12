#include <CLI/CLI.hpp>
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>

using namespace std;
using json = nlohmann::json;

int main(int argc, char** argv) {

    cout << "Moin! Hier ist ein kleiner Summierer mit CLI11!" << "\n";

    CLI::App app{"Schreibe: -r test.json ,um den Inhalt einzulesen und ausgeben zu lassen \nUm einen filename einzugeben schreibe: -f ... \nUm eine Rechung durchzuführen schreibe: -e .. -z .."};

    int erste = 0, zweite = 0, summe = 0;

    string filename = "default";

    app.add_option("-f,--file", filename, "A help string"); //Lese einen filename ein

    app.add_option("-e,--erste_zahl", erste, "A help string"); //Füge eine Zahl hinzu

    app.add_option("-z,--zweite_zahl", zweite, "A help string"); //Füge eine zweite Zahl hinzu

    string filepath;
    app.add_option("-r,--read", filepath,"Path to config file") //Lese eine Datei ein
        ->required()
        ->check(CLI::ExistingFile);

    CLI11_PARSE(app, argc, argv);

    summe = erste + zweite;

    cout << erste << " + " << zweite << " = " << summe << "\n"; //Addiere die beiden hinzugefügten Zahlen

    cout << filename << "\n";

    ifstream file{filepath};

    if(!file.is_open()){ //Lässt sich die Datei öffnen?
        cout << "Error opening file!\n";
        exit(0);
    }

    json FileToJson;

    file >> FileToJson;

    cout << FileToJson.dump() << "\n"; //Gebe den Inhalt der Datei aus

    return 0;
}