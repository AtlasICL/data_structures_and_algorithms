/**
 * Implementation of the Floyd-Warshall algorithm for
 * finding the shortest path between all pairs of nodes
 * in a weighted graph.
 */

#include <vector>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <limits>

constexpr int INF = std::numeric_limits<int>::max() / 2;

// struct to represent an edge in the graph
struct Edge {
    const int u;
    const int v;
    const int weight;
};

// Graph class for a weighted undirected graph, using an edge list
class Graph {
private:
    int V; // vertex count
    std::vector<Edge> edges; // edges

    inline bool isValidVertex(int u) const {
        return u >= 0 && u < V;
    }

    inline bool isValidVertex(int u, int v) const {
        return isValidVertex(u) && isValidVertex(v);
    }

public:
    Graph(int V) : V(V) {}

    int getVertexCount() const {
        return V;
    }

    std::vector<Edge> getEdges() const {
        return edges;
    }

    // adds an edge to the graph, with given edge weight
    // @throws invalid_argument if u or v are not valid nodes
    void addEdge(int u, int v, int weight) {
        if (u < 0 || u >= V || v < 0 || v >= V) {
            throw std::invalid_argument("Invalid vertex index");
        }
        edges.push_back({u, v, weight});
    }

    // Returns true if the nodes u and v are directly connected via an edge,
    // or if u and v are the same node.
    // Returns false otherwise.
    bool edgeConnects(int u, int v) {
        if (!isValidVertex(u, v)) {
            throw std::invalid_argument("Invalid vertex index");
        }
        if (u == v) {
            return true;
        }
        for (const Edge& edge : edges) {
            if (edge.u == u && edge.v == v || edge.u == v && edge.v == u) {
                return true;
            }
        }
        return false;
    }

    // Returns the weight of the edge connecting nodes u and v,
    // and INF if the two nodes are not directly linked by one edge.
    // If u and v are the same node, the weight returned is 0.
    int edgeWeight(int u, int v) {
        if (u == v) {
            return 0;
        }
        if (edgeConnects(u, v)) {
            for (const Edge& edge : edges) {
                if (edge.u == u && edge.v == v || edge.u == v && edge.v == u) {
                    return edge.weight;
                }
            }
        }
        else {
            return INF;
        }
    }

};

