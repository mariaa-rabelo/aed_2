//
// Created by micaela_albino on 23-12-2023.
//
#include <limits>
#include "Menu.h"

Menu::Menu() {
    app = Application();
}


void Menu::listMenu() {
    std::cout << "MENU:" << std::endl;
    std::cout << "1: NumAirports and NumFlights" << std::endl
    << "2: Flights out of an airport and airlines"<< std::endl
    << "3: Flights per city/airline" << std::endl
    << "4: Countries from airport/city" << std::endl
    << "5: Destinations from airport" << std::endl
    << "6: findAirportMaxX" << std::endl
    << "7: Maximum trip" << std::endl
    << "8: getKAirportsGreatestCap" << std::endl
    << "9: essentialAirports"<< std::endl
    << "10: best flight opt"<< std::endl
    << "quit to well... quit" << std::endl;
}


void Menu::selectOptions(queue<string>& order){

    cout << "1: airport code"<<endl
    << "2: airport name"<<endl
    << "3: city and country"<<endl
    << "4: cancel"<<endl;
    //<< "coordinates"<<endl;
    std::string opt;
    std::cin >> opt;
    order.push(opt);
    if (opt == "4") {
        return;
    }
    else if (opt == "1"){
        std::cout << "airport's code:"<<std::endl;
        std::cin >> opt;
        order.push(opt);
    }
    else if (opt == "2"){
        std::cout << "airport's name:"<<std::endl;
        std::cin >> opt;
        order.push(opt);
    }
    else if (opt == "3"){
        std::cout << "city"<<std::endl;
        std::cin >> opt;
        order.push(opt);
        std::cout << "country"<<std::endl;
        std::cin >> opt;
        order.push(opt);
    }
    else {
        std::cout << "invalid input!"<<std::endl; order.pop(); order.push("4");
    }
}

void Menu::enterForMenu(){
    std::cout << "Press enter to return to the menu" << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get(); // Aguarda o usuário pressionar Enter
    listMenu(); // Exibe o menu novamente
}

void Menu::print(){
    app.run();
    listMenu();
    std::string input;
    while (input != "quit") {
        std::cin >> input;
        if (input =="1"){
            showGlobalStats();
        } else if (input == "2"){
            showAirportDetails();
        } else if (input == "3") {
            showCityOrAirlineStats();
        } else if (input == "4") {
            showCountryStats();
        } else if (input == "5"){
            showDestinationsStats();
        } else if (input == "6") {
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
                    continue;
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
        } else if (input == "7"){
            app.maximumTrip();
        } else if (input == "8") {
            std::cout << "K?" << std::endl;
            int k;
            std::cin >> k;
            app.getKAirportsGreatestCap(k);
        } else if (input== "9") {
            app.essentialAirports();
        } else if (input == "10"){
            std::cout << "choose the option for the departure location:"<< std::endl;
            std::queue<std::string> order;
            selectOptions(order);
            auto option = order.front();
            order.pop();
            if (option == "4"){
                continue;
                //ignorar o resto, passa para prox iteração
            }
            bool src = false;
            bool dst = false;
            Vertex<Airport>* sourc;
            Vertex<Airport>* dest;
            std::set<Vertex<Airport>*> sourc_;
            std::set<Vertex<Airport>*> dest_;
            if (option == "1" ){
                if (!app.getAirport(order.front(), true, sourc)){
                    std::cout << "airport's code not found!"<< std::endl;
                    continue;
                }

            }
            else if (option == "2"){
                if (!app.getAirport(order.front(), false, sourc)){
                    std::cout << "airport's name not found!"<< std::endl;
                    continue;
                }
            }
            else if (option == "3"){
                src = true;
                std::string city = order.front();
                order.pop();
                if (!app.getAirportsInCity(city,order.front(),sourc_)){
                    std::cout << "no city with that name was found!"<< std::endl;
                    continue;
                }
            }
            order = {};
            selectOptions(order);
            option= order.front();
            order.pop();
            if ( option== "4"){
                continue;
            }
            if (option == "1" ){
                if (!app.getAirport(order.front(), true, dest)){
                    std::cout << "airport's code not found!"<< std::endl;
                    continue;
                }
                //cout << "dest:"<<endl;
                //dest->getInfo().print();
            }
            else if (option == "2"){
                if (!app.getAirport(order.front(), false, dest)){
                    std::cout << "airport's name not found!"<<std::endl;
                    continue;
                }
            }
            else if (option == "3"){
                dst = true;
                std::string city = order.front();
                order.pop();
                if (!app.getAirportsInCity(city,order.front(),dest_)){
                    std::cout << "no city with that name was found!"<< std::endl;
                    continue;
                }
            }
            if (!src && !dst){
                app.getBestFlightOption(sourc, dest);
            }
            else if (!src && dst){

            }
            else if (src && dst){

            }
            else if (src && !dst){

            }

        }
        else if (input == "11"){
            set<string> airlines;
            string airlineCode;
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

            for (const string& airline : airlines){
                if (!app.checkIfExists(airline)){
                    cout << "Invalid airline code given! "<< airline <<endl;
                    valid = false;
                }
            }
            if (!valid){
                continue;
            }
            string airport;
            cout << "source airport code:"<<endl;
            cin >> airport;
            auto src = app.getVertex(airport);
            cout << "destination airport code:"<<endl;
            cin >> airport;
            auto dst = app.getVertex(airport);
            if (src == nullptr || dst == nullptr){
                cout << "invalid airport"<<endl;
                continue;
            }
            app.bestFlightOptGivenAirports(airlines,src, dst );

        }
        else if (input == "12"){
            int max;
            cout << "max trips"<<endl;
            cin>> max;
            cout << "source airport code"<<endl;
            string airport;
            cin >> airport;
            auto src = app.getVertex(airport);
            cout << "dest airport code"<<endl;
            cin >> airport;
            auto dest = app.getVertex(airport);
            if (src == nullptr || dest == nullptr){
                cout << "invalid airport"<<endl;
                continue;
            }
            app.bestFlightOptMaxAirports(max,src,dest);
        }
        else if (input == "13"){

        }
        else if (input == "quit"){
            break;
        }
        else {
            std::cout << "no functionality called!" << std::endl;
        }
        enterForMenu();
        continue;
    }
}

void Menu::showGlobalStats() {
    std::cout << "Total number of airports: " << app.getNumAirports() << std::endl;
    std::cout << "Total number of flights: " << app.getGlobalNumFlights() << std::endl;
}

void Menu::showAirportDetails() {
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

void Menu::showCityOrAirlineStats(){
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
void Menu::showCountryStats(){
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
void Menu::showDestinationsStats(){
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

