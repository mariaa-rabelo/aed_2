//
// Created by user on 05-Dec-23.
//

#include "Application.h"
#include <set>
#include <algorithm>
#include <map>
//#include <string>

using namespace  std;

Application::Application() {}

void Application::run() {
    FileReader airlines_file("../dataset/airlines1.csv", g_airport);
    FileReader airports_file("../dataset/airports1.csv", g_airport);
    FileReader flights_file("../dataset/flights1.csv", g_airport);

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
    /*
    for (auto node: setVertex){
        node->setVisited(false);
    }*/
    for (auto node: setVertex){
        auto airport = node->getInfo();
        if ( airport.getCode() ==  code){
            flag = true;
            vector<Airport> possible_dests = nodesAtLessDistanceBFS( &g_airport, airport, x);
            for (const Airport& a : possible_dests){
                //if (a.getCode() != code)
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

vector<Airport> Application::nodesAtLessDistanceBFS(const Graph<Airport> *g, const Airport &source, int k) {
    vector<Airport> res;

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
    queue<Vertex<Airport>*> vert;
    queue<Vertex<Airport>*> aux;
    //cout<< "L";
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
    vector<pair<Airport,Airport>> res;
    map<Airport, vector<pair<Airport, int>>> paths;
    vector<int> max_pathsV;
    auto verts = g_airport.getVertexSet();
    for (auto v : verts){
        for (auto v_ : verts){
            v_->setVisited(false);
        }
        vector<pair<Airport, int>> max_path = getMaxPathBFS(v, &g_airport);
        for (const pair<Airport, int>& p : max_path){
            max_pathsV.push_back(p.second);
        }
        auto v_paths = make_pair(v->getInfo(), max_path);
        paths.insert(v_paths);

    }
    //encontrar lenght de max_path
    int max = *max_element(max_pathsV.begin(), max_pathsV.end());
    //colocar em res todos os que têm max_lenght
    for (const auto& p : paths){
        //cout <<"b: "<<endl;
        //p.first.print();
        //cout <<"endl: "<<endl;
        for (const auto& k : p.second){
            //k.first.print();
            if (k.second == max){
                res.emplace_back(p.first, k.first);
            }
        }
    }
    cout << "res:"<<endl;
    for (const auto& p : res){
        cout <<"from:"<< endl;
        p.first.print();
        cout << "to: "<<endl;
        p.second.print();
    }

}

vector<pair<Airport, int>> Application::getMaxPathBFS( Vertex<Airport> *v, Graph<Airport> *g){
    //vector<pair<Vertex<Airport>, int>> res;
    vector<pair<Airport, int>> res;
    int level = 0;
    queue<Vertex<Airport>*> vert;
    queue<Vertex<Airport>*> aux;
    queue<Vertex<Airport>*> final;
    v->setVisited(true);
    vert.push(v);
    while (!vert.empty()){
        //cout << "h";
        while (!vert.empty()){

            Vertex<Airport> * current = vert.front();
            vert.pop();
        //    cout << "being analized:" << endl;
        //    current->getInfo().print();
        //    cout << "adj:" << endl;
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
        }/*
        cout << "tf?";
        queue<Vertex<Airport>*> some = aux;
        while (!some.empty()){
            some.front()->getInfo().print();
            some.pop();
        }*/
        vert = aux;
        aux = {};

    }
    while (!final.empty()){
        Airport ar= final.front()->getInfo();
        //Vertex<Airport> frontV = *vert.front();
        res.push_back(make_pair(ar, level));
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
    for (auto n : verts){
        for (auto e : n->getAdj()){
            g->addEdge(e.getDest()->getInfo(), n->getInfo(), 0);
        }
    }
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
