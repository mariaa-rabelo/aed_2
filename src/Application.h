//
// Created by user on 05-Dec-23.
//

#ifndef AED_2_APPLICATION_H
#define AED_2_APPLICATION_H

#include "FlightOption.h"
#include "FileReader.h"
#include "Graph.h"
#include "Airport.h"
#include <vector>
#include <string>
#include <unordered_set>
#include <set>

class Application {
private:
    Graph<Airport> g_airport;
    FlightOption flightOption;

public:
    Application();

    void run();
    int getNumAirports() const;
    int getGlobalNumFlights() const;

    //func2
    int getOutFlights(const std::string& airportCode) const;
    int getUniqueAirlines(const std::string& airportCode) const;

    //func3
    int getFlightsByCity(const std::string& cityName);
    int getFlightsByAirline(const std::string& airlineCode);

    //func4
    int getUniqueCountriesFromAirport(const std::string& airportCode);
    int getUniqueCountriesFromCity(const std::string& cityName);

    //func5
    int getUniqueAirportsFromAirport(const std::string& airportCode);
    int getUniqueCitiesFromAirport(const std::string& airportCode);

    void findAirportMaxX(std::string code, int x, int option);

    std::vector<Airport> nodesAtLessDistanceBFS(const Graph<Airport> *g, const Airport &source, int k);

    int getTotalFlights(const Graph<Airport> *g, Vertex<Airport> *v);

    void getKAirportsGreatestCap(int k);

    void essentialAirports();

    std::set<Airport> articulationPoints(Graph<Airport> *g);

    void dfs_art(Graph<Airport> *g, Vertex<Airport> *v, std::stack<Airport> &s, std::set<Airport> &l, int &i);

    std::vector<std::pair<Airport, int>> getMaxPathBFS(Vertex<Airport> *v, Graph<Airport> *g);

    void maximumTrip();

    //BestFlightOption
    bool getAirportsInCity(const std::string& city, const std::string& country, std::set<Vertex<Airport>*>res);
    bool getAirport(const std::string& identifier, bool opt, Vertex<Airport>* &vert);
    void getBestFlightOption(Vertex<Airport>* src, Vertex<Airport>* dest );

};



#endif //AED_2_APPLICATION_H
