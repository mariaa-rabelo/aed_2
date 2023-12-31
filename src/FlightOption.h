/**
 * @file FlightOption.h
 * @brief Defines the FlightOption class for calculating flight paths between airports.
 *
 * Created by micaela_albino on 24-12-2023.
 */

#ifndef AED_2_FLIGHTOPTION_H
#define AED_2_FLIGHTOPTION_H

#include "Airport.h"
#include "Graph.h"
#include <vector>
#include <set>
#include <map>

/**
 * @class FlightOption
 * @brief Class for finding flight options between airports, with or without certain filters.
 *
 * This class contains methods to find all possible flight paths between two airports,
 * considering various constraints like airline preferences and the number of maximum airlines.
 */
class FlightOption{
public:
    /**
     * @brief Constructs a FlightOption object.
     */
    FlightOption();

    /**
     * @brief Gets all possible paths between two airports in a graph.
     *
     * @param g Pointer to the graph representing airports and flights.
     * @param source Pointer to the source airport vertex.
     * @param dest Pointer to the destination airport vertex.
     * @return Set of vectors containing all possible paths (as Vertex<Airport>*).
     */
    std::set<std::vector<Vertex<Airport>*>>getAllPaths(const Graph<Airport> *g, Vertex<Airport> *source, Vertex<Airport> *dest);

    /**
     * @brief Helper method for DFS-based path finding.
     *
     * @param g Pointer to the graph representing airports and flights.
     * @param source Pointer to the source airport vertex.
     * @param dest Pointer to the destination airport vertex.
     * @param path Reference to the current path being explored.
     * @param all_paths Reference to set of all paths found.
     * @return True if a path to the destination is found, otherwise false.
     */
    bool dfsFlightVisit(const Graph<Airport> *g, Vertex<Airport> *source, Vertex<Airport> *dest, std::vector<Vertex<Airport>*> &path, std::set<std::vector<Vertex<Airport>*>> &all_paths);

    /**
     * @brief Filters paths based on specified airlines.
     *
     * @param g Pointer to the graph.
     * @param paths Set of all possible paths.
     * @param airlines Set of preferred airline codes.
     * @return Set of paths that only use the specified airlines.
     */
    std::set<std::vector<Vertex<Airport>*>> flightsChoosenAirlines(const Graph<Airport> *g, std::set<std::vector<Vertex<Airport>*>>& paths, std::set<std::string>& airlines);

    /**
     * @brief Filters paths based on a maximum number of airlines.
     *
     * @param g Pointer to the graph.
     * @param paths Set of all possible paths.
     * @param maxAirlines Maximum number of different airlines allowed in a path.
     * @return Set of paths that meet the airline number constraint.
     */
    std::set<std::vector<Airport>> flightsMaxAirlineNumber(const Graph<Airport> *g, std::set<std::vector<Airport>>& paths, int maxAirlines);

    /**
     * @brief Filters paths based on specified airlines using BFS.
     *
     * @param g Pointer to the graph.
     * @param source Pointer to the source airport vertex.
     * @param dest Pointer to the destination airport vertex.
     * @param airlines Set of preferred airline codes.
     * @return Set of vectors containing all paths that meet the airline filter.
     */
    std::set<std::vector<Airport>> bfsFlightVisitFilter(const Graph<Airport> *g, Vertex<Airport> *source, Vertex<Airport> *dest, std::set<std::string>& airlines);

    /**
     * @brief Finds all flight paths between two airports without filters.
     *
     * @param g Pointer to the graph.
     * @param src Pointer to the source airport vertex.
     * @param dest Pointer to the destination airport vertex.
     * @return Set of vectors containing all possible flight paths.
     */
    std::set<std::vector<Airport>> flights(const Graph<Airport> *g, Vertex<Airport>* src, Vertex<Airport>* dest);

    /**
     * @brief BFS-based method to find all paths between two airports.
     *
     * @param g Pointer to the graph.
     * @param source Pointer to the source airport vertex.
     * @param dest Pointer to the destination airport vertex.
     * @return Set of vectors containing all paths found using BFS.
     */
    std::set<std::vector<Airport>> bfsFlightVisit(const Graph<Airport> *g, Vertex<Airport> *source, Vertex<Airport> *dest);

    /**
     * @brief Removes all edges associated with specified airlines from a graph.
     *
     * This function creates a new graph based on the input graph 'g' and removes
     * all edges (flights) that are associated with the airlines listed in the 'airlines' set.
     * This can be used to filter out flights from specific airlines, creating a graph
     * that only includes flights from other airlines.
     *
     * @param g Pointer to the original graph (Graph<Airport>).
     * @param airlines Set of strings containing airline codes to be removed from the graph.
     * @return Graph<Airport> A new graph with the specified airlines' edges removed.
     */
    Graph<Airport> removeEdgeGivenAirline(const Graph<Airport> *g, std::set<std::string> &airlines);
};
#endif //AED_2_FLIGHTOPTION_H