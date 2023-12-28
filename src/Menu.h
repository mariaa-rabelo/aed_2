//
// Created by micaela_albino on 23-12-2023.
//

#ifndef AED_2_MENU_H
#define AED_2_MENU_H


#include "Application.h"
#include <iostream>
#include <string>

class Menu{
private:
    Application app;
public:
    Menu();
    void print();
    void selectOptions(std::queue<std::string>& order);
    void listMenu();
    void showGlobalStats();
    void showAirportDetails();
    void showCityOrAirlineStats();
    void showCountryStats();
    void showDestinationsStats();

    void enterForMenu();
};
#endif //AED_2_MENU_H
