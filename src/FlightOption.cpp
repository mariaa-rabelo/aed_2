//
// Created by micaela_albino on 25-12-2023.
//

#include <map>
#include <iostream>
#include "FlightOption.h"
#include "Airport.h"

FlightOption::FlightOption() {}

std::set<std::vector<Airport>> FlightOption::flights(const Graph<Airport> *g, Vertex<Airport>* src, Vertex<Airport>* dest){
    auto verts = g->getVertexSet();
    for (auto v : verts){
        v->setVisited(false);
    }
    std::set<std::vector<Airport>> path;
    path = bfsFlightVisit(g ,src, dest);

    return path;
}

std::set<std::vector<Airport>> FlightOption::bfsFlightVisit(const Graph<Airport> *g, Vertex<Airport> *source, Vertex<Airport> *dest ){
    std::set<std::vector<Airport>> res;
    std::map<Airport, std::vector<Airport>> pred;
    std::vector<Airport> p = {};
    auto verts = g->getVertexSet();
    for (auto v : verts){
        v->setVisited(false);
        pred.emplace(v->getInfo(), p);
    }

    std::queue<Vertex<Airport>*> q;
    std::queue<Vertex<Airport>*> aux;
    q.push(source);
    source->setVisited(true);
    bool foundDest= false;
    while (!q.empty()) {
        while (!q.empty()) {
            auto v = q.front();
            //cout << "being analized:"<<endl;
            // v->getInfo().print();
            q.pop();
            // cout << "adjacent:"<<endl;
            for (auto e: v->getAdj()) {
                auto neig = e.getDest();
                if (!neig->isVisited()) {
                    //neig->getInfo().print();
                    pred[neig->getInfo()] = pred[v->getInfo()];
                    pred[neig->getInfo()].push_back(v->getInfo());
                    aux.push(neig);
                    if (neig == dest) {
                        foundDest = true;
                        neig->setVisited(false);
                        pred[neig->getInfo()].push_back(neig->getInfo());
                        res.insert(pred[neig->getInfo()]);
                        //return pred[neig->getInfo()];
                    }
                }
            }
        }
        if (foundDest)
            break;
        q = aux;
        aux = {};
    }
    return res;
}

std::set<std::vector<Vertex<Airport>*>> FlightOption::flightsChoosenAirlines(const Graph<Airport> *g, std::set<std::vector<Vertex<Airport>*>>& paths, std::set<std::string>& airlines) {
    std::set<std::vector<Vertex<Airport>*>> res;
    // vê se voos entre aeroportos têm as airlines dadas
    for ( const std::vector<Vertex<Airport>*> &path: paths) {
        bool is_valid = false;
        for (int i = 1; i < path.size(); i++) {
            Vertex<Airport> *src = path[i - 1];
            Vertex<Airport> *dst = path[i];
            auto adjs = src->getAdj();
            // procura de voo entre current src e current dst
            for (auto edge: src->getAdj()) {
                if (edge.getDest() == dst) {
                    is_valid = true;
                    // voo encontrado não tem airline que esteja nas airlines dadas
                    if (airlines.find(edge.getAirline()->getCode()) == airlines.end()) {
                        is_valid = false;
                    }
                    break;
                }
            }
            if (!is_valid)
                break;

        }
        if (is_valid){
            res.insert(path);
        }
    }
    return res;
}


std::set<std::vector<Airport>> FlightOption::flightsMaxAirlineNumber(const Graph<Airport> *g, std::set<std::vector<Airport>>& paths, int maxAirlines){
    std::set<std::vector<Airport>> res;
    for (const auto& path : paths) {
        std::vector<Vertex<Airport> *> verts_of_path;
        for (const auto &airport: path) {
            Vertex<Airport> *v = g->findVertex(airport);
            verts_of_path.push_back(v);
        }
        //airlines de cada path;
        std::set<Airline*> airlines;
        // encontrar voo entre src -> dst
        for (int i = 1; i < verts_of_path.size(); i++){
            Vertex<Airport>* src = verts_of_path[i-1];
            Vertex<Airport>* dst = verts_of_path[i];
            for (auto& e : src->getAdj()){
                auto neig = e.getDest();
                if (neig == dst){
                    Airline* airline = e.getAirline();
                    // airline nova
                    if (airlines.find(airline) == airlines.end()){
                        airlines.insert(airline);
                    }
                }
            }
        }
        if (airlines.size() <= maxAirlines){
            res.insert(path);
        }
    }
    return res;
}

