//
// Created by micaela_albino on 24-12-2023.
//

#ifndef AED_2_FLIGHTOPTION_H
#define AED_2_FLIGHTOPTION_H

#include "Airport.h"
#include "Graph.h"
#include <vector>
#include <set>
#include <map>

using namespace std;
class FlightOption{
private:

public:
    FlightOption();

    // com filtros
    set<vector<Vertex<Airport>*>>getAllPaths( const Graph<Airport> *g, Vertex<Airport> *source, Vertex<Airport> *dest);
    bool dfsFlightVisit(const Graph<Airport> *g, Vertex<Airport> *source, Vertex<Airport> *dest,vector<Vertex<Airport>*> &path, set<vector<Vertex<Airport>*>> &all_paths );
    set<vector<Vertex<Airport>*>> flightsChoosenAirlines(const Graph<Airport> *g, set<vector<Vertex<Airport>*>>& paths, set<string>& airlines);
    set<vector<Airport>> flightsMaxAirlineNumber(const Graph<Airport> *g, set<vector<Airport>>& paths, int maxAirlines);
    set<vector<Airport>> bfsFlightVisitFilter(const Graph<Airport> *g, Vertex<Airport> *source, Vertex<Airport> *dest, set<string>& airlines );
        // sem filtros
    set<vector<Airport>>  flights(const Graph<Airport> *g, Vertex<Airport>* src, Vertex<Airport>* dest);
    set<vector<Airport>> bfsFlightVisit(const Graph<Airport> *g, Vertex<Airport> *source, Vertex<Airport> *dest);

};
#endif //AED_2_FLIGHTOPTION_H
