//
// Created by user on 05-Dec-23.
//

#ifndef AED_2_APPLICATION_H
#define AED_2_APPLICATION_H

#include "FileReader.h"
#include "Graph.h"
#include "Airport.h"
#include <vector>
#include <string>

using namespace std;

class Application {
private:
    Graph<Airport> g_airport;

public:
    Application();
    void run();
    void findAirportMaxX( string code, int x, int option);
    void nodesAtLessDistanceDFSVisit(const Graph<Airport> *g, Vertex<Airport> *v, int k, vector<Airport> &res);
    vector<Airport> nodesAtLessDistanceDFS(const Graph<Airport> *g, const Airport &source, int k);
    int getTotalFlights(const Graph<Airport> *g, Vertex<Airport> * v);
    void getKAirportsGreatestCap(int k);
};


#endif //AED_2_APPLICATION_H
