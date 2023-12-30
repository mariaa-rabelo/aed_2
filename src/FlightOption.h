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

class FlightOption{
private:

public:
    FlightOption();

    // com filtros
    std::set<std::vector<Vertex<Airport>*>>getAllPaths( const Graph<Airport> *g, Vertex<Airport> *source, Vertex<Airport> *dest);
    bool dfsFlightVisit(const Graph<Airport> *g, Vertex<Airport> *source, Vertex<Airport> *dest, std::vector<Vertex<Airport>*> &path, std::set<std::vector<Vertex<Airport>*>> &all_paths );
    std::set<std::vector<Vertex<Airport>*>> flightsChoosenAirlines(const Graph<Airport> *g, std::set<std::vector<Vertex<Airport>*>>& paths, std::set<std::string>& airlines);
    std::set<std::vector<Airport>> flightsMaxAirlineNumber(const Graph<Airport> *g, std::set<std::vector<Airport>>& paths, int maxAirlines);
    std::set<std::vector<Airport>> bfsFlightVisitFilter(const Graph<Airport> *g, Vertex<Airport> *source, Vertex<Airport> *dest, std::set<std::string>& airlines );
    Graph<Airport> removeEdgeGivenAirline(const Graph<Airport> *g, std::set<std::string>& airlines );
        // sem filtros
    std::set<std::vector<Airport>>  flights(const Graph<Airport> *g, Vertex<Airport>* src, Vertex<Airport>* dest);
    std::set<std::vector<Airport>> bfsFlightVisit(const Graph<Airport> *g, Vertex<Airport> *source, Vertex<Airport> *dest);

};
#endif //AED_2_FLIGHTOPTION_H
