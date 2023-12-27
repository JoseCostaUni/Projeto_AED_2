//
// Created by jose-costa on 12/23/23.
//

#ifndef PROJETO_2_GRAPH_H
#define PROJETO_2_GRAPH_H


#include <cstddef>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <limits>
#include "Airline.h"

using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;


/****************** Provided structures  ********************/

template <class T>
class Vertex {
    T info;                // contents
    vector<Edge<T> > adj;  // list of outgoing edges
    bool visited;          // auxiliary field
    bool processing;       // auxiliary field
    int low;               // auxiliary field
    int indegree;          // auxiliary field
    int num;               // auxiliary field
    Vertex<T>* parent;

    void addEdge(Vertex<T> *dest, double w, string airline);
    bool removeEdgeTo(Vertex<T> *d);
public:
    Vertex(T in);
    T getInfo() const;
    void setInfo(T in);
    bool isVisited() const;
    void setVisited(bool v);
    bool isProcessing() const;
    void setProcessing(bool p);
    const vector<Edge<T>> &getAdj() const;
    void setAdj(const vector<Edge<T>> &adj);
    void setParent(Vertex<T>* parent);

    int getIndegree() const;

    void setIndegree(int indegree);

    int getNum() const;

    void setNum(int num);

    int getLow() const;

    void setLow(int low);

    friend class Graph<T>;

    Vertex<T>* getParent();
};

template<class T>
Vertex<T>* Vertex<T>::getParent() {
    return parent;
}

template<class T>
void Vertex<T>::setParent(Vertex<T>* parent) {
    this->parent = parent;
}


template <class T>
class Edge {
    Vertex<T> * dest;      // destination vertex
    double weight;         // edge weight
    string airline;        // airline code
public:
    Edge(Vertex<T> *d, double w,string airline);
    Vertex<T> *getDest() const;
    void setDest(Vertex<T> *dest);
    double getweight() const;
    void setweight(double weight);
    std::string getAirline()const ;
    void setAirline(string airline);
    friend class Graph<T>;
    friend class Vertex<T>;
};


template <class T>
class Graph {
    vector<Vertex<T> *> vertexSet;  // vertex set
    stack<Vertex<T>> stack_;        // auxiliary field
    list<list<T>> list_sccs;        // auxiliary field

    void dfsVisit(Vertex<T> *v,  vector<T> & res) const;
    bool dfsIsDAG(Vertex<T> *v) const;
public:
    Vertex<T> *findVertex(const T &in) const;
    int getNumVertex() const;
    int calculateDiameter() const;
    bool addVertex(const T &in);
    bool removeVertex(const T &in);
    bool addEdge(const T &sourc, const T &dest, double w,string airline);
    bool removeEdge(const T &sourc, const T &dest);
    vector<Vertex<T> * > getVertexSet() const;
    vector<T> dfs() const;
    void countDestinationsBFS(Vertex<T>* vertex, int maxStops,unordered_set<string>& visitedAirports);
    vector<T> shortestPath(T initial , T destination);
    vector<T> dfs(const T & source) const;
    vector<T> bfs(const T &source) const;
    void bfsDifferent(T &source) const;
    vector<T> topsort() const;
    bool isDAG() const;
    void calculateIndegrees() const;
};

//O(V² + V*E)
template<class T>
int Graph<T>::calculateDiameter() const {
    int max_diameter = 0;
    for(auto a : getVertexSet())
    {
        a->setVisited(false);
        a->setParent(nullptr);
        a->setNum(0);
    }
    for (auto a : getVertexSet()){
        T airport = a->getInfo();
        this->bfsDifferent(airport);
        for (Vertex<T>* b : getVertexSet()){
            if (b->getNum() > max_diameter)
            {
                max_diameter = b->getNum();
            }
        }
    }

    return max_diameter;
}

/****************** Provided constructors and functions ********************/

template <class T>
Vertex<T>::Vertex(T in): info(in) {}

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w,string airline): dest(d), weight(w),airline(airline) {}

template <class T>
int Graph<T>::getNumVertex() const {
    return vertexSet.size();
}

