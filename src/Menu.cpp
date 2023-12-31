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


void Menu::selectOptions(std::queue<std::string>& order){
    std::cout << "1: airport code"<< std::endl
            << "2: airport name"<< std::endl
            << "3: city and country"<< std::endl
            << "4: cancel"<< std::endl;

    std::string opt;
    std::getline(std::cin, opt);
    int type = std::stoi(opt);
    switch (type) {
        case 1:
            std::cout << "airport's code:"<<std::endl;
            break;
        case 2:
            std::cout << "airport's name:"<<std::endl;
            break;
        case 3:
            std::cout << "city: "<<std::endl;
            std::getline(std::cin, opt);
            order.push(opt);
            std::cout << "country: "<<std::endl;
            break;
        case 4:
            return;
        default:
            std::cout << "invalid input!" << std::endl;
            return;
    }
    std::getline(std::cin, opt);
    order.push(opt);
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

void Menu::handleBestFlightOption() {
    std::cout << "choose the option for the departure location:"<< std::endl;
    std::queue<std::string> order;
    selectOptions(order);
    auto option = order.front();
    order.pop();
    if (option == "4")
        return;
    bool src = false;
    bool dst = false;
    Vertex<Airport>* sourc;
    Vertex<Airport>* dest;
    std::set<Vertex<Airport>*> sourc_;
    std::set<Vertex<Airport>*> dest_;
    if (option == "1" ){
        if (!app.getAirport(order.front(), true, sourc)){
            std::cout << "airport's code not found!"<< std::endl;
            return;
        }
    }
    else if (option == "2"){
        if (!app.getAirport(order.front(), false, sourc)){
            std::cout << "airport's name not found!"<< std::endl;
            return;
        }
    }
    else if (option == "3"){
        src = true;
        std::string city = order.front();
        order.pop();
        if (!app.getAirportsInCity(city,order.front(),sourc_)){
            std::cout << "no city with that name was found!"<< std::endl;
            return;
        }
    }
    order = {};
    selectOptions(order);
    option= order.front();
    order.pop();
    if ( option== "4"){
        return;
    }
    if (option == "1" ){
        if (!app.getAirport(order.front(), true, dest)){
            std::cout << "airport's code not found!"<< std::endl;
            return;
        }
    }
    else if (option == "2"){
        if (!app.getAirport(order.front(), false, dest)){
            std::cout << "airport's name not found!"<<std::endl;
            return;
        }
    }
    else if (option == "3"){
        dst = true;
        std::string city = order.front();
        order.pop();
        if (!app.getAirportsInCity(city,order.front(),dest_)){
            std::cout << "no city with that name was found!"<< std::endl;
            return;
        }
    }
    if (!src && !dst){
        app.getBestFlightOption(sourc, dest);
    }
    else if (!src && dst){

    }
    else if (src && dst){

    }
    else if (src && !dst) {

    }
}

void Menu::handleAirlinesFLightOptions() {
    std::set<std::string> airlines;
    std::string airlineCode;
    std::cout<< "Please input the airlines you wish to use, type exit when done!"<< std::endl
        <<"Be aware that for the operation to be valid, all airlines given MUST be valid."<< std::endl;
    while (airlineCode != "exit"){
        std::cout << "airline's code:"<< std::endl;
        std::getline(std::cin, airlineCode);
        airlines.insert(airlineCode);
    }
    auto it =airlines.find("exit");
    airlines.erase(it);
    bool valid = true;

    for (const std::string& airline : airlines){
        if (!app.checkIfExists(airline)){
            std::cout << "Invalid airline code given! "<< airline << std::endl;
            valid = false;
        }
    }
    if (!valid){
        return;
    }
    std::string airport;
    std::cout << "source airport code:"<< std::endl;
    std::getline(std::cin, airport);
    auto src = app.getVertex(airport);
    std::cout << "destination airport code:"<< std::endl;
    std::getline(std::cin, airport);
    auto dst = app.getVertex(airport);
    if (src == nullptr || dst == nullptr){
        std::cout << "invalid airport"<< std::endl;
        return;
    }
    app.bestFlightOptGivenAirports(airlines,src,dst);
}

void Menu::handleFlightOptionWithMaxAirlineNumber() {
    int max;
    std::cout << "max airline number"<< std::endl;
    std::cin>> max;
    std::cout << "source airport code"<< std::endl;
    std::string airport;
    std::cin >> airport;
    auto src = app.getVertex(airport);
    std::cout << "dest airport code"<< std::endl;
    std::cin >> airport;
    auto dest = app.getVertex(airport);
    if (src == nullptr || dest == nullptr){
        std::cout << "invalid airport"<< std::endl;
        return;
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
