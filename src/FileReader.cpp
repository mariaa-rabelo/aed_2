//
// Created by user on 05-Dec-23.
//
// FileReader.cpp

#include "FileReader.h"

FileReader::FileReader(const std::string& file_name) {
    file_.open(file_name);
    if (!file_.is_open()) {
        std::cerr << "Error opening file: " << file_name << std::endl;
    }
}

void FileReader::readAirports() {
    // Implementation for reading airports
}

void FileReader::readAirlines() {
    // Implementation for reading airlines
}

void FileReader::readFlights() {
    // Implementation for reading flights
}
