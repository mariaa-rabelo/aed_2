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
        std::string value;
        std::vector<std::string> v;
        while (std::getline(iss, value, ',')) {
            v.push_back(value);
        }
        Airport airport(v.at(0), v.at(1), v.at(2),v.at(3), std::stod(v.at(4)), std::stod(v.at(5)));
        graph_.addVertex(airport);
    }
    file_.close();
}

void FileReader::readAirlines() {
    // Implementation for reading airlines
}

void FileReader::readFlights() {
    // Implementation for reading flights
}
