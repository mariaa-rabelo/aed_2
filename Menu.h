/**
 * @file Menu.h
 * @brief This file contains the definition of the Menu class, which manages the user interface for the application.
 *
 * Created by micaela_albino on 23-12-2023.
 */

#ifndef AED_2_MENU_H
#define AED_2_MENU_H

#include <iostream>
#include <string>
#include "Application.h"

/**
 * @class Menu
 * @brief Manages the user interface and interactions for the airport management system.
 *
 * This class provides methods to display different menus, handle user inputs, and invoke the corresponding
 * functionalities in the Application class.
 */
class Menu {
private:
    /**
     * @var app
     * @brief Instance of Application class to interact with the core functionalities.
     */
    Application app;

public:
    /**
     * @brief Constructs the Menu object and initializes the application.
     */
    Menu();

    /**
     * @brief Starts the menu display and user interaction loop.
     */
    void print();

    /**
     * @brief Presents the user with different selection options and captures their choice.
     * @return A pair of strings representing the type and detail of the selection.
     */
    static std::pair<std::string, std::string> selectOptions();

    /**
     * @brief Displays the main menu with various options for the user to choose from.
     */
    static void listMenu();

    /**
     * @brief Handles the display of global statistics.
     */
    void handleGlobalStats();

    /**
     * @brief Handles the details of a specific airport.
     */
    void handleAirportDetails();

    /**
     * @brief Handles statistics related to cities or airlines.
     */
    void handleCityOrAirlineStats();

    /**
     * @brief Handles statistics about countries served by an airport or city.
     */
    void handleCountryStats();

    /**
     * @brief Handles information about destinations from a specific airport.
     */
    void handleDestinationsStats();

    /**
     * @brief Handles finding reachable destinations within a specified number of stops from an airport.
     */
    void handleReachableInMaxXStops();

    /**
     * @brief Handles finding the top K airports with the greatest capacity.
     */
    void handleGreatestCap();

    /**
     * @brief Handles finding the best flight option based on user criteria.
     */
    void handleBestFlightOption();

    /**
     * @brief Handles flight options with specific airlines.
     */
    void handleAirlinesFLightOptions();


    /**
     * @brief Handles finding flight options with a maximum number of airlines.
     */
    void handleFlightOptionWithMaxAirlineNumber();


    /**
     * @brief Presents the user with the option to return to the main menu or exit the application.
     */
    static void askReturnToMenu();
};

#endif //AED_2_MENU_H