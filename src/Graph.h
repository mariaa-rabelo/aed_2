/**
 * @file Graph.h
 * @brief This file contains the template definitions for Graph, Vertex, and Edge classes.
 *
 * These classes are used to create and manage a graph data structure.
 * Created by user on 05-Dec-23.
 */

#ifndef AED_2_GRAPH_H
#define AED_2_GRAPH_H

#include <unordered_map>
#include <string>
#include <vector>
#include <stack>
#include <list>
#include <queue>
#include <set>
#include <map>
#include <limits>
#include <algorithm>
#include <iostream>
#include "Airline.h"

template <class T> class Vertex;
template <class T> class Graph;
template <class T> class Edge;

/**
 * @class Vertex
 * @brief Represents a vertex in a graph.
 * This class contains the information stored in a vertex, along with a list of outgoing edges
 * (adjacency list). It also contains auxiliary fields for various graph algorithms.
 *
 * @tparam T The type of the content in the vertex.
 */
template <class T>
class Vertex {
    T info;                            ///< Content of the vertex.
    std::vector<Edge<T>> adj;          ///< List of outgoing edges (adjacency list).
    bool visited;                    ///< Auxiliary field to mark if the vertex has been visited.
    int num;                         ///< Auxiliary field used in various algorithms.
    int low;                         ///< Auxiliary field used in algorithms like Tarjan's.

    /**
     * @brief Adds an edge to this vertex.
     *
     * This method creates a new edge from this vertex to the specified destination vertex.
     * The edge is also associated with a specific airline.
     *
     * @param dest The destination vertex of the edge.
     * @param a The airline associated with the edge.
     */
    void addEdge(Vertex<T> *dest, Airline *a);

    /**
     * @brief Removes an edge from this vertex.
     *
     * This method removes an outgoing edge from this vertex to the specified destination vertex.
     * Returns true if the edge was successfully removed, false otherwise.
     *
     * @param d The destination vertex of the edge to remove.
     * @return True if the edge was removed, false otherwise.
     */
    bool removeEdgeTo(Vertex<T> *d);

public:
    /**
     * @brief Constructs a Vertex object with the provided content.
     *
     * @param in The content to be stored in the vertex.
     */
    explicit Vertex(T in);

    /**
     * @brief Retrieves the content of this vertex.
     *
     * @return The content of the vertex.
     */
    T getInfo() const;

    /**
     * @brief Sets the content of this vertex.
     *
     * @param in The new content to set for this vertex.
     */
    void setInfo(T in);

    /**
     * @brief Checks if this vertex has been visited.
     *
     * @return True if the vertex has been visited, false otherwise.
     */
    bool isVisited() const;

    /**
     * @brief Sets the visited status of this vertex.
     *
     * @param v The visited status to set.
     */
    void setVisited(bool v);

    /**
     * @brief Gets the adjacency list of this vertex.
     *
     * @return A constant reference to the vector of outgoing edges from this vertex.
     */
    const std::vector<Edge<T>> &getAdj() const;

    /**
     * @brief Sets the adjacency list of this vertex.
     *
     * @param adj The new adjacency list to set.
     */
    void setAdj(const std::vector<Edge<T>> &adj);

    /**
     * @brief Increases the indegree of this vertex by one.
     */
    void increaseIndegree();

    /**
     * @brief Decreases the indegree of this vertex by one.
     */
    void decreaseIndegree();

    /**
     * @brief Retrieves the indegree of this vertex.
     *
     * @return The indegree of the vertex.
     */
    int getIndegree() const;

    /**
     * @brief Sets the indegree of this vertex.
     *
     * @param indegree The indegree value to set.
     */
    void setIndegree(int indegree);

    /**
     * @brief Retrieves the 'num' value of this vertex.
     *
     * @return The 'num' value of the vertex.
     */
    int getNum() const;

    /**
     * @brief Sets the 'num' value of this vertex.
     *
     * @param num The 'num' value to set.
     */
    void setNum(int num);

    /**
     * @brief Retrieves the 'low' value of this vertex.
     *
     * @return The 'low' value of the vertex.
     */
    int getLow() const;

    /**
     * @brief Sets the 'low' value of this vertex.
     *
     * @param low The 'low' value to set.
     */
    void setLow(int low);

