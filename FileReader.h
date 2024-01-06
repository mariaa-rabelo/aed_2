/**
 * @file FileReader.h
 * @brief Defines the FileReader class for reading data from files and populating the graph.
 *
 * Created by user on 05-Dec-23.
 */

#ifndef AED_2_FILEREADER_H
#define AED_2_FILEREADER_H

#include <fstream>
#include <sstream>
#include <iostream>
#include "Airline.h"
#include "Airport.h"
#include "Graph.h"

/**
 * @class FileReader
 * @brief Class for reading and parsing data from files to populate a graph.
 *
 * This class is responsible for opening and reading data from specified files, such as airports, airlines, and flights,
 * and populating a graph with this data.
 */
class FileReader {
private:
    std::ifstream file_; ///< File stream used to read data.
    Graph<Airport>& graph_; ///< Reference to the graph to populate.

public:
    /**
     * @brief Constructs a FileReader object with the provided file name and graph.
     *
     * @param file_name The name of the file to read from.
     * @param graph Reference to the graph to be populated with the data.
     */
    explicit FileReader(const std::string& file_name, Graph<Airport>& graph);

    /**
     * @brief Reads and processes airport data from the file and populates the graph.
     */
    void readAirports();

    /**
     * @brief Reads and processes airline data from the file and populates the graph.
     */
    void readAirlines();

    /**
     * @brief Reads and processes flight data from the file and populates the graph.
     */
    void readFlights();
};

#endif //AED_2_FILEREADER_H
