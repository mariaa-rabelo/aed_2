//
// Created by micaela_albino on 23-12-2023.
//
#include "Menu.h"

Menu::Menu() {
    app = Application();
}


void Menu::listMenu() {
    std::cout << "\n--- AIRPORT MANAGEMENT SYSTEM MENU ---\n";
    std::cout << "0. Quit Application\n";
    std::cout << "1. Show Global Airport and Flight Statistics\n";
    std::cout << "2. Display Details of a Specific Airport\n";
    std::cout << "3. Show Flight Statistics by City or Airline\n";
    std::cout << "4. List Unique Countries Served by an Airport/City\n";
    std::cout << "5. Explore Destinations from an Airport\n";
    std::cout << "6. Find Reachable Destinations Within X Stops from an Airport\n";
    std::cout << "7. Plan a Maximum Trip\n";
    std::cout << "8. Find Top K Airports with the Greatest Capacity\n";
    std::cout << "9. Identify Essential Airports in the Network\n";
    std::cout << "10. Find the Best Flight Option\n";
    std::cout << "11. Explore Flight Options with Specific Airlines\n";
    std::cout << "12. Find Flight Options with Maximum Airlines\n";
    std::cout << "Please choose an option (0-12): ";
}

void Menu::askReturnToMenu() {
    std::cout << "Press enter to return to the menu or type 'exit' to quit: ";
    std::string choice;
    std::getline(std::cin, choice);
    if (choice == "exit") {
        exit(0);
    } else {
        listMenu();
    }
}

void Menu::print(){
    app.run();
    listMenu();
    std::string input;
    while (true) {
        std::getline(std::cin, input);

        int option;
        try {
            option = std::stoi(input);
        } catch (const std::invalid_argument& e) {
            std::cout << "Invalid input, please enter a number.\n";
            continue;
        }

        switch (option) {
            case 0:
                return;
            case 1:
                handleGlobalStats();
                askReturnToMenu();
                break;
            case 2:
                handleAirportDetails();
                askReturnToMenu();
                break;
            case 3:
                handleCityOrAirlineStats();
                askReturnToMenu();
                break;
            case 4:
                handleCountryStats();
                askReturnToMenu();
                break;
            case 5:
                handleDestinationsStats();
                askReturnToMenu();
                break;
            case 6:
                handleReachableInMaxXStops();
                askReturnToMenu();
                break;
            case 7:
                app.maximumTrip();
                askReturnToMenu();
                break;
            case 8:
                handleGreatestCap();
                askReturnToMenu();
                break;
            case 9:
                app.essentialAirports();
                askReturnToMenu();
                break;
            case 10:
                handleBestFlightOption();
                askReturnToMenu();
                break;
            case 11:
                handleAirlinesFLightOptions();
                askReturnToMenu();
                break;
            case 12:
                handleFlightOptionWithMaxAirlineNumber();
                askReturnToMenu();
                break;
            default:
                std::cout << "Invalid input number :(" << std::endl;
                askReturnToMenu();
                break;
        }
    }
}

void Menu::handleGlobalStats() {
    std::cout << std::endl;
    std::cout << "Total number of airports: " << app.getNumAirports() << std::endl;
    std::cout << "Total number of flights: " << app.getGlobalNumFlights() << std::endl;
    std::cout << std::endl;
}

void Menu::handleAirportDetails() {
    std::cout << std::endl;
    std::cout << "Enter airport code (eg, BSB): ";
    std::string airportCode;
    std::getline(std::cin, airportCode);

    std::cout << std::endl;
    std::cout << "Fetching number of outgoing flights..." <<std::endl;
    int outFlights = app.getOutFlights(airportCode);

    while (outFlights==-1) {
        std::cout << "Invalid airport code, please try again (eg, BSB): ";
        std::getline(std::cin, airportCode);

        std::cout << std::endl;
        std::cout << "Fetching number of outgoing flights..." <<std::endl;
        outFlights = app.getOutFlights(airportCode);
    }
    std::cout << std::endl;
    std::cout << "Number of outgoing flights from " << airportCode << ": " << outFlights << std::endl;

    std::cout << std::endl;
    std::cout << "Fetching number of unique airlines..."<<std::endl;
    int uniqueAirlines = app.getUniqueAirlines(airportCode);
    std::cout << std::endl;
    std::cout << "There are " << uniqueAirlines << " different airlines operating from this airport." << std::endl;
}

