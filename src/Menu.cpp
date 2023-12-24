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
                string opt;
                cin >> opt;
                int optI = 0;
                bool flag = false;
                try{
                    optI = std::stoi(opt);

                }
                catch(const std::invalid_argument& e){
                    std::cerr << "Error: invalid argument - must be a number from 1 to 3!" << std::endl;
                    flag = true;
                }
                catch (const std::out_of_range& e) {
                    flag = true;
                    std::cerr << "Error: out of range - " << e.what() << std::endl;
                }
                if (!flag) {
                    if (optI < 1 || optI > 3){
                        std::cerr << "Must be a number from 1 to 3!" << std::endl;
                        continue;
                    }
                    cout << "What is the maximum number of stops?" << endl;
                    string x;
                    int xI = 0;
                    cin >> x;
                    try{
                        xI = std::stoi(x);
                    }
                    catch(const std::invalid_argument& e){
                        std::cerr << "Error: invalid argument - must be a number!" << std::endl;
                        flag = true;
                    }
                    catch (const std::out_of_range& e) {
                        flag = true;
                        std::cerr << "Error: out of range - " << e.what() << std::endl;
                    }
                    if (!flag)
                        app.findAirportMaxX(code, xI, optI);
                }

        }
        else if (input == "8") {
                cout << "K?" << endl;
                int k;
                cin >> k;
                app.getKAirportsGreatestCap(k);

        }
        else if (input== "9") {
                app.essentialAirports();
        }
        else if (input == "quit"){

        }
        else {
                cout << "no functionality called!" << endl;
        }
    }
}
