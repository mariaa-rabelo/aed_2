//
// Created by micaela_albino on 23-12-2023.
//
#include "Menu.h"

Menu::Menu() {
    app = Application();
}


void Menu::listMenu() {
    std::cout << "MENU:" << std::endl;
    std::cout << "0. Quit" << std::endl
    << "1: NumAirports and NumFlights" << std::endl
    << "2: Flights out of an airport and airlines"<< std::endl
    << "3: Flights per city/airline" << std::endl
    << "4: Countries from airport/city" << std::endl
    << "5: Destinations from airport" << std::endl
    << "6: findAirportMaxX" << std::endl
    << "7: Maximum trip" << std::endl
    << "8: getKAirportsGreatestCap" << std::endl
    << "9: essentialAirports"<< std::endl
    << "10: best flight opt"<< std::endl;
}


void Menu::selectOptions(std::queue<std::string>& order){
    std::cout << "1: airport code"<< std::endl
        << "2: airport name"<< std::endl
        << "3: city and country"<< std::endl
        << "4: cancel"<< std::endl;

    std::string opt;
    std::cin >> opt;
    int type = std::stoi(opt);
    switch (type) {
        case 1:
            std::cout << "airport's code:"<<std::endl;
            break;
        case 2:
            std::cout << "airport's name:"<<std::endl;
            break;
        case 3:
            std::cout << "city"<<std::endl;
            std::cin >> opt;
            order.push(opt);
            std::cout << "country"<<std::endl;
            break;
        case 4:
            return;
        default:
            std::cout << "invalid input!" << std::endl;
            return;
    }
    cin >> opt;
    order.push(opt);
}

void Menu::askReturnToMenu() {
    std::cout << "Press enter to return to the menu or type 'exit' to quit: ";
    std::string choice;
    std::cin.clear();
    getline(cin, choice);
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
    while (input !="0") {
        std::cin >> input;
        int option = std::stoi(input);
        switch (option) {
            case 0:
                break;
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
                std::cout << "Enter the number of airports with the greatest capacity (K):" << std::endl;
                int k;
                std::cin >> k;
                app.getKAirportsGreatestCap(k);
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
                handleFlightOptionWithMaxStops();
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
    std::cout << "Total number of airports: " << app.getNumAirports() << std::endl;
    std::cout << "Total number of flights: " << app.getGlobalNumFlights() << std::endl;
}

void Menu::handleAirportDetails() {
    std::string airportCode;
    bool isValidInput = false;

    do {
        std::cout << "Enter airport code: ";
        std::cin >> airportCode;

        std::cout << "Fetching number of outgoing flights..." <<std::endl;
        int outFlights = app.getOutFlights(airportCode);

        if (outFlights != -1) {
            isValidInput = true;
            std::cout << "Number of outgoing flights from " << airportCode << ": " << outFlights << std::endl;

            std::cout << "Fetching number of unique airlines..."<<std::endl;
            int uniqueAirlines = app.getUniqueAirlines(airportCode);
            std::cout << "There are " << uniqueAirlines << " different airlines operating from this airport." << std::endl;

        } else {
            std::cout << "Invalid airport code. Please try again. Example: CDG" << std::endl;
        }
    } while (!isValidInput);
}

void Menu::handleCityOrAirlineStats(){
    int choice;
    std::string input;
    int numFlights;
    std::cout << "1. Flights from City\n";
    std::cout << "2. Flights by Airline\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    if (choice == 1) {
        std::cout << "Enter city name (eg, Roma): ";
        std::cin >> input;
        numFlights = app.getFlightsByCity(input);
        std::cout << "City: " << input << ", Flights: " << numFlights << std::endl;
    } else if (choice == 2) {
        std::cout << "Enter airline code (eg, SWD):  ";
        std::cin >> input;
        numFlights = app.getFlightsByAirline(input);
        std::cout << "Airline: " << input << ", Flights: " << numFlights << std::endl;
    } else {
        std::cout << "Invalid choice.\n";
    }
}

//Number of different countries
// that a given airport/city flies to;
void Menu::handleCountryStats(){
    int choice;
    std::cout << "1. Unique countries from Airport\n";
    std::cout << "2. Unique countries from City\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    if (choice == 1) {
        std::string input;
        std::cout << "Enter airport code: ";
        std::cin >> input;

        int countriesFromAirport = app.getUniqueCountriesFromAirport(input);
        std::cout << "Number of unique countries from " << input << ": " << countriesFromAirport << std::endl;
    } else if (choice == 2) {
        std::string input;
        std::cout << "Enter city name: ";
        std::cin >> input;

        int countriesFromCity = app.getUniqueCountriesFromCity(input);
        std::cout << "Number of unique countries from " << input << ": " << countriesFromCity << std::endl;
    } else {
        std::cout << "Invalid choice.\n";
    }
}

