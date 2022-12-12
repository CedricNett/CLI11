#include <CLI/CLI.hpp>
#include <iostream>
#include "json.hpp"

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

    CLI11_PARSE(app, argc, argv);

    summe = erste + zweite;

    cout << erste << " + " << zweite << " = " << summe << "\n"; 

    cout << filename << "\n";

    return 0;
}