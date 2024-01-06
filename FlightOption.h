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
#include <stack>

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
     * @brief Filters paths based on a maximum number of airlines.
     *
     * @param g Pointer to the graph.
     * @param paths Set of all possible paths.
     * @param maxAirlines Maximum number of different airlines allowed in a path.
     * @return Set of paths that meet the airline number constraint.
     * @time_complexity O(P) - Where P is the number of paths in 'paths'. Each path is processed individually.
     */
    std::set<std::vector<std::pair<Airport,std::string>>> flightsMaxAirlineNumber(const Graph<Airport> *g, std::set<std::vector<Airport>>& paths, int maxAirlines);

    /**
     * @brief Finds all flight paths between two airports without filters.
     *
     * @param g Pointer to the graph.
     * @param src Pointer to the source airport vertex.
     * @param dest Pointer to the destination airport vertex.
     * @return Set of vectors containing all possible flight paths.
     * @time_complexity O(V + E) - BFS traversal.
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
     * @brief Filters paths based on specified airlines using BFS.
     *
     * @param g Pointer to the graph.
     * @param source Pointer to the source airport vertex.
     * @param dest Pointer to the destination airport vertex.
     * @param airlines Set of preferred airline codes.
     * @return Vector of stacks containing all paths that meet the airline filter.
     */
    std::vector<std::stack<std::pair<Airport, std::string>>> bfsFlightVisitFilter(const Graph<Airport> *g, Vertex<Airport> *source,Vertex<Airport> *dest );


    /**
     * @brief Keeps all edges associated with specified airlines from a graph.
     *
     * This function creates a new graph based on the input graph 'g' and adds
     * all edges (flights) that are associated with the airlines listed in the 'airlines' set
     * and all vertexes that can be reached with said edges.
     * This can be used to filter out flights from unwanted airlines, creating a graph
     * that only includes flights from the selected airlines.
     *
     * @param g Pointer to the original graph (Graph<Airport>).
     * @param airlines Set of strings containing airline codes to be kept.
     * @return Graph<Airport> A new graph with the specified airlines' edges.
     * @time_complexity O(V * E) - Iterates over all vertices (V) and their edges (E).
     */
    Graph<Airport> removeEdgeGivenAirline(const Graph<Airport> *g, std::set<std::string>& airlines );

    bool helperDFS( const Graph<Airport> *g, Vertex<Airport> *src,  Vertex<Airport> *dest);
};
#endif //AED_2_FLIGHTOPTION_H