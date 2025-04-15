#include <vector>
#include <algorithm>
#include <limits>
#include <stdexcept>

constexpr int INF = std::numeric_limits<int>::max() / 2;

// directed weighted edge
struct Edge {
    int from;
    int to;
    int weight;

    Edge(int from, int to, int weight) : from(from), to(to), weight(weight) {} 
};

// Weighted directed graph.
class Graph {
private: 
    int m_V; // number of nodes in the graph
    std::vector<Edge> m_edges; // adjacency list

    // @returns Returns true if u is a valid node in the graph, false otherwise.
    bool isValidVertex(int u) const {
        return (u >= 0 && u < m_V);
    }

    // @returns Returns true if both u and v are valid nodes in the graph, false otherwise.
    bool isValidVertex(int u, int v) const {
        return (u >= 0 && u < m_V && v >= 0 && v < m_V);
    }

    // @returns Returns true if an edge directly connects nodes u and v.
    // @returns Returns false if source and destination are the same node, since an edge does not connect them.
    // @throws Throws an invalid argument exception if u or v are not valid nodes.
    bool edgeConnects(int source, int destination) const {
        if (!isValidVertex(source, destination)) {
            throw std::invalid_argument("Source and destination must be valid nodes for edgeConnects()");
        }
        for (const Edge& edge : m_edges) {
            if (edge.from == source && edge.to == destination) {
                return true;
            }
        }
        return false;
    }

    // @returns Returns the weight of the edge directly connecting u to v, if it exists.
    // @returns If u and v are the same node, the weight is 0.
    // @throws Throws an invalid argument exception if u or v are not valid nodes.
    // @thows Throws a runtime error if u and v are not directly connected by an edge.
    int edgeWeight(int source, int destination) const {
        if (!isValidVertex(source, destination)) {
            throw std::invalid_argument("Invalid vertex for edgeWeight");
        }
        for (const Edge& edge : m_edges) {
            if (edge.from == source && edge.to == destination) {
                return edge.weight;
            }
        }
        throw std::runtime_error("Source and destination are not connected.");
    }

public:
    explicit Graph(int V) : m_V(V) {}

    // adds an edge from 'from' to 'to', with weight 'weight'.
    // @throws Throws an invalid argument exception if from or to are not valid nodes in the graph.
    void addEdge(int source, int destination, int weight) {
        if (!isValidVertex(source, destination)) {
            throw std::invalid_argument("Invalid vertex for addEdge");
        }
        m_edges.push_back(Edge{source, destination, weight});
    }

    // Implements the Floyd-Warshall algorithm.
    // @returns Returns a V*V matrix with the shortest weight to get from i to j.
    std::vector<std::vector<int>> floydWarshall() const {

        // initialise a V*V matrix, with default value INF
        std::vector<std::vector<int>> dist(m_V, std::vector<int>(m_V, INF)); // distance matrix
        
        for (int i = 0 ; i < m_V ; i++) {
            for (int j = 0 ; j < m_V ; j++) {
                if (i == j) {
                    dist[i][j] = 0; // distance to self is 0
                }
                else if (edgeConnects(i, j)) {
                    dist[i][j] = edgeWeight(i, j);
                }
            }
        }

        // consider intermediate nodes
        for (int k = 0 ; k < m_V ; k++) {
            for (int i = 0 ; i < m_V ; i++) {
                for (int j = 0 ; j < m_V ; j++) {
                    if ((dist[i][k] < INF && dist[k][j] < INF) && dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }

        return dist;
    }

    // @returns Returns the shortest path from the source node to the destination node.
    // Return type is a std::vector. Output format: {node1, node2, ..., destination}.
    // The source node is NOT included in the output. If source and destination are the same node, 
    // the output will be {destination}. 
    // If no path exists between the source and destination nodes, returns an empty vector.
    // @throws Raises an illegal argument exception if source or destination are not valid nodes in the graph.
    std::vector<int> shortestPath(int source, int destination) {
        if (!isValidVertex(source, destination)) {
            throw std::invalid_argument("Invalid vertex for shortestPath");
        }
        if (source == destination) {
            return {destination};
        }

        std::vector<std::vector<int>> dist(m_V, std::vector<int>(m_V, INF)); // distance matrix
        std::vector<std::vector<int>> next(m_V, std::vector<int>(m_V, -1));
        
        for (int i = 0 ; i < m_V ; i++) {
            for (int j = 0 ; j < m_V ; j++) {
                if (i == j) {
                    dist[i][j] = 0;
                    next[i][j] = i;
                }
                else if (edgeConnects(i, j)) {
                    dist[i][j] = edgeWeight(i, j);
                    next[i][j] = j;
                }
            }
        }

        // consider intermediary "k" nodes
        for (int k = 0 ; k < m_V ; k++) {
            for (int i = 0 ; i < m_V ; i++) {
                for (int j = 0 ; j < m_V ; j++) {
                    if ((dist[i][k] < INF && dist[k][j] < INF) && (dist[i][k] + dist[k][j] < dist[i][j])) {
                        dist[i][j] = dist[i][k] + dist[k][j]; // shortened distance through intermediary node k
                        next[i][j] = next[i][k];
                    }
                }
            }
        }

        if (next[source][destination] == -1) { // no path exists
            return {};
        }

        std::vector<int> path;
        for (int curr = source ; curr != destination ; curr = next[curr][destination]) {
            path.push_back(curr);
        }
        path.push_back(destination); // add the destination node to the path
        path.erase(path.begin()); // we do not include the source node in the path we return

        return path;
    }
};
