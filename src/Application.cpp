//
// Created by user on 05-Dec-23.
//

#include "Application.h"

Application::Application() {}

void Application::run() {
    FileReader airlines_file("../dataset/airlines.csv");
    FileReader airports_file("../dataset/airports.csv");
    FileReader flights_file("../dataset/flights.csv");
    airlines_file.readAirports();
    airports_file.readAirlines();
    flights_file.readFlights();


    // Example: Print the number of airports in the graph
    //std::cout << "Number of airports: " << graph.getNumAirports() << std::endl;
}

