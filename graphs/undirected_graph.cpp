/**
 * Implementation of an undirected graph.
 */

#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>

class UndirectedGraph {

private:
    int V; // number of vertices
    std::vector<std::vector<int>> adj; // adjacency list

public:
    UndirectedGraph() : V(0), adj(0) {}
    UndirectedGraph(int V) : V(V), adj(V) {}

    // add an edge to the graph
    // @throws out_of_range if u or v are not valid vertices
    void addEdge(int u, int v) {
        if (u >= V || v >= V || u < 0 || v < 0) {
            throw std::out_of_range("Vertex index out of bounds");
        }
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // displays the node count and the adjacency list (neighbours) of each node
    void printGraph() const {
        std::cout << "**** UNDIRECTED GRAPH ****" << std::endl;
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

    UndirectedGraph g(5);

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