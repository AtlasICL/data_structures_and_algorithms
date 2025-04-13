/**
 * Implementation of the Floyd-Warshall algorithm for
 * finding the shortest path between all pairs of nodes
 * in a weighted graph.
 */

#include <vector>
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

    bool isValidVertex(int u) const {
        return u >= 0 && u < V;
    }

    bool isValidVertex(int u, int v) const {
        return isValidVertex(u) && isValidVertex(v);
    }

    // Returns true if the nodes u and v are directly connected via an edge,
    // or if u and v are the same node.
    // Returns false otherwise.
    bool edgeConnects(int u, int v) const {
        if (!isValidVertex(u, v)) {
            throw std::invalid_argument("Invalid vertex index");
        }
        if (u == v) {
            return true;
        }
        for (const Edge& edge : edges) {
            if ((edge.u == u && edge.v == v) || (edge.u == v && edge.v == u)) {
                return true;
            }
        }
        return false;
    }

    // Returns the weight of the edge connecting nodes u and v,
    // and INF if the two nodes are not directly linked by one edge.
    // If u and v are the same node, the weight returned is 0.
    int edgeWeight(int u, int v) const {
        if (u == v) {
            return 0;
        }
        if (!edgeConnects(u, v)) {
            return INF;
        }
        for (const Edge& edge : edges) {
            if ((edge.u == u && edge.v == v) || (edge.u == v && edge.v == u)) {
                return edge.weight;
            }
        }
        return INF;
    }

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

    // Implements the Floyd-Warshall algorithm.
    // Returns a V*V-sized matrix, with the element at (i, j) being the shortest
    // distance between nodes i and j.
    // If the graph is undirected, this will be a symmetric matrix.
    std::vector<std::vector<int>> shortestDistanceMatrix() const {

        std::vector<std::vector<int>> dist(V, std::vector<int>(V)); // initialise a V * V matrix 
        
        // set up the distance matrix with dist(y, x) = edgeWeight(y, x) if such an edge exists,
        // and INF otherwise
        for (int y = 0 ; y < V ; y++) {
            for (int x = 0 ; x < V ; x++) {
                if (y == x) {
                    dist[y][x] = 0; 
                }
                else if (!edgeConnects(y, x)) {
                    dist[y][x] = INF;
                }
                else {
                    dist[y][x] = edgeWeight(y, x);
                }
            }
        }

        // Consider each node k as a potential intermediary node.
        // If dist[y][k] + dist[k][x] is shorter than dist [y][x], we update dist[y][x] (passing
        // through the intermediary node k is the new shortest path between y and x).
        for (int k = 0 ; k < V ; k++) {
            for (int y = 0 ; y < V ; y++) {
                for (int x = 0 ; x < V ; x++) {
                    dist[y][x] = std::min(dist[y][x], dist[y][k] + dist[k][x]);
                    // replace by weight of y->k + k->x if that is shorter than y->x
                }
            }
        }
        return dist;
    }
};

