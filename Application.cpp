//
// Created by user on 05-Dec-23.
//

#include "Application.h"
#include <set>
#include <algorithm>
#include <map>
#include <limits>
#include <cmath>

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
void Application::findAllDestinations(const std::string& airportCode) {
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
void Application::findAirportMaxX( const std::string& code, int x, int option){
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
        std::cout << "Total airports: " << destinations.size()<< std::endl;
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
        std::cout << "Total cities: " << cities.size()<< std::endl;
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
        std::cout << "Total countries: " << countries.size()<< std::endl;
    }
}

std::vector<Airport> Application::nodesAtLessDistanceBFS(const Graph<Airport> *g, const Airport &source, int k) {
    std::vector<Airport> res;

    Vertex<Airport> * v = g->findVertex(source);
    // pôr todos vertices a falso
    for (auto b : g->getVertexSet()){
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
        std::vector<std::pair<Airport, int>> max_path = getMaxPathBFS(v);
        for (const std::pair<Airport, int>& p : max_path){
            max_pathsV.push_back(p.second);
        }
        auto v_paths = make_pair(v->getInfo(), max_path);
        paths.insert(v_paths);
    }
    //encontrar lenght de max_path
    int max = *max_element(max_pathsV.begin(), max_pathsV.end());
    //colocar em res todos os que têm max_length
    for (const auto& p : paths){
        for (const auto& k : p.second){
            if (k.second == max){
                res.emplace_back(p.first, k.first);
            }
        }
    }

    std::cout << "Longest trips available:"<<std::endl;
    for (const auto& p : res){
        std::cout <<"from:"<< std::endl;
        p.first.print();
        std::cout << "to: "<<std::endl;
        p.second.print();
        std::cout <<std::endl;
    }
    std::cout << "They have the maximum of " << max-1 << " flights" <<std::endl;
}

std::vector<std::pair<Airport, int>> Application::getMaxPathBFS( Vertex<Airport> *v){
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
        res.emplace_back(ar, level);
        final.pop();
    }
    return res;
}