void Menu::handleCityOrAirlineStats(){
    std::string input;
    std::cout << "1. Flights from City\n";
    std::cout << "2. Flights by Airline\n";
    std::cout << "Enter your choice: ";
    std::getline(std::cin, input);

    while (input != "1" && input != "2"){
        std::cout << "Invalid choice, try again." << std::endl;
        std::cout << "1. Flights from City\n";
        std::cout << "2. Flights by Airline\n";
        std::cout << "Enter your choice: ";
        std::getline(std::cin, input);
    }

    int numFlights;
    if (input == "1"){
        std::cout << "Enter city name (eg, Roma): ";
        std::getline(std::cin, input);
        numFlights = app.getFlightsByCity(input);
        std::cout << "City: " << input << ", Flights: " << numFlights << std::endl;
        return;
    }
    std::cout << "Enter airline code (eg, SWD):  ";
    std::getline(std::cin, input);
    numFlights = app.getFlightsByAirline(input);
    std::cout << "Airline: " << input << ", Flights: " << numFlights << std::endl;
}

//Number of different countries
// that a given airport/city flies to;
void Menu::handleCountryStats(){
    std::string input;
    std::cout << "1. Unique countries directly reachable from Airport\n";
    std::cout << "2. Unique countries directly reachable from City\n";
    std::cout << "Enter your choice: ";
    std::getline(std::cin, input);

    while (input != "1" && input != "2"){
        std::cout << "Invalid choice, try again." << std::endl;
        std::cout << "1. Unique countries directly reachable from Airport\n";
        std::cout << "2. Unique countries directly reachable from City\n";
        std::cout << "Enter your choice: ";
        std::getline(std::cin, input);
    }

    if (input == "1") {
        std::string airportCode;
        std::cout << "Enter airport code: ";
        std::getline(std::cin, airportCode);

        int countriesFromAirport = app.getUniqueCountriesFromAirport(airportCode);
        std::cout << "Number of unique countries directly reachable from " << airportCode << ": " << countriesFromAirport << std::endl;
        return;
    }

    std::string cityName;
    std::cout << "Enter city name: ";
    std::getline(std::cin, cityName);

    int countriesFromCity = app.getUniqueCountriesFromCity(cityName);
    std::cout << "Number of unique countries directly reachable from " << cityName << ": " << countriesFromCity << std::endl;
}

//Number of destinations (airports, cities or countries)
//available for a given airport; func 5
void Menu::handleDestinationsStats(){
    std::string airportCode;
    std::cout << "Enter airport code: ";
    std::getline(std::cin, airportCode);
    app.findAllDestinations(airportCode);
}

void Menu::handleReachableInMaxXStops() {
    std::cout << "Enter airport code: " << std::endl;
    std::string code;
    std::getline(std::cin, code);

    std::cout << "What type of destinations are you looking for?" << std::endl;
    std::cout << "1: airports" << std::endl
              << "2: cities" << std::endl
              << "3: countries" << std::endl;

    std::string opt;
    std::getline(std::cin, opt);
    int optI = 0;
    bool flag = false;

    try{
        optI = std::stoi(opt);
    } catch(const std::invalid_argument& e){
        std::cerr << "Error: invalid argument - must be a number from 1 to 3!" << std::endl;
        flag = true;
    } catch (const std::out_of_range& e) {
        flag = true;
        std::cerr << "Error: out of range - " << e.what() << std::endl;
    }

    if (!flag) {
        if (optI < 1 || optI > 3){
            std::cerr << "Must be a number from 1 to 3!" << std::endl;
            return;
        }
        std::cout << "What is the maximum number of stops?" << std::endl;
        std::string x;
        std::getline(std::cin, x);
        int xI = 0;

        try {
            xI = std::stoi(x);
        } catch(const std::invalid_argument& e){
            std::cerr << "Error: invalid argument - must be a number!" << std::endl;
            return;
        } catch (const std::out_of_range& e) {
            std::cerr << "Error: out of range - " << e.what() << std::endl;
            return;
        }
        app.findAirportMaxX(code, xI, optI);
    }
}

