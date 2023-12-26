//
// Created by micaela_albino on 23-12-2023.
//
#include <limits>
#include "Menu.h"

Menu::Menu() {
    app = Application();
}


void Menu::listMenu() {
    cout << "MENU:" << endl;
    cout << "1: NumAirports and NumFlights" << endl
    << "2: Flights out of an airport and airlines"<< endl
    //TODO: give the user the option to choose the city or airline
    << "3: Flights per city/airline" << endl
    << "4: Countries from airport/city" << endl
    << "5: Destinations from airport" << endl
    << "6: findAirportMaxX" << endl
    << "7: Maximum trip" << endl
    << "8: getKAirportsGreatestCap" << endl
    << "9: essentialAirports"<< endl
    << "10: best flight opt"<< endl
    << "quit to well... quit" << endl;
}

void Menu::selectOptions(queue<string>& order){
    cout << "1: airport code"<<endl
    << "2: airport name"<<endl
    << "3: city and country"<<endl
    << "4: cancel"<<endl;
    //<< "coordinates"<<endl;
    string opt;
    cin >> opt;
    order.push(opt);
    if (opt == "4") {
        return;
    }
    else if (opt == "1"){
        cout << "airport's code:"<<endl;
        cin >> opt;
        order.push(opt);
    }
    else if (opt == "2"){
        cout << "airport's name:"<<endl;
        cin >> opt;
        order.push(opt);
    }
    else if (opt == "3"){
        cout << "city"<<endl;
        cin >> opt;
        order.push(opt);
        cout << "country"<<endl;
        cin >> opt;
        order.push(opt);
    }
    else {cout << "invalid input!"<<endl; order.pop(); order.push("4");}
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
    string input;
    while (input != "quit") {
        cin >> input;
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
        }
        else if (input == "6") {
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
        else if (input == "7"){
            app.maximumTrip();
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
        else if (input == "10"){
            cout << "choose the option for the departure location:"<<endl;
            queue<string> order;
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
            set<Vertex<Airport>*> sourc_;
            set<Vertex<Airport>*> dest_;
            if (option == "1" ){
                if (!app.getAirport(order.front(), true, sourc)){
                    cout << "airport's code not found!"<<endl;
                    continue;
                }
                //cout << "src:"<<endl;
                //sourc->getInfo().print();
            }
            else if (option == "2"){
                if (!app.getAirport(order.front(), false, sourc)){
                    cout << "airport's name not found!"<<endl;
                    continue;
                }
            }
            else if (option == "3"){
                src = true;
                string city = order.front();
                order.pop();
                if (!app.getAirportsInCity(city,order.front(),sourc_)){
                    cout << "no city with that name was found!"<<endl;
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
                    cout << "airport's code not found!"<<endl;
                    continue;
                }
                //cout << "dest:"<<endl;
                //dest->getInfo().print();

            }
            else if (option == "2"){
                if (!app.getAirport(order.front(), false, dest)){
                    cout << "airport's name not found!"<<endl;
                    continue;
                }

            }
            else if (option == "3"){
                dst = true;
                string city = order.front();
                order.pop();
                if (!app.getAirportsInCity(city,order.front(),dest_)){
                    cout << "no city with that name was found!"<<endl;
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
            /*
            while (!order.empty()){
                if (order.front() == "1"){
                    order.pop();
                    Vertex<Airport>* v;
                    if (!app.getAirport(order.front(), true, v)){
                        break;
                    }
                }
            }
            app.getBestFlightOption();
            */
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
    std::cout << "1. Flights from City\n";
    std::cout << "2. Flights by Airline\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    if (choice == 1) {
        auto flightsByCity = app.getFlightsByCity();
        for (const auto& [city, count] : flightsByCity) {
            std::cout << "City: " << city << ", Flights: " << count << std::endl;
        }
    } else if (choice == 2) {
        auto flightsByAirline = app.getFlightsByAirline();
        for (const auto& [airline, count] : flightsByAirline) {
            std::cout << "Airline: " << airline << ", Flights: " << count << std::endl;
        }
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

