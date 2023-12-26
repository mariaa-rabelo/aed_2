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

using namespace std;

class Application {
private:
    Graph<Airport> g_airport;
    FlightOption flightOption;

public:
    Application();

    void run();

    void findAirportMaxX(string code, int x, int option);

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