    /**
     * @brief Compares this vertex with another vertex based on their contents.
     *
     * @param other The vertex to compare with.
     * @return True if this vertex is less than the other vertex, false otherwise.
     */
    bool operator<(const Vertex<T>& other) const;

    friend class Graph<T>; ///< Allows Graph<T> to access private members of Vertex<T>.
};

/**
 * @class Edge
 * @brief Template class representing an edge in a graph.
 *
 * This class models an edge in a graph, holding a pointer to the destination vertex
 * and an associated airline object. It is used within the Graph class to represent
 * connections between vertices.
 *
 * @tparam T The type of content in the vertices that the edge connects.
 */
template <class T>
class Edge {

    Vertex<T> * dest;     ///< Destination vertex.
    Airline* airline;     ///< Airline associated to the edge.
public:
    /**
     * @brief Constructor to create an edge with a destination vertex and associated airline.
     * @param d Pointer to the destination vertex.
     * @param a Pointer to the Airline object associated with the edge.
     */
    Edge(Vertex<T> *d, Airline *a);

    //TOdo DOXYGEN
    Edge(const Edge<T>& other);

    /**
     * @brief Retrieves the destination vertex of this edge.
     *
     * @return Pointer to the destination vertex.
     */
    Vertex<T> *getDest() const;

    /**
     * @brief Sets the destination vertex of this edge.
     *
     * @param dest Pointer to the new destination vertex.
     */
    void setDest(Vertex<T> *dest);

    /**
     * @brief Retrieves the airline associated with this edge.
     *
     * @return Pointer to the airline associated with the edge.
     */
    Airline* getAirline() const;

    /**
     * @brief Sets the airline associated with this edge.
     *
     * @param airline The Airline object to associate with the edge.
     */
    void setAirline(const Airline& airline);

    friend class Graph<T>; ///< Allows Graph<T> to access private members of Edge<T>.
    friend class Vertex<T>; ///< Allows Vertex<T> to access private members of Edge<T>.
};

/**
 * @class Graph
 * @brief Template class representing a graph.
 *
 * This class models a graph data structure, using a list of vertices and airlines.
 * It provides functionalities for adding and removing vertices and edges, finding vertices and airlines,
 * and querying various properties of the graph.
 *
 * @tparam T The type of content in the vertices of the graph.
 */
template <class T>
class Graph {
    std::vector<Vertex<T> *> vertexSet;     ///< A vector that stores pointers to all the vertices in the graph.
    std::vector<Airline*> airlines;         ///< A vector that stores pointers to all the airlines associated with the graph.

public:

    /**
    * @brief Finds a vertex in the graph with the given content.
    * @param in The content to search for.
    * @return Pointer to the vertex if found, nullptr otherwise.
    */
    Vertex<T> *findVertex(const T &in) const;

    /**
     * @brief Finds a vertex in the graph based on a given code (assuming the vertex content has a 'getCode' method).
     * @param code The code to search for.
     * @return Pointer to the vertex if found, nullptr otherwise.
     */
    Vertex<T> * findVertex(const std::string &code) const;

    /**
     * @brief Gets the number of vertices in the graph.
     * @return The number of vertices.
     */
    int getNumVertex() const;

    /**
     * @brief Adds a vertex to the graph.
     * @param in Content of the vertex to be added.
     * @return True if the vertex was successfully added, false if it already exists.
     */
    bool addVertex(const T &in);
    /**
     * @brief Removes the vertex with the specified content from the graph.
     * @param in Content of the vertex to be removed.
     * @return True if the vertex is removed successfully, false if it does not exist.
     */
    bool removeVertex(const T &in);

    /**
     * @brief Finds an airline by its code.
     * @param code The airline's code.
     * @return Pointer to the airline if found, nullptr otherwise.
     */
    Airline* findAirline(const std::string& code) const;

    /**
     * @brief Adds an airline to the graph.
     * @param airline The airline to be added.
     * @return True if the airline is added successfully, false if an airline with the same code already exists.
     */
    bool addAirline(const Airline& airline);

    /**
     * @brief Adds an edge between two vertices in the graph.
     * @param sourc Content of the source vertex.
     * @param dest Content of the destination vertex.
     * @param airline Airline associated with the edge.
     * @return True if the edge is added successfully, false if either vertex does not exist.
     */
    bool addEdge(const T &sourc, const T &dest, Airline* airline);