//Number of destinations (airports, cities or countries)
//available for a given airport; func 5
void Menu::handleDestinationsStats(){
    std::string input;
    std::cout << "Enter airport code: ";
    std::cin >> input;
    int airportDest = app.getUniqueAirportsFromAirport(input);
    int citiesDest = app.getUniqueCitiesFromAirport(input);
    int countriesDest = app.getUniqueCountriesFromAirport(input);

    std::cout << airportDest <<
        " airports are a destination for " << input << std::endl;
    std::cout << citiesDest <<
              " cities are a destination for " << input << std::endl;
    std::cout << countriesDest <<
              " countries are a destination for " << input << std::endl;
}

void Menu::handleReachableInMaxXStops() {
    std::cout << "code of airport: " << std::endl;
    std::string code;
    std::cin >> code;
    std::cout << "What type of destinations are you looking for?" << std::endl;
    std::cout << "1: airports" << std::endl
              << "2: cities" << std::endl
              << "3: countries" << std::endl;
    std::string opt;
    std::cin >> opt;
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
        int xI = 0;
        std::cin >> x;
        try {
            xI = std::stoi(x);
        } catch(const std::invalid_argument& e){
            std::cerr << "Error: invalid argument - must be a number!" << std::endl;
            flag = true;
        } catch (const std::out_of_range& e) {
            flag = true;
            std::cerr << "Error: out of range - " << e.what() << std::endl;
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
    std::set<string> airlines;
    std::string airlineCode;
    cout<< "Please input the airlines you wish to use, type exit when done!"<<endl
        <<"Be aware that for the operation to be valid, all airlines given MUST be valid."<<endl;
    while (airlineCode != "exit"){
        cout << "airline's code:"<<endl;
        cin >> airlineCode;
        airlines.insert(airlineCode);

    }
    auto it =airlines.find("exit");
    airlines.erase(it);
    bool valid = true;

    for (const std::string& airline : airlines){
        if (!app.checkIfExists(airline)){
            cout << "Invalid airline code given! "<< airline <<endl;
            valid = false;
        }
    }
    if (!valid){
        return;
    }
    std::string airport;
    cout << "source airport code:"<<endl;
    cin >> airport;
    auto src = app.getVertex(airport);
    cout << "destination airport code:"<<endl;
    cin >> airport;
    auto dst = app.getVertex(airport);
    if (src == nullptr || dst == nullptr){
        cout << "invalid airport"<<endl;
        return;
    }
    app.bestFlightOptGivenAirports(airlines,src, dst );
}

void Menu::handleFlightOptionWithMaxStops() {
    int max;
    cout << "max trips"<<endl;
    cin>> max;
    cout << "source airport code"<<endl;
    std::string airport;
    cin >> airport;
    auto src = app.getVertex(airport);
    cout << "dest airport code"<<endl;
    cin >> airport;
    auto dest = app.getVertex(airport);
    if (src == nullptr || dest == nullptr){
        cout << "invalid airport"<<endl;
        return;
    }
    app.bestFlightOptMaxAirports(max,src,dest);
}

