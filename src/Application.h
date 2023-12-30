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
    void findAllDestinations(const std::string airportCode);

    //func6
    void findAirportMaxX(std::string code, int x, int option);
    std::vector<Airport> nodesAtLessDistanceBFS(const Graph<Airport> *g, const Airport &source, int k);

    //func7
    void maximumTrip();
    std::vector<std::pair<Airport, int>> getMaxPathBFS(Vertex<Airport> *v, Graph<Airport> *g);

    //func8
    int getTotalFlights(const Graph<Airport> *g, Vertex<Airport> *v);
    void getKAirportsGreatestCap(int k);

    //func9
    std::set<Airport> articulationPoints(Graph<Airport> *g);
    void dfs_art(Graph<Airport> *g, Vertex<Airport> *v, std::stack<Airport> &s, std::set<Airport> &l, int &i);
    void essentialAirports();

    //BestFlightOption

    // sem filtros
    double haversineDistance(double lat1, double lon1, double lat2, double lon2);
    void getBestFlightOption(std::pair<std::string, std::string> src, std::pair<std::string, std::string> dest);
    std::vector<Airport> findShortestPath(Vertex<Airport> *src, Vertex<Airport> *dest);
    std::set<Vertex<Airport> *> getVerticesBasedOnInput(std::pair<std::string, std::string> pair1);

    // com filtros
    void bestFlightOptGivenAirports(std::set<std::string> &airlines, Vertex<Airport> *src, Vertex<Airport> *dest);
    void bestFlightOptMaxAirports(int maxAirlines, Vertex<Airport> *src, Vertex<Airport> *dest);

    //auxiliar
    Vertex<Airport>* getVertex(std::string v, const Graph<Airport> *g);
        Vertex<Airport> *getVertex(std::string v);
    bool checkIfExists(const std::string &code);
};
#endif //AED_2_APPLICATION_H
