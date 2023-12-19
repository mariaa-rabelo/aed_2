//
// Created by user on 05-Dec-23.
//

#include "Application.h"

Application::Application() {}

void Application::run() {
    FileReader airlines_file("../dataset/airlines.csv", g_airport);
    FileReader airports_file("../dataset/airports.csv", g_airport);
    FileReader flights_file("../dataset/flights.csv", g_airport);

    airports_file.readAirports();
    airlines_file.readAirlines();
    flights_file.readFlights();

    // Example: Print the number of airports in the graph
    //std::cout << "Number of airports: " << graph.getNumAirports() << std::endl;
}

