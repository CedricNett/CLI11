#include <CLI/CLI.hpp>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {

    cout << "Moin! Hier ist ein kleiner Summierer mit CLI11!" << "\n";

    CLI::App app{"Hier steht Ihre Werbung!"};

    int erste = 0, zweite = 0, summe = 0;

    app.add_option("-e,--erste_zahl", erste, "A help string");

    app.add_option("-z,--zweite_zahl", zweite, "A help string");

    CLI11_PARSE(app, argc, argv);

    summe = erste + zweite;

    cout << erste << " + " << zweite << " = " << summe << "\n";

    return 0;
}