    /**
     * @brief Removes an edge between two vertices in the graph.
     * @param sourc Content of the source vertex.
     * @param dest Content of the destination vertex.
     * @return True if the edge is removed successfully, false if either vertex does not exist or the edge does not exist.
     */
    bool removeEdge(const T &sourc, const T &dest);

    /**
     * @brief Gets the total number of edges in the graph.
     * @return Total number of edges.
     */
    int getTotalEdges() const;

    /**
     * @brief Gets the list of vertices in the graph.
     * @return Vector of pointers to vertices.
     */
    std::vector<Vertex<T> * > getVertexSet() const;

    /**
     * @brief Gets the list of airlines in the graph.
     * @return Vector of pointers to airlines.
     */
    std::vector<Airline*> getAirlines() const;

    /**
     * @brief Finds the shortest path (least number of stops) between two airports.
     *
     * @param src Pointer to the source airport vertex.
     * @param dest Pointer to the destination airport vertex.
     * @return std::vector<Airport> A vector of airports representing the path from source to destination.
     */
    std::vector<Edge<Airport>> findShortestPath(Vertex<Airport>* src, Vertex<Airport>* dest);

    //TODO doxygen for it
    void findAndDisplayBestPaths(const std::set<Vertex<Airport>*>& srcVertices, const std::set<Vertex<Airport>*>& destVertices);
};

/****************** Constructors and functions ********************/

template <class T>
Vertex<T>::Vertex(T in): info(in) {}

template <class T>
Edge<T>::Edge(Vertex<T> *d, Airline* a): dest(d), airline(a) {}

template <class T>
Edge<T>::Edge(const Edge<T>& other) : dest(other.dest), airline(other.airline) {}

template <class T>
int Graph<T>::getNumVertex() const {
    return vertexSet.size();
}

template <class T>
std::vector<Vertex<T> * > Graph<T>::getVertexSet() const {
    return vertexSet;
}
template <class T>
std::vector<Airline*> Graph<T>::getAirlines() const{
    return airlines;
}

template<class T>
T Vertex<T>::getInfo() const {
    return info;
}

template<class T>
void Vertex<T>::setInfo(T in) {
    Vertex::info = in;
}

template<class T>
bool Vertex<T>::operator<(const Vertex<T>& other) const{
    return this->getInfo() < other.getInfo();
}
template<class T>
Vertex<T> *Edge<T>::getDest() const {
    return dest;
}

template<class T>
void Edge<T>::setDest(Vertex<T> *d) {
    Edge::dest = d;
}

template<class T>
Airline* Edge<T>::getAirline() const {
    return airline;
}

template<class T>
void Edge<T>::setAirline(const Airline& newAirline) {
    Edge::airline = newAirline;
}


/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
    for (auto v : vertexSet)
        if (v->info == in)
            return v;
    return nullptr;
}

template <class T>
Vertex<T> * Graph<T>::findVertex(const std::string &code) const {
    for (auto v : vertexSet) {
        if (v->info.getCode() == code)
            return v;
    }
    return nullptr;
}

template <class T>
bool Vertex<T>::isVisited() const {
    return visited;
}

template<class T>
int Vertex<T>::getNum() const {
    return num;
}

template<class T>
void Vertex<T>::setNum(int n) {
    Vertex::num = n;
}

template<class T>
int Vertex<T>::getLow() const {
    return low;
}

template<class T>
void Vertex<T>::setLow(int l) {
    Vertex::low = l;
}

template <class T>
void Vertex<T>::setVisited(bool v) {
    Vertex::visited = v;
}

template<class T>
const std::vector<Edge<T>> &Vertex<T>::getAdj() const {
    return adj;
}

template <class T>
void Vertex<T>::setAdj(const std::vector<Edge<T>> &newAdj) {
    Vertex::adj = newAdj;
}


/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
    if ( findVertex(in) != nullptr)
        return false;

    auto *newVertex = new Vertex<T>(in);
    vertexSet.push_back(newVertex);
    return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, Airline* airline) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2,airline);
    return true;
}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, Airline *a) {
    adj.push_back(Edge<T>(d, a));
}


