/**
 * Implementation of an undirected graph.
 */

#include <vector>
#include <queue>
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>

// helper function to print a vector
template<typename T>
void printVector(const std::vector<T>& vec) {
    std::cout << "[";
    for (size_t i = 0; i < vec.size() - 1; i++) {
        std::cout << vec[i] << ", ";
    }
    std::cout << vec[vec.size()-1] << "]" << std::endl;
}

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

    // breadth first traversal of the graph
    void breadth_first_traversal(int starting_idx) const {

        std::cout << "Starting B-F traversal from index " << starting_idx << std::endl; 

        if (starting_idx < 0 || starting_idx >= V) {
            throw std::invalid_argument("Invalid starting index for BFT");
        }

        std::queue<int> search_queue; // queue of nodes to search
        std::vector<bool> visited(V, false); // vector to keep track of which nodes have been visited
        // we initialise it to have V elements, and each element is initially set to value false

        visited[starting_idx] = true;
        search_queue.push(starting_idx);

        std::vector<int> visited_nodes = {}; // this is just to visualise the order in which we visited the nodes

        while (!search_queue.empty()) {
            const int& current_node = search_queue.front();
            search_queue.pop();

            visited_nodes.push_back(current_node); // helper

            // enqueue the neighbours of our current node (unless they have already been visited)
            for (const int& neighbour : adj[current_node]) {
                if (visited[neighbour] == false) {
                    search_queue.push(neighbour);
                    visited[neighbour] = true; // once the neighbour node is "seen" it is considered visited
                }
            }
        }

        std::cout << "Nodes visited during BFT : \n";
        printVector(visited_nodes);
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

    g.breadth_first_traversal(2);
    
}