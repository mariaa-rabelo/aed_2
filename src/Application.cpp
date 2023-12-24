//
// Created by user on 05-Dec-23.
//

#include "Application.h"
#include <set>
#include <algorithm>
#include <map>
//#include <string>

//using namespace  std;

Application::Application() {}

void Application::run() {
    FileReader airlines_file("../dataset/airlines.csv", g_airport);
    FileReader airports_file("../dataset/airports.csv", g_airport);
    FileReader flights_file("../dataset/flights.csv", g_airport);

    airports_file.readAirports();
    airlines_file.readAirlines();
    flights_file.readFlights();

    std::cout << "Number of airports: " << g_airport.getNumVertex() << std::endl;
}

// funcionalidade 6
void Application::findAirportMaxX( string code, int x, int option){
    set<Airport> destinations;
    auto setVertex = g_airport.getVertexSet();
    bool flag = false;
    for (auto node: setVertex){
        auto airport = node->getInfo();
        if ( airport.getCode() ==  code){
            flag = true;
            vector<Airport> possible_dests = nodesAtLessDistanceDFS( &g_airport, airport, x);
            for (const Airport& a : possible_dests){
                destinations.insert(a);
            }
            break;
        }
    }
    if (!flag){
        cout << "airport code not found!"<< endl;
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
        set<string> cities;
        for (const Airport& a: destinations){
            cities.insert(a.getCity());
        }
        for (const string& city : cities){
            cout << city<< endl;
        }
    }
        //countries
    else if (option == 3){
        set<string> countries;
        for (const Airport& a: destinations){
            countries.insert(a.getCountry());
        }
        for (const string& country : countries){
            cout << country<< endl;
        }
    }


}

vector<Airport> Application::nodesAtLessDistanceDFS(const Graph<Airport> *g, const Airport &source, int k) {
    vector<Airport> res;
    Vertex<Airport> * y = g->findVertex(source);
    if (y == nullptr)
        return res;


    for (auto b : g->getVertexSet()){
        b->setVisited(false);
    }
    nodesAtLessDistanceDFSVisit(g, y, k, res);
    return res;
}

void Application::nodesAtLessDistanceDFSVisit(const Graph<Airport> *g, Vertex<Airport> *v, int k, vector<Airport> &res) {

    v->setVisited(true);
    if (k <= 0){
        res.push_back(v->getInfo());
    }
    else{
        for (auto h : v->getAdj()){
            Vertex<Airport> * u = h.getDest();
            if (!u->isVisited()){
                nodesAtLessDistanceDFSVisit(g, u, k-1, res);
            }
        }
    }
}
// funcionalidade 8
int Application::getTotalFlights(const Graph<Airport> *g, Vertex<Airport> * v){
    auto setVertex = g->getVertexSet();
    Airport airport = v->getInfo();
    //outgoing
    int outgoing = v->getAdj().size();
    return v->getIndegree()+outgoing;

}
void Application::getKAirportsGreatestCap(int k){
    vector<int> caps;
   multimap<int, Airport> capacity;
    auto vertexSet = g_airport.getVertexSet();
    for (auto v : vertexSet){
        int vertCap = getTotalFlights(&g_airport, v);
        caps.push_back(vertCap);
        capacity.emplace(vertCap, v->getInfo());
    }
    std::sort(caps.begin(), caps.end(), [](int a, int b) { return a > b; });
    for (int i = 0; i < k; i++){
        auto it = capacity.find(caps[i]);
        if (it != capacity.end()){
            Airport airport = (*it).second;
            airport.print();
            capacity.erase(it);
        }


    }


}

//funcionalidade 9

//unordered_
set<Airport> Application::articulationPoints(Graph<Airport> *g) {
    set<Airport> res;
    //unordered_set<Airport> res;
    if (g->getVertexSet().empty())
        return res;
    auto g_ = g;
    auto verts = g_->getVertexSet();
    for (auto v : verts){
        v->setVisited(false);
        v->setLow(0);
        v->setNum(0);

    }
    int i = 1;
    stack<Airport> s = {};
    for (auto v : verts){
        if (v->getNum() == 0)
            dfs_art(g_, v, s, res, i);
    }
    return res;
}

void Application::dfs_art(Graph<Airport> *g, Vertex<Airport> *v, stack<Airport> &s, set<Airport> &l, int &i){
    v->setNum(i);
    v->setLow(i);
    i++;
    s.push(v->getInfo());
    int children = 0;
    for (auto e : v->getAdj()){
        auto adj = e.getDest();
        stack<Airport> copy = s;
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
            v->setLow(min(v->getLow(), adj->getLow()));
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
            v->setLow(min(v->getLow(), adj->getNum()));
        }
    }
    s.pop();
}

void Application::essentialAirports(){
    set<Airport> airports =  articulationPoints(&g_airport);
    cout << endl<< "Essential Airports: " << endl;
    for (const Airport& a : airports){
        a.print();
    }

}
