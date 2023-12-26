//
// Created by micaela_albino on 25-12-2023.
//

#include <map>

#include <iostream>
#include "FlightOption.h"
#include "Airport.h"
using namespace std;
FlightOption::FlightOption() {

}

set<vector<Airport>> FlightOption::flights(const Graph<Airport> *g, Vertex<Airport>* src, Vertex<Airport>* dest){
    auto verts = g->getVertexSet();
    for (auto v : verts){
        v->setVisited(false);
    }
    //Vertex<Airport>* v1 = verts[1];
    //Vertex<Airport>* v2 = verts[3];
    std::set<vector<Airport>> path;
    //dfsFlightVisit(g, v1, v2, path);
    path = bfsFlightVisit(g ,src, dest);

    return path;
}



//ver se source existe
//ver se dest existe
//ver se source != dest

set<vector<Airport>> FlightOption::bfsFlightVisit(const Graph<Airport> *g, Vertex<Airport> *source, Vertex<Airport> *dest ){
    set<vector<Airport>> res;
    map<Airport, std::vector<Airport>> pred;
    vector<Airport> p = {};
    auto verts = g->getVertexSet();
    for (auto v : verts){
        v->setVisited(false);
        pred.emplace(v->getInfo(), p);
    }

    queue<Vertex<Airport>*> q;
    queue<Vertex<Airport>*> aux;
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