std::pair<std::string, std::string> Menu::selectOptions(){
    std::cout << "0: cancel\n" <<std::endl
              << "1: airport code"<< std::endl
              << "2: airport name"<< std::endl
              << "3: city name"<< std::endl
              << "4: geographical coordinates\n";

    std::string type, detail;
    std::getline(std::cin, type);

    while (type < "0" || type > "4") {
        std::cout << "Invalid input, please choose a number between 0 and 4.\n";
        std::getline(std::cin, type);
    }

    switch (std::stoi(type)) {
        case 0:
            return std::make_pair("cancel", "");
        case 1:
            std::cout << "airport's code:"<<std::endl;
            break;
        case 2:
            std::cout << "airport's name:"<<std::endl;
            break;
        case 3:
            std::cout << "city: "<<std::endl;
            break;
        case 4:{
            std::string latitude, longitude;
            std::cout << "Enter latitude: ";
            std::getline(std::cin, latitude);
            std::cout << "Enter longitude: ";
            std::getline(std::cin, longitude);
            detail = (latitude + " " + longitude);
            return std::make_pair(type, detail);
        }
    }

    std::getline(std::cin, detail);
    return std::make_pair(type, detail);
}

void Menu::handleBestFlightOption() {
    std::cout << "Choose the option for the departure location:"<< std::endl;
    auto source = selectOptions();
    if (source.first == "cancel") return;

    std::cout << "Choose the option for the destination location:\n";
    auto destination = selectOptions();
    if (destination.first == "cancel") return;

    app.getBestFlightOption(source, destination);
}

void Menu::handleAirlinesFLightOptions() {
    std::set<std::string> airlines;
    std::string airlineCode;
    std::cout<< "Please input the airlines you wish to use, type 'exit' when done!"<< std::endl;
    std::getline(std::cin, airlineCode);

    while (airlineCode != "exit") {
        if (!app.checkIfExists(airlineCode)){
        std::cout << "Invalid airline code given! Type 'exit' when done: "<< airlineCode << std::endl;
        } else airlines.insert(airlineCode);
        std::cout << "Airline's code:"<< std::endl;
        std::getline(std::cin, airlineCode);
    }

    std::cout << "Choose the option for the departure location:"<< std::endl;
    auto source = selectOptions();
    if (source.first == "cancel") return;

    std::cout << "Choose the option for the destination location:\n";
    auto destination = selectOptions();
    if (destination.first == "cancel") return;

    app.bestFlightOptFilter(airlines, source,destination);
}

void Menu::handleFlightOptionWithMaxAirlineNumber() {
    std::string maxInput;
    std::cout << "Max desired airline number: "<< std::endl;
    std::getline(std::cin, maxInput);

    int max = std::stoi(maxInput);

    std::cout << "source airport code (eg, BSB): "<< std::endl;
    std::string airport;
    std::getline(std::cin, airport);
    auto src = app.getVertex(airport);
    while (src == nullptr){
        std::cout << "invalid airport code, try again (eg, BSB): "<< std::endl;
        std::getline(std::cin, airport);
        src = app.getVertex(airport);
    }

    std::cout << "dest airport code (eg, BSB): "<< std::endl;
    std::getline(std::cin, airport);
    auto dest = app.getVertex(airport);

    while (dest == nullptr){
        std::cout << "invalid airport code, try again (eg, XAP): "<< std::endl;
        std::getline(std::cin, airport);
        dest = app.getVertex(airport);
    }

    app.bestFlightOptMaxAirports(max,src,dest);
}

void Menu::handleGreatestCap() {

    int k = -1;
    while (k < 0) {
        std::cout << "Enter the number of airports (K):" << std::endl;
        std::string inputK;
        std::getline(std::cin, inputK);

        try {
            k = std::stoi(inputK);
            if (k < 0) {
                std::cout << "Please enter a positive number.\n";
            }
        } catch (const std::invalid_argument& e) {
            std::cout << "Invalid input, please enter a valid number.\n";
        } catch (const std::out_of_range& e) {
            std::cout << "Number is too large, please enter a smaller number.\n";
        }
    }
    app.getKAirportsGreatestCap(k);
}
