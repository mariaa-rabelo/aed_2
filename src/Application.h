/**
 * @file Application.h
 * @brief Defines the Application class, which handles the main functionalities of the airport management system.
 * @date 05-Dec-2023
 */

#ifndef AED_2_APPLICATION_H
#define AED_2_APPLICATION_H

#include <vector>
#include <string>
#include <unordered_set>
#include <set>
#include "FlightOption.h"
#include "FileReader.h"
#include "Graph.h"
#include "Airport.h"

/**
 * @class Application
 * @brief Manages the main functionalities of the airport management system including graph operations and flight options.
 */
class Application {
private:
    Graph<Airport> g_airport;           ///< Graph representing the network of airports.
    FlightOption flightOption;          ///< Manages different flight options.
public:
    /**
     * @brief Constructor for the Application class.
     */
    Application();

    /**
     * @brief Runs the main loop of the application.
     */
    void run();

    /**
     * @brief Gets the total number of airports in the graph.
     * @return Total number of airports.
     */
    int getNumAirports() const;

    /**
     * @brief Gets the total number of flights in the graph.
     * @return Total number of flights.
     */
    int getGlobalNumFlights() const;

    /**
     * @brief Gets the number of outgoing flights from a specified airport.
     * @param airportCode The code of the airport.
     * @return Number of outgoing flights.
     */
    int getOutFlights(const std::string& airportCode) const;

    /**
     * @brief Gets the number of unique airlines operating from a specified airport.
     * @param airportCode The code of the airport.
     * @return Number of unique airlines.
     */
    int getUniqueAirlines(const std::string& airportCode) const;

    /**
     * @brief Gets the number of flights departing from a specified city.
     * @param cityName The name of the city.
     * @return Number of flights.
     */
    int getFlightsByCity(const std::string& cityName);

    /**
     * @brief Gets the number of flights operated by a specified airline.
     * @param airlineCode The code of the airline.
     * @return Number of flights.
     */
    int getFlightsByAirline(const std::string& airlineCode);

    /**
     * @brief Gets the number of unique countries directly reachable from a specified airport.
     * @param airportCode The code of the airport.
     * @return Number of unique countries.
     */
    int getUniqueCountriesFromAirport(const std::string& airportCode);

    /**
     * @brief Gets the number of unique countries directly reachable from a specified city.
     * @param cityName The name of the city.
     * @return Number of unique countries.
     */
    int getUniqueCountriesFromCity(const std::string& cityName);

    /**
     * @brief Finds all destinations reachable from a specified airport.
     * @param airportCode The code of the airport.
     */
    void findAllDestinations(const std::string& airportCode);

    /**
     * @brief Finds airports reachable within a maximum number of stops from a specified airport.
     * @param code The code of the airport.
     * @param x Maximum number of stops.
     * @param option Type of destination to find (airports, cities, countries).
     */
    void findAirportMaxX(std::string code, int x, int option);

    /**
     * @brief Finds nodes (airports) at a distance less than or equal to a given number of stops.
     * @param g Pointer to the airport graph.
     * @param source Source airport.
     * @param k Maximum number of stops.
     * @return Vector of airports within the specified distance.
     */
    std::vector<Airport> nodesAtLessDistanceBFS(const Graph<Airport> *g, const Airport &source, int k);

    /**
     * @brief Plans a maximum trip, finding the longest path in the graph.
     */
    void maximumTrip();

    /**
     * @brief Finds the maximum path from a specified vertex in the graph using BFS.
     * @param v Pointer to the vertex (airport).
     * @param g Pointer to the airport graph.
     * @return Vector of pairs containing airports and their respective distances.
     */
    std::vector<std::pair<Airport, int>> getMaxPathBFS(Vertex<Airport> *v, Graph<Airport> *g);

    /**
     * @brief Gets the total number of flights associated with a specified vertex (airport).
     * @param g Pointer to the airport graph.
     * @param v Pointer to the vertex (airport).
     * @return Total number of flights.
     */
    int getTotalFlights(const Graph<Airport> *g, Vertex<Airport> *v);

