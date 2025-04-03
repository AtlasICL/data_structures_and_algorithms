/**
 * Implementation of an unweighted, undirected graph,
 * using an adjacency list.
 */

#include <vector>
#include <queue>
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <algorithm>

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

    // breadth-first search to find the shortest path between 2 nodes in the graph
    // @returns a vector with the path between the 2 nodes, or an empty vector if no path exists
    // @throws invalid_argument if starting node or target node are invalid
    std::vector<int> breadth_first_search(int starting_node, int target_node) const {

        // validate starting node
        if (starting_node < 0 || starting_node >= V) { 
            throw std::invalid_argument("Invalid index for starting node");
        }

        // validate target node
        if (target_node < 0 || target_node >= V) {
            throw std::invalid_argument("Invalid index for target node");
        }

        std::queue<int> search_queue; // queue of nodes to search
        std::vector<bool> visited(V, false); // vector to keep track of which nodes have been visited
        // we initialise it to have V elements, and each element is initially set to value false

        std::vector<int> parent(V, -1); // used to keep track of predecessor (parent) of each node during BFS
        // a parent will be set for each node when the node is discovered
        // all elements initialised to -1 until they have been visited

        visited[starting_node] = true;
        search_queue.push(starting_node);

        while (!search_queue.empty()) {
            const int& current_node = search_queue.front();
            search_queue.pop();

            // check if we've reached the target
            if (current_node == target_node) {
                break;
            }

            for (const int& neighbour : adj[current_node]) {
                if (visited[neighbour] == false) {
                    visited[neighbour] = true;
                    parent[neighbour] = current_node;
                    search_queue.push(neighbour);
                }
            }
        }

        // if the target was never visited, it must be unreachable from the starting node
        if (visited[target_node] == false) {
            return {};
        }

        // reconstruct the path from target to start using parents
        // we start from the target, and go upwards (to the parent each time)
        std::vector<int> path;
        for (int curr_node = target_node; curr_node != -1; curr_node = parent[curr_node]) {
            path.push_back(curr_node);
        }
        // since we built the path by going from the *target* to the *starting node*, we reverse the path before returning it
        std::reverse(path.begin(), path.end());

        return path;
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