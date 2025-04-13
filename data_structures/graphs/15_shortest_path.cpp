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
            if (edge.u == u && edge.v == v || edge.u == v && edge.v == u) {
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

    // Returns the shortest path between nodes source and destination.
    // If u and v are the same node, will return an empty vector.
    // If no path exists between source and destination, throws a runtime error.
    std::vector<int> shortestPath(int source, int destination) const {
        if (!isValidVertex(source, destination)) {
            throw std::invalid_argument("Invalid vertex");
        }

        // special case where source == destination
        if (source == destination) {
            return {};
        }
        
        std::vector<std::vector<int>> dist(V, std::vector<int>(V, INF)); // distance matrix
        // parent[i][j] will hold the immediate predecessor of j on the path from i.
        std::vector<std::vector<int>> parent(V, std::vector<int>(V, -1));

        for (int y = 0 ; y < V ; y++) {
            for (int x = 0 ; x < V ; x++) {
                if (y == x) {
                    dist[y][x] = 0; // (distance to self)
                    parent[y][x] = y; // self-path 
                }
                else if (!edgeConnects(y, x)) {
                    dist[y][x] = INF; // this is technically redundant since dist has been initialised with INF values
                    // parent[y][x] remains -1;
                }
                else {
                    dist[y][x] = edgeWeight(y, x);
                    parent[y][x] = y; // for a direct connection, the parent of destination is source
                }
            }
        }

        // Considering intermediate vertices
        for (int k = 0 ; k < V ; k++) {
            for (int y = 0 ; y < V ; y++) {
                for (int x = 0 ; x < V ; x++) {
                    
                    if (dist[y][k] < INF && dist[k][x] < INF &&
                        dist[y][k] + dist[k][x] < dist[y][x]) { // check if a shorter path exists by passing through k
                            
                        dist[y][x] = dist[y][k] + dist[k][x];
                        // Update parent: the parent of j in the new path is the parent from k to j.
                        parent[y][x] = parent[k][x]; 
                    }

                }
            }
        }

        // If no path exists between source and destination, 
        // then parent[source][destination] will be -1. 
        // This assumes that source and destination are _distinct_ nodes, which we ensured
        // by checking source == destination earlier in the function, with an early return.
        if (parent[source][destination] == -1) {
            throw std::runtime_error("No path exists. \nEnsure a path exists between source and destination when calling shortestPath.");
        }

        std::vector<int> path;
        int curr_node = destination;
        while (curr_node != source) {
            path.push_back(curr_node);
            curr_node = parent[source][curr_node];
        }
        path.push_back(source); // include the source node

        // the path was constructed in reverse order (from destination to source), so we reverse it
        std::reverse(path.begin(), path.end());
        return path;
    }

    // Also returns the shortest path between nodes source and destination.
    // If u and v are the same node, will return an empty vector.
    // If no path exists between source and destination, throws a runtime error.
    // ! This implementation of the function uses the next (look-forward) setup
    // instead of the parent setup. 
    // This isn't strictly necessary, I just wanted to write the function both ways
    // to get a deeper understanding.
    std::vector<int> shortestPathAlt(int source, int destination) const {
        if (!isValidVertex(source, destination)) {
            throw std::runtime_error("Invalid vertices for shortest path.");
        }

        if (source == destination) {
            return {};
        }

        std::vector<std::vector<int>> dist(V, std::vector<int>(V, INF)); // V*V matrix with default value INF
        std::vector<std::vector<int>> next(V, std::vector<int>(V, -1)); // V*V matrix with default value -1

    }
};

