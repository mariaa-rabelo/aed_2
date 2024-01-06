//
// Created by micaela_albino on 25-12-2023.
//

#include <map>
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
            q.pop();
            v->setVisited(true);
            for (auto e: v->getAdj()) {
                auto neig = e.getDest();
                if (!neig->isVisited()) {
                    pred[neig->getInfo()] = pred[v->getInfo()];
                    pred[neig->getInfo()].push_back(v->getInfo());
                    aux.push(neig);
                    if (neig == dest) {
                        foundDest = true;
                        neig->setVisited(false);
                        pred[neig->getInfo()].push_back(neig->getInfo());
                        res.insert(pred[neig->getInfo()]);
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

std::vector<std::stack<std::pair<Airport, std::string>>> FlightOption::bfsFlightVisitFilter(const Graph<Airport> *g, Vertex<Airport> *source,Vertex<Airport> *dest ){
    std::stack<std::pair<Airport, std::string>> stc = {};
    std::vector<std::stack<std::pair<Airport, std::string>>> p = {stc};
    auto verts = g->getVertexSet();
    for (auto v : verts){
        v->setVisited(false);
    }
    // não existe nenhum path entre src e dest
   // std::cout << "helper"<<std::endl;
    if (!helperDFS(g, source, dest)){
        return p;
    }
    //std::cout<< "....."<<std::endl;

    std::vector<std::stack<std::pair<Airport, std::string>>> res;
    std::map<Airport, std::vector<std::stack<std::pair<Airport, std::string>>>> pred;
    std::pair<Airport, std::string> srcPair = std::make_pair(source->getInfo(), "");

    for (auto v : verts){
        v->setVisited(false);
        pred.emplace(v->getInfo(), p);
    }
    std::queue<Vertex<Airport>*> q;
    std::queue<Vertex<Airport>*> aux;
    source->setVisited(true);
    q.push(source);
    bool foundDest= false;
    while (!q.empty()) {
        while (!q.empty()) {
            auto v = q.front();
            q.pop();
            for (auto e: v->getAdj()) {
                auto neig = e.getDest();
                if (!neig->isVisited()) {
                    if (pred[neig->getInfo()].size() == 1 && pred[neig->getInfo()][0].empty()){
                        pred[neig->getInfo()] = pred[v->getInfo()];
                        std::pair<Airport, std::string> new_pair(v->getInfo(),e.getAirline()->getCode());
                        for (auto& prev_path : pred[neig->getInfo()]){
                            prev_path.push(new_pair);
                        }
                    }
                    else {
                        for (const auto& previous_path : pred[v->getInfo()]){
                            pred[neig->getInfo()].push_back(previous_path);
                            std::pair<Airport, std::string> new_pair(v->getInfo(),e.getAirline()->getCode());
                            pred[neig->getInfo()][pred[neig->getInfo()].size()-1].push(new_pair);

                        }
                    }
                    aux.push(neig);
                    if (neig == dest) {
                        foundDest = true;
                        neig->setVisited(false);
                    }
                }
            }
        }

        if (foundDest ){
            res = pred[dest->getInfo()];
            return res;
        }
        while (!aux.empty()){
            auto vert = aux.front();
            vert->setVisited(true);
            q.push(vert);
            aux.pop();
        }

    }
    res = pred[dest->getInfo()];
    return res;

}

std::set<std::vector<std::pair<Airport,std::string>>> FlightOption::flightsMaxAirlineNumber(const Graph<Airport> *g, std::set<std::vector<Airport>>& paths, int maxAirlines){
    std::set<std::vector<std::pair<Airport,std::string>>> res;
    // numero de airlines
    int minSize = 100;
    for (const auto& path : paths){
        auto current_size = path.size();
        if( current_size< minSize){
            minSize = current_size;
        }
    }
    for (const auto& path : paths) {
        if (path.size() > minSize){
            continue;
        }
        std::vector<std::pair<Airport,std::string>> final_path;
        std::vector<Vertex<Airport> *> verts_of_path;
        for (const auto &airport: path) {
            Vertex<Airport> *v = g->findVertex(airport);
            verts_of_path.push_back(v);
        }
        //airlines de cada path;
        std::set<Airline*> airlines;
        // encontrar voo entre src -> dst
        final_path.push_back(std::make_pair(verts_of_path[0]->getInfo(), ""));
        for (int i = 1; i < verts_of_path.size(); i++){
            Vertex<Airport>* src = verts_of_path[i-1];
            Vertex<Airport>* dst = verts_of_path[i];
            for (auto& e : src->getAdj()){
                auto neig = e.getDest();
                if (neig == dst){
                    Airline* airline = e.getAirline();
                    final_path.push_back(make_pair(dst->getInfo(), airline->getCode()));
                    // airline nova
                    if (airlines.find(airline) == airlines.end()){
                        airlines.insert(airline);
                    }
                    break;
                }
            }
        }
        if (airlines.size() <= maxAirlines){
            res.insert(final_path);
        }
    }
    return res;
}

Graph<Airport>  FlightOption::removeEdgeGivenAirline(const Graph<Airport> *g, std::set<std::string>& airlines ){
    Graph<Airport> new_graph;

    for (auto v : g->getVertexSet()){
        for (auto edge : v->getAdj()){
            if (airlines.find(edge.getAirline()->getCode()) != airlines.end()){
                new_graph.addVertex(v->getInfo());
                new_graph.addVertex(edge.getDest()->getInfo());
                new_graph.addEdge(v->getInfo(), edge.getDest()->getInfo(), edge.getAirline());
            }
        }
    }
    return new_graph;
}

bool FlightOption::helperDFS( const Graph<Airport> *g, Vertex<Airport> *src,  Vertex<Airport> *dest){
    if (src->getInfo().getCode() == dest->getInfo().getCode())
        return true;
    src->setVisited(true);
    //std::cout << src->getInfo().getCode()<<std::endl;
    for (auto e : src->getAdj()){
        auto adj = e.getDest();
        if (!adj->isVisited()){
            if (helperDFS(g, adj, dest)){
                return true;
            }
        }
    }
    return false;
}