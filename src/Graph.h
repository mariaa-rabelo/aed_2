//
// Created by user on 05-Dec-23.
//

#ifndef AED_2_GRAPH_H
#define AED_2_GRAPH_H
#include <unordered_map>
#include <string>
#include <vector>
#include "Airport.h"
#include "Flight.h"

class Graph {
private:
    std::unordered_map<std::string, Airport*> airports;
    std::unordered_map<std::string, Airline*> airlines;
    std::vector<Flight*> flights;

public:
    Graph();
    ~Graph();

    void addAirport(const std::string& code, const std::string& name, const std::string& city, const std::string& country, double latitude, double longitude);
    void addAirline(const std::string& code, const std::string& name, const std::string& callsign, const std::string& country);
    void addFlight(Airport* source, Airport* destination, Airline* airline);

    Airport* getAirport(const std::string& code) const;
    Airline* getAirline(const std::string& code) const;
    std::vector<Flight*> getFlightsFromAirport(const std::string& airportCode) const;
};

#endif //AED_2_GRAPH_H
