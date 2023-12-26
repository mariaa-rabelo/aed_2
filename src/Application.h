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
    std::map<std::string, int> getFlightsByCity();
    std::map<std::string, int> getFlightsByAirline();

    //func4
    int getUniqueCountriesFromAirport(const std::string& airportCode);
    int getUniqueCountriesFromCity(const std::string& cityName);

    //func5
    int getUniqueAirportsFromAirport(const std::string& airportCode);
    int getUniqueCitiesFromAirport(const std::string& airportCode);

    void findAirportMaxX(std::string code, int x, int option);

    vector<Airport> nodesAtLessDistanceBFS(const Graph<Airport> *g, const Airport &source, int k);

    int getTotalFlights(const Graph<Airport> *g, Vertex<Airport> *v);

    void getKAirportsGreatestCap(int k);

    void essentialAirports();

    set<Airport> articulationPoints(Graph<Airport> *g);

    void dfs_art(Graph<Airport> *g, Vertex<Airport> *v, stack<Airport> &s, set<Airport> &l, int &i);

    vector<pair<Airport, int>> getMaxPathBFS(Vertex<Airport> *v, Graph<Airport> *g);

    void maximumTrip();

    //BestFlightOption
    bool getAirportsInCity(const string& city, const string& country, set<Vertex<Airport>*>res);
    bool getAirport(const string& identifier, bool opt, Vertex<Airport>* &vert);
    void getBestFlightOption(Vertex<Airport>* src, Vertex<Airport>* dest );
};



#endif //AED_2_APPLICATION_H
