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
    << "7: Maximum trip" << endl
    << "8: getKAirportsGreatestCap" << endl
    << "9: essentialAirports"<< endl
    << "10: best flight opt"<< endl;
    //<< "quit to well... quit" << endl;
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

        }
        else {
                cout << "no functionality called!" << endl;
        }
    }
}
