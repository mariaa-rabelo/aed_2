//
// Created by user on 05-Dec-23.
//

#ifndef AED_2_FILEREADER_H
#define AED_2_FILEREADER_H

#include <fstream>
#include <sstream>
#include <iostream>
#include "Airline.h"
#include "Airport.h"
#include "Flight.h"
#include "Graph.h"


class FileReader {
private:
    std::ifstream file_;
public:
    explicit FileReader(const std::string& file_name);
    void readAirports();
    void readAirlines();
    void readFlights();
};

#endif //AED_2_FILEREADER_H
