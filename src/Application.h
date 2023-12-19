//
// Created by user on 05-Dec-23.
//

#ifndef AED_2_APPLICATION_H
#define AED_2_APPLICATION_H

#include "FileReader.h"
#include "Graph.h"
#include "Airport.h"


class Application {
private:
    Graph<Airport> g_airport;

public:
    Application();
    void run();
};


#endif //AED_2_APPLICATION_H