template <class T>
vector<Vertex<T> * > Graph<T>::getVertexSet() const {
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

template<class T>
Vertex<T> *Edge<T>::getDest() const {
    return dest;
}

template<class T>
void Edge<T>::setDest(Vertex<T> *d) {
    Edge::dest = d;
}

template<class T>
double Edge<T>::getweight() const {
    return weight;
}

template<class T>
void Edge<T>::setweight(double weight) {
    Edge::weight = weight;
}
template<class T>
void Edge<T>::setAirline(std::string airline) {
    Edge::airline = airline;
}
template<class T>
std::string Edge<T>::getAirline() const{
    return airline;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
    for (auto v : vertexSet)
        if (v->info == in)
            return v;
    return NULL;
}

template <class T>
bool Vertex<T>::isVisited() const {
    return visited;
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
const vector<Edge<T>> &Vertex<T>::getAdj() const {
    return adj;
}

template <class T>
void Vertex<T>::setAdj(const vector<Edge<T>> &adj) {
    Vertex::adj = adj;
}


/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
    if (findVertex(in) != NULL)
        return false;
    vertexSet.push_back(new Vertex<T>(in));
    return true;
}


/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w,string airline) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    v1->addEdge(v2,w,airline);
    return true;
}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w,string airline) {
    adj.push_back(Edge<T>(d, w,airline));
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
    if (v1 == NULL || v2 == NULL)
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
            adj.erase(it);
            return true;
        }
    return false;
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
vector<T> Graph<T>::dfs() const {
    vector<T> res;
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
void Graph<T>::dfsVisit(Vertex<T> *v, vector<T> & res) const {
    v->visited = true;
    res.push_back(v->info);
    for (auto & e : v->adj) {
        auto w = e.dest;
        if ( ! w->visited)
            dfsVisit(w, res);
    }
}


/****************** BFS ********************/
/*
 * Performs a breadth-first search (bfs) in a graph (this), starting
 * from the vertex with the given source contents (source).
 * Returns a vector with the contents of the vertices by bfs order.
 */
template <class T>
vector<T> Graph<T>::bfs(const T & source) const {
    vector<T> res;
    auto s = findVertex(source);
    if (s == NULL)
        return res;
    queue<Vertex<T> *> q;
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
}

template<class T>
void Graph<T>::bfsDifferent(T &source) const {
    auto s = findVertex(source);
    if (s == NULL)
        return ;
    queue<Vertex<T> *> q;
    for (auto v : vertexSet)
        v->setVisited(false);
    q.push(s);
    s->setVisited(true);
    s->setNum(0);
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        for (const Edge<T> & e : v->getAdj()) {
            Vertex<T>* w = e.getDest();
            if (!w->isVisited()) {
                q.push(w);
                w->setVisited(true);
                w->setNum(v->getNum() + 1);
            }
        }
    }
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

/*
 * Performs a topological sorting of the vertices of a graph (this).
 * Returns a vector with the contents of the vertices by topological order.
 * If the graph has cycles, returns an empty vector.
 * Follows the algorithm described in theoretical classes.
 */

template<class T>
void topsortAux(Vertex<T>* vertex, stack<Vertex<T>*> & s) {
    vertex->setVisited(true);
    for (Edge<T> edge : vertex->getAdj()) {
        auto neighbor = edge.getDest();
        if (!neighbor->isVisited()) {
            topsortAux(neighbor, s);
        }
    }
    s.push(vertex);
}

template<class T>
vector<T> Graph<T>::topsort() const {
    vector<T> res;
    stack<Vertex<T>*> s;
    for (Vertex<T> * vertex : this->vertexSet) {
        vertex->setVisited(false);
    }
    for (Vertex<T>* vertex : this->vertexSet) {
        if (!vertex->isVisited())
            topsortAux(vertex, s);
    }

    while (!s.empty()) {
        res.push_back(s.top()->getInfo());
        s.pop();
    }
    return res;
}

template<class T>
vector<T> Graph<T>::shortestPath(T initial, T destination) {
    vector<T> res;
    Vertex<T>* initialVertex = findVertex(initial);
    Vertex<T>* finalVertex = findVertex(destination);

    if (initialVertex == nullptr || finalVertex == nullptr)
        return res;  // Return an empty vector indicating failure

    // Resetting visited and parent information
    for (auto v : vertexSet) {
        v->setVisited(false);
        v->setParent(nullptr);
    }

    queue<Vertex<T> *> q;
    q.push(initialVertex);
    initialVertex->setVisited(true);

    while (!q.empty()) {
        auto v = q.front();
        q.pop();

        if (v == finalVertex) {
            // Reconstruct the path
            while (v->getParent() != nullptr) {
                res.push_back(v->getInfo());
                v = v->getParent();
            }
            res.push_back(initial);  // Add the initial vertex to the path
            reverse(res.begin(), res.end());  // Reverse the path to get correct order
            return res;
        }

        for (const Edge<T> &e : v->getAdj()) {
            Vertex<T>* w = e.getDest();
            if (!w->isVisited()) {
                w->setParent(v);
                q.push(w);
                w->setVisited(true);
            }
        }
    }

    return res;  // Return an empty vector indicating that no path was found
}

template <class T>
void Graph<T>::calculateIndegrees() const {
    for (auto v : vertexSet) {
        v->setIndegree(0);
    }

    for (auto v : vertexSet) {
        for (auto &e : v->getAdj()) {
            auto w = e.getDest();
            w->setIndegree(w->getIndegree() + 1);
        }
    }
}

#endif //PROJETO_2_GRAPH_H
