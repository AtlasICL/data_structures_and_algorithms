/**
 * Problem Week 10:
 * 
 * Exercise: implement a graph using an adjacency list and perform a
 * breadth-first search. 
 * 
 * Challenge: implement Kruskal's algorithms to find the minimum spanning
 * tree of a graph; and compare its results with Prim's algorithm.
 */

#include <vector>
#include <list>
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <queue>
#include <algorithm>


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


// Union-Find structure to detect cycles
class UnionFind {
private:
    std::vector<int> parent;
    std::vector<int> rank;

public:
    // initialise: each vertex is its own parent, and ranks start at 0
    UnionFind(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    // Find the representative (root) of the set that vertex i belongs to
    int find(int i) {
        if (parent[i] != i) {
            parent[i] = find(parent[i]);
        }
        return parent[i];
    }
    
    // union the sets that contain i and j. Returns true if the union was performed.
    bool unionSets(int i, int j) {
        int ri = find(i);
        int rj = find(j);
        if (ri == rj) {
            return false; // They are already in the same set.
        }
        
        // union by rank: attach the smaller tree to the root of the larger tree.
        if (rank[ri] < rank[rj]) {
            parent[ri] = rj;
        }
        else if (rank[ri] > rank[rj]) {
            parent[rj] = ri;
        }
        else {
            parent[rj] = ri;
            rank[ri]++;
        }
        return true;
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

    // Implements Prim's algorithm to find the Minimum Spanning Tree (MST) of the graph.
    // Prim's algorithm starts from an arbitrary node. This implementation starts from node 0 by default.
    // @returns Returns a list of edges which make up the MST.
    // @attention Assumes the graph is connected!
    std::vector<Edge> primsMST() const {
        if (m_V == 0 || m_V == 1) {
            return {};
        }

        std::vector<Edge> mst;
        std::vector<bool> inMST(m_V, false); // to keep track of which nodes are in the MST

        struct EdgeCompare {
            bool operator()(const Edge& e1, const Edge& e2) const {
                return e1.weight > e2.weight; // e1 is consider lower prio if its weight is larger
            }
        };

        // Priority queue, to get the edge with the smallest weight.
        std::priority_queue<Edge, std::vector<Edge>, EdgeCompare> prioQueue;

        // Lambda function, which adds all the edges connected to node u
        // which lead to nodes not yet in the mst (hence "crossing"). 
        auto addCrossingEdges = [&](int u) {
            inMST[u] = true; // node u is now in the MST
            std::vector<int> neighbours = getNeighbourhood(u);
            // add the edges, if they connect to a node not in the MST
            for (int neighbour : neighbours) {
                if (!inMST[neighbour]) {
                    int weight = getEdgeWeight(u, neighbour);
                    prioQueue.push(Edge(u, neighbour, weight));
                }
            }
        };

        // Start from vertex 0. It is guaranteed to exist.
        addCrossingEdges(0);

        // Keep adding edges until we have (m_V - 1) edges in the MST (property of trees).
        while (!prioQueue.empty() && mst.size() < static_cast<size_t>(m_V - 1)) {
            Edge currEdge = prioQueue.top(); // Edge with lowest weight
            prioQueue.pop(); // Remove current edge.
            
            // Determine which of the 2 nodes connected to the edge is NOT already in the MST.
            int nodeToAdd = inMST[currEdge.u] ? currEdge.v : currEdge.u;

            if (inMST[nodeToAdd]) { // this means both sides of the edge were already in the MST
                continue; // so we skip this edge.
            }

            mst.push_back(currEdge); // add the current edge to the MST
            addCrossingEdges(nodeToAdd); // and add the crossing edges from the node just added
        }
        return mst;
    }

    // Kruskal's algorithm to compute the MST
    // @returns the MST as an std::vector<Edge>
    // @attention This assumes the Graph is connected!
    std::vector<Edge> kruskalMST() {
        std::vector<Edge> mst; // vector which stores the edges which comprise the MST

        // sort the edges of the graph by ascending weight (using a lambda to compare weights)
        std::sort(m_edges.begin(), m_edges.end(), [](const Edge &a, const Edge &b){return a.weight < b.weight;});

        // initialise a UnionFind class for V vertices 
        UnionFind uf(m_V);

        // process edges in sorted order
        for (const auto& edge : m_edges) {
            // only add the edge to the MST if it does not create a cycle
            // we check this using UnionFind
            if (uf.unionSets(edge.u, edge.v) == true) {
                mst.push_back(edge);
                // if we have V-1 edges, the MST is complete (property of trees) IF GRAPH IS CONNECTED!
                if (mst.size() == m_V - 1) {
                    break;
                }
            }
        }
        return mst;
    }
};

// helper function to print a vector
template<typename T>
void printVector(const std::vector<T>& vec) {
    std::cout << "[";
    for (size_t i = 0; i < vec.size() - 1; i++) {
        std::cout << vec[i] << ", ";
    }
    std::cout << vec[vec.size()-1] << "]" << std::endl;
}

// Overload the stream insertion operator for the Edge struct.
std::ostream& operator<<(std::ostream& os, const Edge& edge) {
    os << "Edge(" << edge.u << ", " << edge.v << ", weight: " << edge.weight << ")";
    return os;  // Return the stream to allow chaining.
}

int main() {

    WeightedUndirectedGraph g(6); 
    g.addEdge(0, 1, 1);
    g.addEdge(0, 2, 10);
    g.addEdge(1, 2, 2);
    g.addEdge(1, 3, 6);
    g.addEdge(2, 3, 1);
    g.addEdge(2, 4, 5);
    g.addEdge(3, 4, 1);
    g.addEdge(4, 5, 2);
    
    std::vector<Edge> kruskalMST = g.kruskalMST();
    std::vector<Edge> primsMST = g.primsMST();

    printVector(kruskalMST);
    printVector(primsMST);
}
