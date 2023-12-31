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
    bool visited{};                    ///< Auxiliary field to mark if the vertex has been visited.
    bool processing{};                 ///< Auxiliary field to mark if the vertex is being processed.
    int indegree{};                    ///< Auxiliary field to store the in-degree of the vertex.
    int num{};                         ///< Auxiliary field used in various algorithms.
    int low{};                         ///< Auxiliary field used in algorithms like Tarjan's.

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
     * @brief Constructor to create a vertex with given content.
     * @param in Content of the vertex.
     */
    explicit Vertex(T in);
    T getInfo() const;
    void setInfo(T in);
    bool isVisited() const;
    void setVisited(bool v);
    bool isProcessing() const;
    void setProcessing(bool p);
    const std::vector<Edge<T>> &getAdj() const;
    void setAdj(const std::vector<Edge<T>> &adj);

    void increaseIndegree();
    void decreaseIndegree();

    int getIndegree() const;
    void setIndegree(int indegree);

    int getNum() const;
    void setNum(int num);

    int getLow() const;
    void setLow(int low);
    bool operator<(const Vertex<T>& other) const;

    friend class Graph<T>; ///< Allows Graph<T> to access private members of Vertex<T>.
};

/**
 * @class Edge
 * @brief Template class representing an edge in a graph.
 *
 * @tparam T The type of content in the vertices that the edge connects.
 */
template <class T>
class Edge {

    Vertex<T> * dest;      // destination vertex
    Airline* airline;         // edge weight
public:
    /**
     * @brief Constructor to create an edge with a destination vertex and associated airline.
     * @param d Destination vertex.
     * @param a Airline associated with the edge.
     */
    Edge(Vertex<T> *d, Airline *a);
    Vertex<T> *getDest() const;
    void setDest(Vertex<T> *dest);
    Airline* getAirline() const;
    void setAirline(const Airline& airline);
    friend class Graph<T>;
    friend class Vertex<T>;
};

/**
 * @class Graph
 * @brief Template class representing a graph.
 *
 * @tparam T The type of content in the vertices of the graph.
 */
template <class T>
class Graph {
    std::vector<Vertex<T> *> vertexSet;      // vertex set
    std::vector<Airline*> airlines;
    std::stack<Vertex<T>> _stack_;           // auxiliary field
    std::list<std::list<T>> _list_sccs_;        // auxiliary field

    void dfsVisit(Vertex<T> *v,  std::vector<T> & res) const;
public:

    Vertex<T> *findVertex(const T &in) const;
    Vertex<T> * findVertex(const std::string &code) const;
    int getNumVertex() const;

    /**
     * @brief Adds a vertex to the graph.
     * @param in Content of the vertex to be added.
     * @return True if the vertex was successfully added, false if it already exists.
     */
    bool addVertex(const T &in);
    bool removeVertex(const T &in);

    Airline* findAirline(const std::string& code) const;
    bool addAirline(const Airline& airline);

    /**
     * @brief Adds an edge to the graph.
     * @param sourc Content of the source vertex.
     * @param dest Content of the destination vertex.
     * @param airline Airline associated with the edge.
     * @return True if the edge was successfully added, false if either vertex does not exist.
     */
    bool addEdge(const T &sourc, const T &dest, Airline* airline);
    bool removeEdge(const T &sourc, const T &dest);
    int getTotalEdges() const;

    std::vector<Vertex<T> * > getVertexSet() const;
    std::vector<Airline*> getAirlines() const;
};

/****************** Constructors and functions ********************/

template <class T>
Vertex<T>::Vertex(T in): info(in) {}

template <class T>
Edge<T>::Edge(Vertex<T> *d, Airline* a): dest(d), airline(a) {}


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
bool Vertex<T>::isProcessing() const {
    return processing;
}

template<class T>
void Vertex<T>::setProcessing(bool p) {
    Vertex::processing = p;
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
void Vertex<T>::increaseIndegree(){
    indegree++;
}
template<class T>
void Vertex<T>::decreaseIndegree(){
    indegree--;
}

template<class T>
int Vertex<T>::getIndegree() const {
    return indegree;
}

template<class T>
void Vertex<T>::setIndegree(int ind) {
    Vertex::indegree = ind;
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
    d->increaseIndegree();
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

/*
 * Auxiliary function that visits a vertex (v) and its adjacent, recursively.
 * Updates a parameter with the list of visited node contents.
 */
template <class T>
void Graph<T>::dfsVisit(Vertex<T> *v, std::vector<T> & res) const {
    v->visited = true;
    res.push_back(v->info);
    for (auto & e : v->adj) {
        auto w = e.dest;
        if ( ! w->visited)
            dfsVisit(w, res);
    }
}


#endif //AED_2_GRAPH_H
