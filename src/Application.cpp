//
// Created by user on 05-Dec-23.
//

#include "Application.h"
#include <set>
#include <algorithm>
#include <map>

using namespace std;
Application::Application() {
    flightOption = FlightOption();
}

void Application::run() {
    FileReader airlines_file("../dataset/airlines.csv", g_airport);
    FileReader airports_file("../dataset/airports.csv", g_airport);
    FileReader flights_file("../dataset/flights.csv", g_airport);

    airports_file.readAirports();
    airlines_file.readAirlines();
    flights_file.readFlights();
}

//func 1
int Application::getNumAirports() const{
    return g_airport.getNumVertex();
}

int Application::getGlobalNumFlights() const{
    return g_airport.getTotalEdges();
}

//func 2
int Application::getOutFlights(const std::string& airportCode) const{
    Vertex<Airport> * v = g_airport.findVertex(airportCode);
    if (v) return v->getAdj().size();
    return -1;
}

int Application::getUniqueAirlines(const std::string& airportCode) const{
    Vertex<Airport>* v = g_airport.findVertex(airportCode);
    if (v == nullptr) return 0;
    std::set<Airline*> uniqueAirlines;
    for (const Edge<Airport>& edge : v->getAdj()) {
        uniqueAirlines.insert(edge.getAirline());
    }
    return uniqueAirlines.size();
}

//func3
int Application::getFlightsByCity(const std::string& cityName) {
    int flightCount = 0;
    for (auto vertex : g_airport.getVertexSet()) {
        if (vertex->getInfo().getCity() == cityName) {
            flightCount += vertex->getAdj().size();
        }
    }
    return flightCount;
}

int Application::getFlightsByAirline(const std::string& airlineCode) {
    int flightCount = 0;
    for (auto vertex : g_airport.getVertexSet()) {
        for (auto& edge : vertex->getAdj()) {
            if (edge.getAirline()->getCode() == airlineCode) {
                flightCount++;
            }
        }
    }
    return flightCount;
}

//func4
int Application::getUniqueCountriesFromAirport(const std::string& airportCode) {
    Vertex<Airport>* airport = g_airport.findVertex(airportCode);
    if (!airport) return 0;

    std::set<std::string> uniqueCountries;
    for (auto& edge : airport->getAdj()) {
        uniqueCountries.insert(edge.getDest()->getInfo().getCountry());
    }
    return uniqueCountries.size();
}

int Application::getUniqueCountriesFromCity(const std::string& cityName) {
    std::set<std::string> uniqueCountries;
    for (auto vertex : g_airport.getVertexSet()) {
        if (vertex->getInfo().getCity() == cityName) {
            for (auto& edge : vertex->getAdj()) {
                uniqueCountries.insert(edge.getDest()->getInfo().getCountry());
            }
        }
    }
    return uniqueCountries.size();
}

//func5
void Application::findAllDestinations(const std::string airportCode) {
    Vertex<Airport>* startVertex = g_airport.findVertex(airportCode);
    if (!startVertex) {
        std::cout << "Airport not found." << std::endl;
        return;
    }

    // Reset 'visited' status of all vertices
    for (auto& vertex : g_airport.getVertexSet()) {
        vertex->setVisited(false);
    }

    std::set<std::string> uniqueAirports, uniqueCities, uniqueCountries;
    std::queue<Vertex<Airport>*> bfsQueue;

    bfsQueue.push(startVertex);
    startVertex->setVisited(true);

    while (!bfsQueue.empty()) {
        Vertex<Airport>* current = bfsQueue.front();
        bfsQueue.pop();

        uniqueAirports.insert(current->getInfo().getCode());
        uniqueCities.insert(current->getInfo().getCity());
        uniqueCountries.insert(current->getInfo().getCountry());

        for (const Edge<Airport>& edge : current->getAdj()) {
            if (!edge.getDest()->isVisited()) {
                bfsQueue.push(edge.getDest());
                edge.getDest()->setVisited(true);
            }
        }
    }

    std::cout << "Airports reachable from " << airportCode << ": " << uniqueAirports.size() << std::endl;
    std::cout << "Cities reachable from " << airportCode << ": " << uniqueCities.size() << std::endl;
    std::cout << "Countries reachable from " << airportCode << ": " << uniqueCountries.size() << std::endl;

}

