#include <CLI/CLI.hpp>
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>

using namespace std;
using json = nlohmann::json;

int main(int argc, char** argv) {

    cout << "Moin! Hier ist ein kleiner Summierer mit CLI11!" << "\n";

    CLI::App app{"Um einen filename einzugeben schreibe: -f ... \nUm eine Rechung durchzuführen schreibe: -e .. -z .."};

    int erste = 0, zweite = 0, summe = 0;

    string filename = "default";

    app.add_option("-f,--file", filename, "A help string");

    app.add_option("-e,--erste_zahl", erste, "A help string");

    app.add_option("-z,--zweite_zahl", zweite, "A help string");

    string filepath;
    app.add_option("-r,--read", filepath,"Path to config file")
        ->required()
        ->check(CLI::ExistingFile);

    CLI11_PARSE(app, argc, argv);

    summe = erste + zweite;

    cout << erste << " + " << zweite << " = " << summe << "\n"; 

    cout << filename << "\n";

    ifstream file{filepath};

    if(!file.is_open()){
        cout << "Error opening file!\n";
        exit(0);
    }

    json FileToJson;

    file >> FileToJson;

    cout << FileToJson.dump() << "\n";

    return 0;
}