std::set<std::vector<Vertex<Airport>*>> FlightOption::getAllPaths( const Graph<Airport> *g, Vertex<Airport> *source, Vertex<Airport> *dest){
    for (auto v :g->getVertexSet()){
        v->setVisited(false);
    }
    std::vector<Vertex<Airport>*> path;
    std::set<std::vector<Vertex<Airport>*>> all_paths;
    dfsFlightVisit(g, source, dest, path, all_paths);
    return all_paths;
}

bool FlightOption::dfsFlightVisit(const Graph<Airport> *g, Vertex<Airport> *source, Vertex<Airport> *dest,
                                  std::vector<Vertex<Airport>*> &path, std::set<std::vector<Vertex<Airport>*>> &all_paths ){
    source->setVisited(true);
    path.push_back(source);
    if (source == dest){
        source->setVisited(false);
        return true;
    }
    for (auto edge : source->getAdj() ){
        auto neig = edge.getDest();
        if (!neig->isVisited() ){
            if (dfsFlightVisit(g, neig, dest, path, all_paths)) {
                all_paths.insert(path);
                path.pop_back();
            }
        }
    }
    source->setVisited(false);
    path.pop_back();
    return false;
}

std::set<std::vector<Airport>> FlightOption::bfsFlightVisitFilter(const Graph<Airport> *g, Vertex<Airport> *source, Vertex<Airport> *dest, std::set<std::string>& airlines ){
    std::set<std::vector<Airport>> res;
    std::map<Airport, std::vector<Airport>> pred;
    std::vector<Airport> p = {};
    auto verts = g->getVertexSet();
    for (auto v : verts){
        v->setVisited(false);
        pred.emplace(v->getInfo(), p);
    }

    std::queue<Vertex<Airport>*> q;
    std::queue<Vertex<Airport>*> aux;
    q.push(source);
    source->setVisited(true);
    bool foundDest= false;
    while (!q.empty()) {
        while (!q.empty()) {
            auto v = q.front();
            //cout << "being analized:"<<endl;
            // v->getInfo().print();
            q.pop();
            // cout << "adjacent:"<<endl;
            for (auto e: v->getAdj()) {
                auto neig = e.getDest();
                auto it = airlines.find(e.getAirline()->getCode());
                if (!neig->isVisited() && it != airlines.end()) {
                    //neig->getInfo().print();
                    pred[neig->getInfo()] = pred[v->getInfo()];
                    pred[neig->getInfo()].push_back(v->getInfo());
                    aux.push(neig);
                    if (neig == dest) {
                        foundDest = true;
                        neig->setVisited(false);
                        pred[neig->getInfo()].push_back(neig->getInfo());
                        res.insert(pred[neig->getInfo()]);
                        //return pred[neig->getInfo()];
                    }
                }
            }
        }
        if (foundDest)
            break;
        q = aux;
        aux = {};
    }
    return res;
}
/*
set<std::vector><Airport>> FlightOption::flightsChoosenAirlines(const Graph<Airport> *g, set<std::vector><Airport>>& paths, set<string>& airlines ){

    set<std::vector><Airport>> res;

    for (const auto& path : paths){
        vector<Vertex<Airport>*> verts_of_path;
        for (const auto& airport : path){
            Vertex<Airport>* v = g->findVertex(airport);
            verts_of_path.push_back(v);
        }
        bool flag = false;
        // encontrar voo entre src -> dst
        for (int i = 1; i < verts_of_path.size(); i++){
            Vertex<Airport>* src = verts_of_path[i-1];
            Vertex<Airport>* dst = verts_of_path[i];
            for (auto& e : src->getAdj()){
                auto neig = e.getDest();
                if (neig == dst){
                    //airline do voo não está em lista de airlines que quero
                    if (airlines.find(e.getAirline()->getCode()) == airlines.end()){
                        flag = true;
                        break;
                    }
                }
            }
            if (flag){break;}
        }
        //nenhum dos voos entre os aeroportos têm airlines que não foram selecionadas
        if (!flag){
            res.insert(path);
        }

    }

    return res;

}
*/

/*
bool FlightOption::bfsFlightVisit(const Graph<Airport> *g, Vertex<Airport> *source, Vertex<Airport> *dest, vector<Airport> &res ){
    source->setVisited(true);
    res.push_back(source->getInfo());
    if (source == dest){
        return true;
    }
    for (auto & e : source->getAdj()) {
        auto w = e.getDest();
        if ( !w->isVisited()){
            if (bfsFlightVisit(g, w, dest, res)){
                return true;
            }
        }
    }
    res.pop_back();
    return false;


}
*/