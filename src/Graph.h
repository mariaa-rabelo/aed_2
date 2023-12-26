//
// Created by user on 05-Dec-23.
//

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

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

template <class T>
class Vertex {
    T info;                // content
    std::vector<Edge<T> > adj;  // list of outgoing edges
    bool visited;          // auxiliary field
    bool processing;       // auxiliary field
    int indegree;          // auxiliary field
    int num;               // auxiliary field
    int low;               // auxiliary field

    void addEdge(Vertex<T> *dest, Airline *a);
    bool removeEdgeTo(Vertex<T> *d);
public:
    Vertex(T in);
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

    friend class Graph<T>;
};

template <class T>
class Edge {
    Vertex<T> * dest;      // destination vertex
    Airline* airline;         // edge weight
public:
    Edge(Vertex<T> *d, Airline *a);
    Vertex<T> *getDest() const;
    void setDest(Vertex<T> *dest);
    Airline* getAirline() const;
    void setAirline(Airline airline);
    friend class Graph<T>;
    friend class Vertex<T>;
};

template <class T>
class Graph {
    std::vector<Vertex<T> *> vertexSet;      // vertex set
    std::vector<Airline*> airlines;
    std::stack<Vertex<T>> _stack_;           // auxiliary field
    std::list<std::list<T>> _list_sccs_;        // auxiliary field

    void dfsVisit(Vertex<T> *v,  std::vector<T> & res) const;
    bool dfsIsDAG(Vertex<T> *v) const;
public:
    Vertex<T> *findVertex(const T &in) const;
    Vertex<T> * findVertex(const std::string &code) const;
    int getNumVertex() const;
    bool addVertex(const T &in);
    bool removeVertex(const T &in);

    Airline* findAirline(const std::string& code) const;
    bool addAirline(const Airline& airline);

    bool addEdge(const T &sourc, const T &dest, Airline* airline);
    bool removeEdge(const T &sourc, const T &dest);
    int getTotalEdges() const;

    std::vector<Vertex<T> * > getVertexSet() const;
    std::vector<T> dfs() const;
    std::vector<T> dfs(const T & source) const;
    std::vector<T> bfs(const T &source) const;
    std::vector<T> topsort() const;
    bool isDAG() const;

};

/****************** Provided constructors and functions ********************/

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
                                // operador <
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
void Edge<T>::setAirline(Airline airline) {
    Edge::airline = airline;
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
void Vertex<T>::setIndegree(int indegree) {
    Vertex::indegree = indegree;
}

template<class T>
int Vertex<T>::getNum() const {
    return num;
}

template<class T>
void Vertex<T>::setNum(int num) {
    Vertex::num = num;
}

template<class T>
int Vertex<T>::getLow() const {
    return low;
}

template<class T>
void Vertex<T>::setLow(int low) {
    Vertex::low = low;
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
void Vertex<T>::setAdj(const std::vector<Edge<T>> &adj) {
    Vertex::adj = adj;
}


/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
    if ( findVertex(in) != nullptr)
        return false;

    Vertex<T> *newVertex = new Vertex<T>(in);
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


/****************** DFS ********************/
/*
 * Performs a depth-first search (dfs) traversal in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template <class T>
std::vector<T> Graph<T>::dfs() const {
    std::vector<T> res;
    for (auto v : vertexSet)
        v->visited = false;
    for (auto v : vertexSet)
        if (! v->visited)
            dfsVisit(v, res);
    return res;
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


/****************** DFS ********************/
/*
 * Performs a depth-first search (dfs) in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order,
 * from the source node.
 */
template <class T>
std::vector<T> Graph<T>::dfs(const T & source) const {
    std::vector<T> res;
    auto s = findVertex(source);
    if (s == nullptr)
        return res;

    for (auto v : vertexSet)
        v->visited = false;

    dfsVisit(s, res);
    return res;
}


/****************** BFS ********************/
/*
 * Performs a breadth-first search (bfs) in a graph (this), starting
 * from the vertex with the given source contents (source).
 * Returns a vector with the contents of the vertices by bfs order.
 */
template <class T>
std::vector<T> Graph<T>::bfs(const T & source) const {
    std::vector<T> res;
    auto s = findVertex(source);
    if (s == NULL)
        return res;
    std::queue<Vertex<T> *> q;
    for (auto v : vertexSet)
        v->visited = false;
    q.push(s);
    s->visited = true;
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        res.push_back(v->info);
        for (auto & e : v->adj) {
            auto w = e.dest;
            if ( ! w->visited ) {
                q.push(w);

                w->visited = true;
            }
        }
    }
    return res;
}


/****************** isDAG  ********************/
/*
 * Performs a depth-first search in a graph (this), to determine if the graph
 * is acyclic (acyclic directed graph or DAG).
 * During the search, a cycle is found if an edge connects to a vertex
 * that is being processed in the stack of recursive calls (see theoretical classes).
 * Returns true if the graph is acyclic, and false otherwise.
 */

template <class T>
bool Graph<T>::isDAG() const {
    for (auto v : vertexSet) {
        v->visited = false;
        v->processing = false;
    }
    for (auto v : vertexSet)
        if (! v->visited)
            if ( ! dfsIsDAG(v) )
                return false;
    return true;
}

/**
 * Auxiliary function that visits a vertex (v) and its adjacent, recursively.
 * Returns false (not acyclic) if an edge to a vertex in the stack is found.
 */
template <class T>
bool Graph<T>::dfsIsDAG(Vertex<T> *v) const {
    v->visited = true;
    v->processing = true;
    for (auto & e : v->adj) {
        auto w = e.dest;
        if (w->processing)
            return false;
        if (! w->visited)
            if (! dfsIsDAG(w))
                return false;
    }
    v->processing = false;
    return true;
}


/****************** toposort ********************/
//=============================================================================
// Exercise 1: Topological Sorting
//=============================================================================
// TODO
/*
 * Performs a topological sorting of the vertices of a graph (this).
 * Returns a vector with the contents of the vertices by topological order.
 * If the graph has cycles, returns an empty vector.
 * Follows the algorithm described in theoretical classes.
 */

template<class T>
std::vector<T> Graph<T>::topsort() const {
    std::vector<T> res;
    std::queue<Vertex<T>*> q;

    if (!isDAG()) return res;

    // calculate incoming degree
    for (auto v: vertexSet){
        v->indegree=0;
    }

    for (auto v: vertexSet){
        for (const Edge<T> &edge: v->getAdj()){
            edge.dest->indegree++;
        }
    }

    //queue of 0-indegree vertices
    for (auto v: vertexSet){
        if (v->indegree==0){
            q.push(v);
            //std::cout << v->getInfo() << std::endl;
        }
    }

    //process vertices
    while (!q.empty()){
        auto front= q.front();
        q.pop();
        for (const Edge<T> &edge: front->getAdj()){
            edge.dest->indegree--; //update indegree
            if (edge.dest->indegree==0)
                q.push(edge.dest); //update queue
        }
        res.push_back(front->getInfo());
    }

    return res;
}


#endif //AED_2_GRAPH_H
