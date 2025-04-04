/**
 * Implementation of an unweighted, directed graph
 * using an adjacency list.
 */

#include <vector>
#include <iostream>
#include <string>
#include <stdexcept>

// helper function to print a vector
template<typename T>
void printVector(const std::vector<T>& vec) {
    std::cout << "[";
    if (vec.empty()) {
        std::cout << "]" << std::endl;
        return;
    }
    for (size_t i = 0; i < vec.size() - 1; i++) {
        std::cout << vec[i] << ", ";
    }
    std::cout << vec[vec.size()-1] << "]" << std::endl;
}

class DirectedGraph {
    private:
    int V; // number of vertices
    std::vector<std::vector<int>> adj; // adjacency list

public:
    DirectedGraph() : V(0), adj(0) {}
    DirectedGraph(int V) : V(V), adj(V) {}

    // add an edge to the graph, connecting u to v (order matters!)
    // @throws out_of_range if u or v are not valid vertices
    void addEdge(int u, int v) {
        if (u >= V || v >= V || u < 0 || v < 0) {
            throw std::out_of_range("Vertex index out of bounds");
        }
        adj[u].push_back(v);
    }

    // displays the node count and the adjacency list (neighbours) of each node
    void printGraph() const {
        std::cout << "***** DIRECTED GRAPH *****" << std::endl;
        std::cout << "---- Vertex count = " << V << " ----" << std::endl;
        for (int i = 0; i < V; i++) {
            std::cout << "| " << i << ": ";
            for (const auto& neighbor : adj[i]) {
                std::cout << neighbor << " ";
            }
            std::cout << "\n";
        }
        std::cout << "--------------------------" << std::endl;
    }
};

int main() {

    DirectedGraph g(5);

    g.addEdge(0, 1);
    g.addEdge(0, 4);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(3, 0);

    g.printGraph();
}