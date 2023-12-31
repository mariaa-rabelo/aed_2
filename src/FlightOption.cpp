//
// Created by micaela_albino on 25-12-2023.
//

#include <map>
#include <iostream>
#include "FlightOption.h"
#include "Airport.h"
//using namespace std;
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


std::vector<std::stack<std::pair<Airport, std::string>>> FlightOption::bfsFlightVisitFilter(const Graph<Airport> *g, Vertex<Airport> *source,
                                                                                         Vertex<Airport> *dest ){
    std::vector<std::stack<std::pair<Airport, std::string>>> res;
    std::map<Airport, std::vector<std::stack<std::pair<Airport, std::string>>>> pred;
    std::pair<Airport, std::string> srcPair = std::make_pair(source->getInfo(), "");
    std::stack<std::pair<Airport, std::string>> stc = {};
    std::vector<std::stack<std::pair<Airport, std::string>>> p = {stc};
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
                    if (pred[neig->getInfo()].size() == 1 && pred[neig->getInfo()][0].empty()){
                        pred[neig->getInfo()] = pred[v->getInfo()];
                        std::pair<Airport, std::string> new_pair(v->getInfo(),e.getAirline()->getCode());
                        pred[neig->getInfo()][0].push(new_pair);
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

        if (foundDest)
            break;
        q = aux;
        aux = {};
    }
    res = pred[dest->getInfo()];
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
/*
 bool checkifPathExists(const Graph<Airport> *g, Vertex<Airport> *source,Vertex<Airport> *dest, int max){
    auto verts = g->getVertexSet();
    for (auto v : verts){
        v->setVisited(false);
    }
    std::queue<Vertex<Airport>*> q;
    std::queue<Vertex<Airport>*> aux;
    q.push(source);
    source->setVisited(true);

    while (!q.empty()) {
        while (!q.empty()) {
            auto v = q.front();
            q.pop();
            v->setVisited(true);
            for (auto e: v->getAdj()) {
                auto neig = e.getDest();
                if (!neig->isVisited()) {
                    aux.push(neig);
                    if (neig == dest){
                        return true;
                    }
                }
            }
        }
        max--;
        q = aux;
        aux = {};
        if (max <= 0){
            return false;
        }

    }
}

 */


/*
std::vector<std::stack<std::pair<Airport, std::string>>> FlightOption::flightsMaxAirlineNumber(const Graph<Airport> *g, Vertex<Airport> *source,Vertex<Airport> *dest, int max){

    std::vector<std::stack<std::pair<Airport, std::string>>> res;
    std::map<Airport, std::vector<std::stack<std::pair<Airport, std::string>>>> pred;
    pair<Airport, std::string> srcPair = make_pair(source->getInfo(), "");
    stack<std::pair<Airport, std::string>> stc = {};
    std::vector<std::stack<std::pair<Airport, std::string>>> p = {stc};
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
        //cout << "ASD?"<< endl;
        while (!q.empty()) {
            auto v = q.front();
            q.pop();
            v->setVisited(true);
            for (auto e: v->getAdj()) {
                auto neig = e.getDest();
                if (!neig->isVisited()) {
                    if (pred[neig->getInfo()].size() == 1 && pred[neig->getInfo()][0].empty()){
                        pred[neig->getInfo()] = pred[v->getInfo()];
                        pair<Airport, std::string> new_pair(v->getInfo(),e.getAirline()->getCode());
                        pred[neig->getInfo()][0].push(new_pair);
                    }
                    else {
                        for (const auto& previous_path : pred[v->getInfo()]){
                            pred[neig->getInfo()].push_back(previous_path);
                            pair<Airport, std::string> new_pair(v->getInfo(),e.getAirline()->getCode());
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
        max--;
        if (foundDest ||max == 0)
            break;

        q = aux;
        aux = {};
    }
    res = pred[dest->getInfo()];
    return res;





}

*/



/*
std::set<std::stack<std::pair<Airport, std::string>>> FlightOption::bfsFlightVisitFilter(const Graph<Airport> *g, Vertex<Airport> *source,
                                                            Vertex<Airport> *dest ){
    std::set<std::stack<std::pair<Airport, std::string>>> res;
    std::map<Airport, std::set<std::stack<std::pair<Airport, std::string>>>> pred;

    std::set<std::stack<std::pair<Airport, std::string>>> p = {};
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
                    //neig->getInfo().print();
                    pred[neig->getInfo()].insert(pred[v->getInfo()].begin(), pred[v->getInfo()].end());

                    for ( auto path : pred[neig->getInfo()]){
                        pair<Airport, std::string> new_pair(v->getInfo(),e.getAirline()->getCode());
                        path.emplace(new_pair);
                    }
                    //pred[neig->getInfo()] = pred[v->getInfo()];
                    //pred[neig->getInfo()].push_back(v->getInfo());
                    aux.push(neig);
                    if (neig == dest) {
                        foundDest = true;
                        neig->setVisited(false);
                        for ( stack<pair<Airport, basic_string<char>>> path : pred[neig->getInfo()]){
                            pair<Airport, std::string> new_pair(neig->getInfo(),"");
                            path.emplace(new_pair);
                        }

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
    res = pred[dest->getInfo()];
    return res;

}
*/

/*
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
            q.pop();
            //v->setVisited(true);
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
*/

/*

std::set<std::vector<Vertex<Airport>*>> FlightOption::getAllPaths( const Graph<Airport> *g, Vertex<Airport> *source, Vertex<Airport> *dest){
    for (auto v :g->getVertexSet()){
        v->setVisited(false);
    }
    std::vector<Vertex<Airport>*> path;
    std::set<std::vector<Vertex<Airport>*>> all_paths;
    dfsFlightVisit(g, source, dest, path, all_paths);
    return all_paths;
}

 */


/*

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

 */