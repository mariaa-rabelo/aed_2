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
    std::set<std::vector<Airport>>  flights(const Graph<Airport> *g, Vertex<Airport>* src, Vertex<Airport>* dest);
    std::set<std::vector<Airport>> bfsFlightVisit(const Graph<Airport> *g, Vertex<Airport> *source, Vertex<Airport> *dest);

};
#endif //AED_2_FLIGHTOPTION_H