// funcionalidade 6
void Application::findAirportMaxX( std::string code, int x, int option){
    std::set<Airport> destinations;
    auto setVertex = g_airport.getVertexSet();
    bool flag = false;
    for (auto node: setVertex){
        auto airport = node->getInfo();
        if ( airport.getCode() ==  code){
            flag = true;
            std::vector<Airport> possible_dests = nodesAtLessDistanceBFS( &g_airport, airport, x);
            for (const Airport& a : possible_dests){
                destinations.insert(a);
            }
            break;
        }
    }
    if (!flag){
        std::cout << "airport code not found!"<< std::endl;
        return;
    }
    //airports
    if (option == 1){
        for (const Airport& a: destinations){
            a.print();
        }
    }
    //cities
    else if (option == 2){
        std::set<std::string> cities;
        for (const Airport& a: destinations){
            cities.insert(a.getCity());
        }
        for (const std::string& city : cities){
            std::cout << city<< std::endl;
        }
    }
    //countries
    else if (option == 3){
        std::set<std::string> countries;
        for (const Airport& a: destinations){
            countries.insert(a.getCountry());
        }
        for (const std::string& country : countries){
            std::cout << country<< std::endl;
        }
    }
}

std::vector<Airport> Application::nodesAtLessDistanceBFS(const Graph<Airport> *g, const Airport &source, int k) {
    std::vector<Airport> res;

    Vertex<Airport> * v = g->findVertex(source);
    /*if (v == nullptr) {
        //cout<< "NULL";
        return res;
    }*/
    // pôr todos vertices a falso
    for (auto b : g->getVertexSet()){
        // cout<< "H";
        b->setVisited(false);
    }
    int level = 0;
    std::queue<Vertex<Airport>*> vert;
    std::queue<Vertex<Airport>*> aux;
    vert.push(v);
    while (level < k){
        while (!vert.empty()){
            Vertex<Airport> * current = vert.front();
            vert.pop();
            for ( Edge<Airport> e : current->getAdj()) {
                Vertex<Airport>* adj = e.getDest();
                if (!adj->isVisited()) {
                    aux.push(adj);
                    adj->setVisited(true);
                }
            }
        }
        level++;
        vert = aux;
        while (!aux.empty()){
            res.push_back(aux.front()->getInfo());
            aux.pop();
        }
        //aux = {};

    }
    while (!vert.empty()){
        res.push_back(vert.front()->getInfo());
        vert.pop();
    }
    return res;
}

//funcionalidade 7

void Application::maximumTrip(){
    std::vector<std::pair<Airport,Airport>> res;
    std::map<Airport, std::vector<std::pair<Airport, int>>> paths;
    std::vector<int> max_pathsV;
    auto verts = g_airport.getVertexSet();
    for (auto v : verts){
        for (auto v_ : verts){
            v_->setVisited(false);
        }
        std::vector<std::pair<Airport, int>> max_path = getMaxPathBFS(v, &g_airport);
        for (const std::pair<Airport, int>& p : max_path){
            max_pathsV.push_back(p.second);
        }
        auto v_paths = make_pair(v->getInfo(), max_path);
        paths.insert(v_paths);
    }
    //encontrar lenght de max_path
    int max = *max_element(max_pathsV.begin(), max_pathsV.end());
    //colocar em res todos os que têm max_lenght
    for (const auto& p : paths){
        for (const auto& k : p.second){
            if (k.second == max){
                res.emplace_back(p.first, k.first);
            }
        }
    }
    std::cout << "total flights: " << max << endl
    << "res:"<<std::endl;
    for (const auto& p : res){
        std::cout <<"from:"<< std::endl;
        p.first.print();
        std::cout << "to: "<<std::endl;
        p.second.print();
    }
}

std::vector<std::pair<Airport, int>> Application::getMaxPathBFS( Vertex<Airport> *v, Graph<Airport> *g){
    std::vector<std::pair<Airport, int>> res;
    int level = 0;
    std::queue<Vertex<Airport>*> vert;
    std::queue<Vertex<Airport>*> aux;
    std::queue<Vertex<Airport>*> final;
    v->setVisited(true);
    vert.push(v);
    while (!vert.empty()){
        while (!vert.empty()){
            Vertex<Airport> * current = vert.front();
            vert.pop();
            for ( Edge<Airport> e : current->getAdj()) {
                Vertex<Airport>* adj = e.getDest();
                if (!adj->isVisited()) {
                   // adj->getInfo().print();
                    aux.push(adj);
                    adj->setVisited(true);
                }
            }
        }
        level++;
        if (!aux.empty()){
            final = aux;
        }
        vert = aux;
        aux = {};
    }
    while (!final.empty()){
        Airport ar= final.front()->getInfo();
        res.push_back(std::make_pair(ar, level));
        final.pop();
    }
    return res;
}

