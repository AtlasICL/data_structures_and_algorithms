/**
 * Implementation of a weighted undirected graph.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

// Struct to represent an edge in the weighted undirected graph.
struct Edge {
    int u;
    int v;
    int weight;

    explicit Edge(int u, int v, int weight) : u(u), v(v), weight(weight) {}

    // Comparison operator (==) overload, to compare equality of 2 given edges.
    // Since the graph is undirected, u and v are interchangeable.
    bool operator==(const Edge& other) const {
        return ((u == other.u && v == other.v) || (u == other.v && v == other.u)) && weight == other.weight;
    }
};

// Weighted undirected graph. 
class WeightedUndirectedGraph {
private:
    int m_V; // node count
    std::vector<Edge> m_edges; // edge list

    // @returns Returns true if u is a valid node in the graph.
    bool isValidNode(int u) const noexcept {
        return u >= 0 && u < m_V;
    }

    // @returns Returns true if both u and v are valid nodes in the graph.
    bool isValidNode(int u, int v) const noexcept {
        return isValidNode(u) && isValidNode(v);
    }

    // @returns Returns true if an edge exists directly connecting nodes u and v.
    // @throws Raises an invalid argument exception if u or v are not valid nodes.
    bool edgeExists(int u, int v) const {
        if (!isValidNode(u, v)) {
            throw std::invalid_argument("Invalid vertex");
        }
        for (const Edge& edge : m_edges) {
            if ((edge.u == u && edge.v == v) || (edge.u == v && edge.v == u)) {
                return true;
            }
        }
        return false;
    }

    // @returns Returns the weight of the edge between nodes u and v.
    // @throws Raises an invalid argument exception if u and v are not valid nodes in the graph.
    // @throws Raises a runtime exception if no edge exists between u and v.
    int getEdgeWeight(int u, int v) const {
        if (!isValidNode(u, v)) {
            throw std::invalid_argument("Invalid vertex for getEdgeWeight");
        }
        if (!edgeExists(u, v)) {
            throw std::runtime_error("Given edge does not exist");
        }
        for (const Edge& edge : m_edges) {
            if ((edge.u == u && edge.v == v) || (edge.u == v && edge.v == u)) {
                return edge.weight;
            }
        }
        throw std::runtime_error("Given edge does not exist");
    }

    // @returns Returns the neighbourhood of the given node.
    // @returns Returns an empty vector if the node has no neighbours.
    // @throws Raises an invalid argument exception if u is not a valid node.
    std::vector<int> getNeighbourhood(int u) const {
        if (!isValidNode(u)) {
            throw std::invalid_argument("Invalid node in getNeighbourhood");
        }
        std::vector<int> neighbours = {};
        for (const Edge& edge : m_edges) {
            if (edge.u == u) {
                neighbours.push_back(edge.v);
            }
            if (edge.v == u) {
                neighbours.push_back(edge.u);
            }
        }
        return neighbours;
    }

    // @returns Returns the number of neighbours of the given node.
    // @returns Returns 0 if the node has no neighbours.
    // @throws Raises an invalid argument exception if the given node is not a valid node.
    int getNeighbourCount(int u) const {
        if (!isValidNode(u)) {
            throw std::invalid_argument("Invalid node for getNeighbourCount");
        }
        return getNeighbourhood(u).size();
    }

public:
    explicit WeightedUndirectedGraph(int V) : m_V(V), m_edges({}) {}

    // @returns Adds an (undirected) edge to the graph, connecting nodes u and v.
    // @throws Raises an invalid argument exception if u and v are not valid nodes in the graph.
    // @throws Raises a runtime exception if an edge already exists between u and v.
    void addEdge(int u, int v, int weight) {
        if (!isValidNode(u, v)) {
            throw std::invalid_argument("Invalid vertex for addEdge");
        }
        if (edgeExists(u, v)) {
            throw std::runtime_error("Edge already exists");
        }
        m_edges.push_back(Edge{u, v, weight});
    }

    // @returns Removes the edge between nodes u and v.
    // @throws Raises an invalid argument exception if u and v are not valid nodes in the graph.
    // @throws Throws a runtime error if no edge exists between nodes u and v.
    // @note NOTE: Each pair of nodes is guaranteed to only have 1 edge directly connecting them. 
    void removeEdge(int u, int v) {
        if (!isValidNode(u, v)) {
            throw std::invalid_argument("Invalid vertex for removeEdge");
        }
        if (!edgeExists(u, v)) {
            throw std::runtime_error("Attempting to remove nonexistant edge");
        }
        std::vector<Edge>::iterator it = std::find(m_edges.begin(), m_edges.end(), Edge{u, v, getEdgeWeight(u, v)});
        if (it != m_edges.end()) {
            m_edges.erase(it);
            return;
        }
        // NOTE: The std::find which searched for the edge implicity also searches for {v, u} edge (as well as {u, v}). 
        // See the == operator overload in Edge struct.
    }

    // @returns Updates the weight of the edge directly connecting nodes u and v.
    // @throws Raises an invalid argument exception if u and v are not valid nodes in the graph.
    // @throws Throws a runtime error if no edge exists between nodes u and v.
    // @note NOTE: Each pair of nodes is guaranteed to only have 1 edge directly connecting them. 
    void updateEdgeWeight(int u, int v, int newWeight) {
        if (!isValidNode(u, v)) {
            throw std::invalid_argument("Invalid vertex for updateEdgeWeight");
        }
        if (!edgeExists(u, v)) {
            throw std::runtime_error("Attempting to update weight of nonexistant edge");
        }
        removeEdge(u, v); // delete the pre-existing edge
        m_edges.push_back(Edge{u, v, newWeight}); // add an edge with the new weight
    }

    // Prints the graph, displaying the nodes that each node is connected to.
    void print() const {
        std::cout << "**** Undirected weighted graph on " << m_V << " nodes ****\n";
        for (int u = 0 ; u < m_V ; u++) {
            std::cout << " ~" << u << " -> ";
            std::vector<int> neighbours = getNeighbourhood(u);
            for (int neighbour = 0; neighbour < neighbours.size(); neighbour++) {
                std::cout << neighbours[neighbour] << " ";
            }
            std::cout << std::endl;
        }
    }
};