// funcionalidade 8
int Application::getTotalFlights(const Graph<Airport> *g, Vertex<Airport> * v){
    auto setVertex = g->getVertexSet();
    Airport airport = v->getInfo();
    int outgoing = v->getAdj().size();
    int incoming = 0;
    for (auto ver : setVertex){
        for (auto edg : ver->getAdj()){
            if (edg.getDest() == v){
                incoming++;
            }
        }
    }
    return incoming+outgoing;

}
void Application::getKAirportsGreatestCap(int k){
    std::vector<int> caps;
    std::vector<std::pair<int, Airport>> sum_flights;
    auto vertexSet = g_airport.getVertexSet();
    for (auto v : vertexSet){
        int vertCap = getTotalFlights(&g_airport, v);
        caps.push_back(vertCap);
        sum_flights.emplace_back( vertCap,v->getInfo());
    }
    std::sort(sum_flights.begin(), sum_flights.end(), [](const std::pair<int, Airport>& a, const std::pair<int, Airport>& b) { return a.first > b.first; });
    std::cout << "Airports:" << "      Flights:" << std::endl;
    for (int i = 0; i < k; i++){
        auto current = sum_flights[i];
        std::cout << current.second.getCode() << ":     "<< current.first<<std::endl;
    }

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

    //add opposite edges
    auto verts = g_->getVertexSet();
    for (auto n : verts){
        for (auto e : n->getAdj()){
            g_->addEdge(e.getDest()->getInfo(), n->getInfo(), nullptr);
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

void Application::getBestFlightOption(std::pair<std::string, std::string> src, std::pair<std::string, std::string> dest){
    auto srcVertices = getVerticesBasedOnInput(&g_airport, src);
    auto destVertices = getVerticesBasedOnInput(&g_airport, dest);
    g_airport.findAndDisplayBestPaths(srcVertices, destVertices);
    //findAndDisplayBestPaths(g, srcVertices, destVertices);
}


std::set<Vertex<Airport>*> Application::getVerticesBasedOnInput(Graph<Airport>* g, const std::pair<std::string, std::string>& input) {
    std::set<Vertex<Airport>*> vertices;

    if (input.first == "1") { // Airport code
        Vertex<Airport>* v = g->findVertex(input.second);
        if (!v) std::cout << "No airport was found with that code :( " << std::endl;
        else vertices.insert(v);
    } else if (input.first == "2") { // Airport name
        for (auto& vertex : g->getVertexSet()) {
            if (vertex->getInfo().getName() == input.second) {
                vertices.insert(vertex);
            }
        }
    } else if (input.first == "3") { // City name
        for (auto& vertex : g->getVertexSet()) {
            if (vertex->getInfo().getCity() == input.second) {
                vertices.insert(vertex);
            }
        }
    } else if (input.first =="4"){ //lat and long
        std::istringstream iss(input.second);
        double inputLat, inputLon;
        iss >> inputLat >> inputLon;

        double minDistance = std::numeric_limits<double>::max();

        for (auto& vertex : g->getVertexSet()) {
            double distance = haversineDistance(inputLat, inputLon, vertex->getInfo().getLatitude(), vertex->getInfo().getLongitude());
            if (distance < minDistance) {
                minDistance = distance;
                vertices.clear();
                vertices.insert(vertex);
            } else if (distance == minDistance) {
                vertices.insert(vertex);
            }
        }
    }
    return vertices;
}

double Application::haversineDistance(double lat1, double lon1, double lat2, double lon2) {
    const double earthRadiusKm = 6371.0;

    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;

    lat1 = lat1 * M_PI / 180.0;
    lat2 = lat2 * M_PI / 180.0;

    double a = sin(dLat/2) * sin(dLat/2) +
               sin(dLon/2) * sin(dLon/2) * cos(lat1) * cos(lat2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    return earthRadiusKm * c;
}

void Application::bestFlightOptMaxAirports(  int maxAirlines, Vertex<Airport>* src, Vertex<Airport>* dest){

    auto paths = flightOption.flights(&g_airport, src, dest);
    auto res = flightOption.flightsMaxAirlineNumber(&g_airport, paths, maxAirlines);
    for(const auto& possible_path : res){
        std::cout << "Possible path"<< std::endl;
        for (const auto& airport : possible_path){
            if (airport.second.empty()){
                std::cout << "departure: "<< airport.first.getCode() <<std::endl;
            }
            else
                std::cout << airport.first.getCode() << " ( " << airport.second<< " ) " <<std::endl;
        }
    }

}

void Application:: bestFlightOptFilter(std::set<std::string>& airlines, std::pair<std::string, std::string> src, std::pair<std::string, std::string> dest){
    auto new_g = flightOption.removeEdgeGivenAirline(&g_airport, airlines);

    auto srcVertices = getVerticesBasedOnInput(&new_g, src);
    auto destVertices = getVerticesBasedOnInput(&new_g, dest);
    if (srcVertices.empty() || destVertices.empty()){
        std::cout << "No valid route!"<<std::endl;
        return;
    }
    for (auto srcVertex : srcVertices) {
        for (auto destVertex : destVertices) {
            auto paths = flightOption.bfsFlightVisitFilter(&new_g, srcVertex, destVertex);
            std::set<std::stack<std::pair<Airport,std::string>>> paths_set(paths.begin(), paths.end());
            std::cout << "All paths from " << srcVertex->getInfo().getCode() << " to " << destVertex->getInfo().getCode() << ":"<<std::endl;
            for ( std::stack<std::pair<Airport, std::string>> path : paths_set){
                std::cout << "path:"<<std::endl;
                std::cout << destVertex->getInfo().getCode()<<std::endl;
                while (!path.empty()){
                    std::cout << "^ airport: "<< path.top().first.getCode() << " airline: "<< path.top().second << std::endl;
                    path.pop();
                }
            }
        }
    }
}


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