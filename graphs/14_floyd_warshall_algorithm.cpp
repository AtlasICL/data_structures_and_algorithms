/**
 * Implementation of the Floyd-Warshall algorithm for
 * finding the shortest path between all pairs of nodes
 * in a weighted directed graph.
 * 
 * This implementation is built for a Graph class which uses
 * an adjacency list. 
 * 
 * -- INCOMPLETE --
 */

#include <vector>
#include <iostream>
#include <string>
#include <stdexcept>

class DirectedGraph {
private:
    int V;
    std::vector<std::vector<int>> adj;

public:
    DirectedGraph() : V(0), adj(V) {}

    DirectedGraph(int numVertices) : V(numVertices), adj(numVertices) {}

    void addEdge(int u, int v) {

    }
};

