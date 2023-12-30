//
// Created by micaela_albino on 23-12-2023.
//

#ifndef AED_2_MENU_H
#define AED_2_MENU_H


#include <iostream>
#include <string>

#include "Application.h"

class Menu{
private:
    Application app;
public:
    Menu();
    void print();
    static void selectOptions(std::queue<std::string>& order);
    static void listMenu();
    void handleGlobalStats();
    void handleAirportDetails();
    void handleCityOrAirlineStats();
    void handleCountryStats();
    void handleDestinationsStats();
    void handleReachableInMaxXStops();
    void handleBestFlightOption();
    void handleAirlinesFLightOptions();
    void handleFlightOptionWithMaxStops();

    static void askReturnToMenu();
};
#endif //AED_2_MENU_H
