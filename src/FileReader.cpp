//
// Created by user on 05-Dec-23.
//
// FileReader.cpp

#include "FileReader.h"

FileReader::FileReader(const std::string& file_name, Graph<Airport>& graph)
    : graph_(graph) {
    file_.open(file_name);
    if (!file_.is_open()) {
        std::cerr << "Error opening file: " << file_name << std::endl;
    }
}

void FileReader::readAirports() {
    std::string line;
    std::getline(file_, line);
    while(std::getline(file_, line)) {
        std::istringstream iss(line);
        std::string code, name, city, country, lat, lon;
        std::getline(iss, code, ',');
        std::getline(iss, name, ',');
        std::getline(iss, city, ',');
        std::getline(iss, country, ',');
        std::getline(iss, lat, ',');
        std::getline(iss, lon, ',');

        Airport airport(code, name, city, country, std::stod(lat), std::stod(lon));
        graph_.addVertex(airport);
    }
    file_.close();
}

void FileReader::readAirlines() {
    std::string line;
    std::getline(file_, line);  // Ignore the header line
    while(std::getline(file_, line)) {
        std::istringstream iss(line);
        std::string code, name, callsign, country;
        std::getline(iss, code, ',');
        std::getline(iss, name, ',');
        std::getline(iss, callsign, ',');
        std::getline(iss, country, ',');

        Airline airline(code, name, callsign, country);
        graph_.addAirline(airline);
    }
    file_.close();
}

void FileReader::readFlights() {
    std::string line;
    std::getline(file_, line);  // Ignore the header line
    while(std::getline(file_, line)) {
        std::istringstream iss(line);
        std::string sourceCode, targetCode, airlineCode;
        std::getline(iss, sourceCode, ',');
        std::getline(iss, targetCode, ',');
        std::getline(iss, airlineCode, ',');

        auto source = graph_.findVertex(sourceCode);
        auto target = graph_.findVertex(targetCode);
        auto airline = graph_.findAirline(airlineCode);

        if (source && target && airline) {
            graph_.addEdge(source, target, airline);
        } else {
            // Handle the case where source, target, or airline is not found
            std::cerr << "Error: Source, target, or airline not found." << std::endl;
        }
    }
    file_.close();
}