/*
 * Removes an edge from a graph (this).
 * The edge is identified by the source (sourc) and destination (dest) contents.
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    return v1->removeEdgeTo(v2);
}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
    for (auto it = adj.begin(); it != adj.end(); it++)
        if (it->dest  == d) {
            d->decreaseIndegree();
            adj.erase(it);
            return true;
        }
    return false;
}

template <class T>
int Graph<T>::getTotalEdges() const {
    int totalEdges = 0;
    for (auto v : vertexSet) {
        totalEdges += v->getAdj().size();
    }
    return totalEdges;
}

template <class T>
Airline* Graph<T>::findAirline(const std::string& code) const {
    for (Airline* airline : airlines) {
        if (airline->getCode() == code) {
            return airline;
        }
    }
    return nullptr;  // Airline not found
}

template <class T>
bool Graph<T>::addAirline(const Airline& airline) {
    if (findAirline(airline.getCode()) == nullptr) {
        airlines.push_back(new Airline(airline));
        return true;
    }
    return false;  // Airline with the same code already exists
}


/*
 *  Removes a vertex with a given content (in) from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such vertex does not exist.
 */
template <class T>
bool Graph<T>::removeVertex(const T &in) {
    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++)
        if ((*it)->info  == in) {
            auto v = *it;
            vertexSet.erase(it);
            for (auto u : vertexSet)
                u->removeEdgeTo(v);
            delete v;
            return true;
        }
    return false;
}

template <class T>
std::vector<Edge<Airport>> Graph<T>::findShortestPath(Vertex<Airport>* src, Vertex<Airport>* dest) {
    //para cada vertice, seu predecessor no caminho mais curto
    std::map<Vertex<Airport>*, Vertex<Airport>*> predecessors;

    //std::map<Vertex<Airport>*, Edge<Airport>> edgeTo;
    // entre src ate cada outro airport
    std::map<Vertex<Airport>*, int> distances;
    std::queue<Vertex<Airport>*> queue;

    for (auto& vertex : vertexSet) {
        distances[vertex] = std::numeric_limits<int>::max();
        vertex->setVisited(false);
    }

    distances[src] = 0;
    queue.push(src);
    src->setVisited(true);

    while (!queue.empty()) {
        Vertex<Airport>* current = queue.front();
        queue.pop();

        for (const Edge<Airport>& edge : current->getAdj()) {
            Vertex<Airport>* neighbor = edge.getDest();
            if (!neighbor->isVisited()) {
                neighbor->setVisited(true);
                queue.push(neighbor);
                distances[neighbor] = distances[current] + 1;
                predecessors[neighbor] = current;
      //          edgeTo[neighbor] =edge;
            }
        }
    }

    std::vector<Edge<Airport>> path;
    if (distances[dest] != std::numeric_limits<int>::max()) {
        for (Vertex<Airport>* at = dest; at != src; at = predecessors[at]) {
        //    path.push_back(edgeTo[at]);
            for (const Edge<Airport>& edge : at->getAdj()) {
                if (edge.getDest() == predecessors[at]) {
                    path.push_back(edge);
                    break;
                }
            }
        }
        std::reverse(path.begin(), path.end());
    }
    return path;
}

template <class T>
void Graph<T>::findAndDisplayBestPaths(const std::set<Vertex<Airport>*>& srcVertices, const std::set<Vertex<Airport>*>& destVertices) {
    std::vector<std::vector<Edge<Airport>>> bestPaths;
    int minStops = std::numeric_limits<int>::max();

    for (auto srcVertex : srcVertices) {
        for (auto destVertex : destVertices) {
            std::vector<Edge<Airport>> path = findShortestPath(srcVertex, destVertex);
            int stops = path.size() - 1;

            if (stops < minStops) {
                minStops = stops;
                bestPaths.clear();
                bestPaths.push_back(path);
            } else if (stops == minStops) {
                bestPaths.push_back(path);
            }
        }
    }

    for (const auto& path : bestPaths) {
        std::cout << "Path with " << minStops << " stops: " << std::endl;
        for (const auto& edge : path) {
            std::cout << "flying to: " << edge.getDest()->getInfo().getCode()
                      << " with airline " << edge.getAirline()->getCode()
                      << " " << edge.getAirline()->getCallsign()
                      << std::endl;
        }
        std::cout << std::endl;
    }
}




#endif //AED_2_GRAPH_H