// funcionalidade 8
int Application::getTotalFlights(const Graph<Airport> *g, Vertex<Airport> * v){
    auto setVertex = g->getVertexSet();
    Airport airport = v->getInfo();
    //outgoing
    int outgoing = v->getAdj().size();
    int incoming = 0;
    for (auto ver : setVertex){
        for (auto edg : ver->getAdj()){
            if (edg.getDest() == v){
                incoming++;
            }
        }
    }
    if (v->getInfo().getCode() == "ORD" || v->getInfo().getCode() == "PEK" || v->getInfo().getCode() == "LHR") {
        std::cout << "vert:" << v->getInfo().getCode() << std::endl
                  << "indeg:" << v->getIndegree() << std::endl
                  << "out:" << outgoing << std::endl;
    }
    return incoming+outgoing;

}
void Application::getKAirportsGreatestCap(int k){
    std::vector<int> caps;
    //std::multimap<int, Airport> capacity;
    std::vector<pair<int, Airport>> sum_flights;
    auto vertexSet = g_airport.getVertexSet();
    for (auto v : vertexSet){
        int vertCap = getTotalFlights(&g_airport, v);
        caps.push_back(vertCap);
        sum_flights.push_back(make_pair( vertCap,v->getInfo()));
    }
    std::sort(sum_flights.begin(), sum_flights.end(), [](pair<int, Airport> a, pair<int, Airport> b) { return a.first > b.first; });
    //std::sort(caps.begin(), caps.end(), [](int a, int b) { return a > b; });
    std::cout << "Airports:" << "      Flights:" << std::endl;
    for (int i = 0; i < k; i++){
        auto current = sum_flights[i];
        std::cout << current.second.getCode() << ":     "<< current.first<<std::endl;
    }
    /*for (int i = 0; i < k; i++){
        auto it = capacity.find(caps[i]);
        if (it != capacity.end()){
            Airport airport = (*it).second;
            airport.print();
            capacity.erase(it);
        }
    }*/
}

//funcionalidade 9

void Application::essentialAirports(){
    std::set<Airport> airports =  articulationPoints(&g_airport);
    std::cout << std::endl<< "Essential Airports: " << std::endl;
    for (const Airport& a : airports){
        a.print();
    }
    std::cout << airports.size() << " essential airports" << std::endl;
}


std::set<Airport> Application::articulationPoints(Graph<Airport> *g) {
    std::set<Airport> res;

    if (g->getVertexSet().empty())
        return res;
    auto g_ = g;
    auto verts = g_->getVertexSet();
    for (auto n : verts){
        for (auto e : n->getAdj()){
            g_->addEdge(e.getDest()->getInfo(), n->getInfo(), 0);
        }
    }
    for (auto v : verts){
        v->setVisited(false);
        v->setLow(0);
        v->setNum(0);
    }
    int i = 1;
    std::stack<Airport> s = {};
    for (auto v : verts){
        if (v->getNum() == 0)
            dfs_art(g_, v, s, res, i);
    }
    return res;
}

void Application::dfs_art(Graph<Airport> *g, Vertex<Airport> *v, std::stack<Airport> &s, std::set<Airport> &l, int &i){
    v->setNum(i);
    v->setLow(i);
    i++;
    s.push(v->getInfo());
    int children = 0;
    for (auto e : v->getAdj()){
        auto adj = e.getDest();
        std::stack<Airport> copy = s;
        bool flag = false;
        while (!copy.empty()){
            if (copy.top() == adj->getInfo()) {
                flag = true;
            }
            copy.pop();
        }
        if (adj->getNum() == 0){
            children++;
            dfs_art(g, adj, s, l, i);
            v->setLow(std::min(v->getLow(), adj->getLow()));
            if (adj->getLow() >= v->getNum()){
                if (v->getInfo() == g->getVertexSet()[0]->getInfo()) {
                    if (children > 1){
                        l.insert(v->getInfo());
                    }
                }
                else {
                    l.insert(v->getInfo());
                }
            }
        }
        else if (flag){
            v->setLow(std::min(v->getLow(), adj->getNum()));
        }
    }
    s.pop();
}

