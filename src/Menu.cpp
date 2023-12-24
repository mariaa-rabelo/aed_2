//
// Created by micaela_albino on 23-12-2023.
//
#include "Menu.h"

Menu::Menu() {
    app = Application();
}


void Menu::listMenu() {
    cout << "MENU:" << endl;
    cout << "1: " << endl
    << "2: "<< endl
    << "3: " << endl
    << "4: " << endl
    << "5: " << endl
    << "6: findAirportMaxX" << endl
    << "7: " << endl
    << "8: getKAirportsGreatestCap" << endl
    << "9: essentialAirports"<< endl;
    //<< "quit to well... quit" << endl;
}

void Menu::print(){
    app.run();
    listMenu();
    string input;
    while (input != "quit") {
        cin >> input;
        if (input == "6") {
                cout << "code of airport: " << endl;
                string code;
                cin >> code;
                cout << "What type of destinations are you looking for?" << endl;
                cout << "1: airports" << endl
                     << "2: cities" << endl
                     << "3: countries" << endl;
                int opt;
                cin >> opt;
                cout << "What is the maximum number of stops?" << endl;
                int x;
                cin >> x;
                app.findAirportMaxX(code, x, opt);
                break;
        }
        else if (input == "8") {
                cout << "K?" << endl;
                int k;
                cin >> k;
                app.getKAirportsGreatestCap(k);
                break;
        }
        else if (input== "9") {
                app.essentialAirports();
        }
        else {
                cout << "no functionality called!" << endl;
        }
    }
}
