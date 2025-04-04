/**
 * Implementation of Prim's algorithm for finding
 * the MST of a weighted undirected graph.
 * -- INCOMPLETE --
 */

#include <vector>
#include <iostream>
#include <stdexcept>
#include <algorithm>

// struct to represent an edge in the graph
struct Edge {
    int u;
    int v;
    int weight;
};

// Graph class for a weighted undirected graph, using an edge list
class Graph {
private:
    int V; // vertex count
    std::vector<Edge> edges; // edges

public:
    Graph(int V) : V(V) {}

    // adds an edge to the graph, with given edge weight
    // @throws invalid_argument if u or v are not valid nodes
    void addEdge(int u, int v, int weight) {
        if (u < 0 || u >= V || v < 0 || v >= V) {
            throw std::invalid_argument("Invalid vertex index");
        }
        edges.push_back({u, v, weight});
    }

    // finds the MST of the graph using Prim's algorithm

    // TODO: actually do the work

    // apparently Prim's works best with an adjacency list
};