    /**
     * @brief Finds the top K airports with the greatest capacity.
     * @param k Number of airports to find.
     */
    void getKAirportsGreatestCap(int k);

    /**
     * @brief Finds articulation points in the graph, representing essential airports.
     * @param g Pointer to the airport graph.
     * @return Set of essential airports.
     */
    std::set<Airport> articulationPoints(Graph<Airport> *g);

    /**
     * @brief Depth-first search algorithm to find articulation points.
     * @param g Pointer to the airport graph.
     * @param v Pointer to the vertex (airport).
     * @param s Reference to a stack of airports.
     * @param l Reference to a set of essential airports.
     * @param i Integer for numbering vertices.
     */
    void dfs_art(Graph<Airport> *g, Vertex<Airport> *v, std::stack<Airport> &s, std::set<Airport> &l, int &i);

    /**
     * @brief Identifies essential airports in the network.
     */
    void essentialAirports();

    /**
     * @brief Calculates the Haversine distance between two geographical points.
     * @param lat1 Latitude of the first point.
     * @param lon1 Longitude of the first point.
     * @param lat2 Latitude of the second point.
     * @param lon2 Longitude of the second point.
     * @return Haversine distance.
     */
    double haversineDistance(double lat1, double lon1, double lat2, double lon2);

    /**
     * @brief Finds and displays the best flight option(s) based on the given source and destination inputs.
     *
     * @param src A pair representing the source location's type and identifier (e.g., airport code, name, city).
     * @param dest A pair representing the destination location's type and identifier.
     */
    void getBestFlightOption(std::pair<std::string, std::string> src, std::pair<std::string, std::string> dest);

    /**
     * @brief Finds the shortest path (least number of stops) between two airports.
     *
     * @param src Pointer to the source airport vertex.
     * @param dest Pointer to the destination airport vertex.
     * @return std::vector<Airport> A vector of airports representing the path from source to destination.
     */
    std::vector<Airport> findShortestPath(Vertex<Airport> *src, Vertex<Airport> *dest);

    /**
     * @brief Retrieves a set of airport vertices based on the specified input type and detail.
     *
     * @param input A pair representing the type (e.g., code, name, city) and the detail (e.g., actual code or city name).
     * @return std::set<Vertex<Airport>*> A set of vertices corresponding to the input criteria.
     */
    std::set<Vertex<Airport> *> getVerticesBasedOnInput(std::pair<std::string, std::string> input);


    /**
     * @brief Finds flight options from a source to a destination airport considering only specified airlines.
     *
     * @param airlines A set of airline codes to filter the flight options.
     * @param src Pointer to the source airport vertex.
     * @param dest Pointer to the destination airport vertex.
     */
    void bestFlightOptGivenAirports(std::set<std::string>& airlines, Vertex<Airport>* src, Vertex<Airport>* dest);

    /**
     * @brief Finds flight options from a source to a destination with a maximum number of airline changes allowed.
     *
     * @param maxAirlines The maximum number of airlines allowed in a flight path.
     * @param src Pointer to the source airport vertex.
     * @param dest Pointer to the destination airport vertex.
     */
    void bestFlightOptMaxAirports(int maxAirlines, Vertex<Airport>* src, Vertex<Airport>* dest);

    /**
     * @brief Retrieves a vertex from the graph based on the given airport identifier.
     *
     * @param v The identifier of the airport.
     * @param g Pointer to the graph containing the airport vertices.
     * @return Vertex<Airport>* Pointer to the corresponding airport vertex, if found; otherwise, nullptr.
     */
    Vertex<Airport>* getVertex(std::string v, const Graph<Airport>* g);

    /**
     * @brief Retrieves a vertex from the graph based on the given airport identifier.
     *
     * @param v The identifier of the airport.
     * @return Vertex<Airport>* Pointer to the corresponding airport vertex, if found; otherwise, nullptr.
     */
    Vertex<Airport>* getVertex(std::string v);

    /**
     * @brief Checks if an airline with the given code exists in the graph.
     *
     * @param code The airline code to check.
     * @return true If the airline exists.
     * @return false If the airline does not exist.
     */

    bool checkIfExists(const std::string& code);
};
#endif //AED_2_APPLICATION_H