//FlightOption
 bool Application::getAirportsInCity(const std::string& city, const std::string& country, std::set<Vertex<Airport>*> res){
    bool result = false;
    auto verts = g_airport.getVertexSet();
    for ( const auto &v : verts){
        if (v->getInfo().getCity() == city && v->getInfo().getCountry() == country){
            res.insert(v);
            result = true;
        }
    }
    return result;
}

bool Application::getAirport(const std::string& identifier, bool opt, Vertex<Airport>* &vert){
    auto verts = g_airport.getVertexSet();
    if (opt) {
        for (const auto &v: verts) {
            if (v->getInfo().getCode() == identifier) {
                vert = v;
                return true;
            }
        }
    }
    else {
        for (const auto &v: verts) {
            if (v->getInfo().getName() == identifier){
                vert = v;
                return true;
            }
        }
    }
    return false;
}

void Application::getBestFlightOption(Vertex<Airport>* src, Vertex<Airport>* dest ){
    std::set<std::vector<Airport>> path = flightOption.flights(&g_airport, src, dest);
    for(const auto& possible_path : path){
        std::cout << "possible path: "<< std::endl;
        for (const auto& airport : possible_path){
            airport.print();
        }
    }
}

//bestFlightOption com filtros

void Application::bestFlightOptGivenAirports(std::set<std::string>& airlines, Vertex<Airport>* src, Vertex<Airport>* dest ){

    auto new_g = flightOption.removeEdgeGivenAirline(&g_airport, airlines);
    auto srcV = getVertex(src->getInfo().getCode(), &new_g );
    auto destV = getVertex(dest->getInfo().getCode(), &new_g);
    if (srcV == nullptr || destV == nullptr){
        std::cout << "No options found!"<<std::endl;
        return;
    }
    auto paths = flightOption.bfsFlightVisitFilter(&new_g, srcV, destV);
    cout << "ALL PATHS: "<<endl;
    for ( stack<pair<Airport, basic_string<char>>> path : paths){
        pair<Airport, std::string> new_pair(destV->getInfo(),"");
        path.push(new_pair);
        cout << "path:"<<endl;
        while (!path.empty()){
            cout << " airport: "<< path.top().first.getCode() << " airline: "<< path.top().second << endl;
            path.pop();
        }
    }

}

void Application::bestFlightOptMaxAirports(  int maxAirlines, Vertex<Airport>* src, Vertex<Airport>* dest){

    auto paths = flightOption.flights(&g_airport, src, dest);
    auto res = flightOption.flightsMaxAirlineNumber(&g_airport, paths, maxAirlines);
    for(const auto& possible_path : res){
        std::cout << "possible path:"<< std::endl;
        for (const auto& airport : possible_path){
            if (airport.second == ""){
                cout << "departure:"<< airport.first.getCode() <<endl;

            }
            else
                cout << airport.first.getCode() << " ( " << airport.second<< " ) " <<endl;
        }
    }
    /*
    auto paths = flightOption.flightsMaxAirlineNumber(&g_airport, src, dest, maxAirlines);
    if (paths.size() == 1 && paths[0].empty()){
        cout << "Not possible to reach "<< dest->getInfo().getCode()
        << " from "<< src->getInfo().getCode() << "in "<< maxAirlines << " trips, or less."<<endl;
        return;
    }
    cout << "ALL PATHS: "<<endl;
    for ( stack<pair<Airport, basic_string<char>>> path : paths){
        pair<Airport, std::string> new_pair(dest->getInfo(),"");
        path.push(new_pair);
        cout << "path:"<<endl;
        while (!path.empty()){
            cout << " airport: "<< path.top().first.getCode() << " Airline: "<< path.top().second << endl;
            path.pop();
        }
    }

    */
}

//auxiliar
Vertex<Airport>*Application::getVertex(std::string v, const Graph<Airport> *g) {
    return g->findVertex(v);
}

Vertex<Airport>* Application::getVertex(std::string v){
    return g_airport.findVertex(v);
}

bool Application::checkIfExists(const std::string& code){
    for (auto airl : g_airport.getAirlines()){
        if (airl->getCode() == code)
            return true;
    }

    return false;
}