/**
 * Implementation of depth-first search algorithm.
 * 
 * This implementation is built for a Graph class which uses
 * an adjacency list. 
 * 
 */

#include <vector>
#include <stack>
#include <iostream>
#include <string>
#include <stdexcept>
#include <algorithm>

class Graph {
private:
    int V; // number of vertices
    std::vector<std::vector<int>> adj; // adjacency list

public:
    Graph() : V(0), adj(0) {}

    Graph(int numVertices) : V(numVertices), adj(numVertices) {}

    // adds an edge to the graph between nodes u and v (undirected graph)
    // @throws invalid_argument if either u or v are not valid nodes in the graph
    void addEdge(int u, int v) {
        if (u < 0 || u >= V || v < 0 || v >= V) {
            throw std::invalid_argument("index out of bounds for addEdge");
        }
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // displays the node count and the adjacency list (neighbours) of each node
    void printGraph() const {
        std::cout << "********  GRAPH ********" << std::endl;
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

    // performs a depth-first traversal of the graph and prints
    // the order in which the nodes were visited to the console
    // @throws invalid_argument if u or v are not valid vertices in the graph
    void depth_first_traversal(int start_node) const {
        if (start_node < 0 || start_node >= V) { 
            throw std::invalid_argument("Invalid starting node passed in to depth first traversal");
        }

        std::vector<bool> visited(V, false);
        std::stack<int> search_stack;

        visited[start_node] = true;
        search_stack.push(start_node);

        std::cout << "-- Performing depth-first traversal, order: --\n| ";

        while (!search_stack.empty()) {

            int current_node = search_stack.top();
            search_stack.pop();

            std::cout << " " << current_node;

            for (const int& neighbour_node : adj[current_node]) {
                if (visited[neighbour_node]) {
                    continue;
                }
                search_stack.push(neighbour_node);
                visited[neighbour_node] = true;
            }
        }
        std::cout << " |\n-- Depth-first traversal complete --" << std::endl;
    }

    // performs a depth-first search for the target_node, starting from start_node
    // @returns Returns an std::vector with the path of nodes to get from the start to the target.
    // @returns Returns an empty vector if the target is unreachable from the start node.
    std::vector<int> depth_first_search(int start_node, int target_node) const {

        if (start_node < 0 || start_node >= V) {
            throw std::invalid_argument("Invalid start_node index");
        }
        if (target_node < 0 || target_node >= V) {
            throw std::invalid_argument("Invalid target_node");
        }

        // handle special case 
        if (start_node == target_node) {
            return {start_node};
        }

        std::vector<bool> visited(V, false);
        std::stack<int> search_stack;
        std::vector<int> parent(V, -1); // used to keep track of predecessor (parent) of each node during DFS
        // a parent will be set for each node when the node is discovered
        // all elements initialised to -1 until they have been visited

        visited[start_node] = true;
        search_stack.push(start_node);

        while (!search_stack.empty()) {

            int current_node = search_stack.top();
            search_stack.pop();

            // check if we are at the target node
            if (current_node == target_node) {
                break;
            }

            for (const int& neighbour_node : adj[current_node]) {
                if (visited[neighbour_node]) {
                    continue;
                }
                visited[neighbour_node] = true;
                search_stack.push(neighbour_node);
                parent[neighbour_node] = current_node;
            }
        }

        // check if the target node was found
        if (visited[target_node] == false) {
            return {};
        }

        // reconstruct the path from the target to the start node
        std::vector<int> path;
        for (int path_tracer = target_node; path_tracer != -1; path_tracer = parent[path_tracer]) {
            path.push_back(path_tracer);
        }
        // reverse the path, since we traced from target to start
        std::reverse(path.begin(), path.end());

        return path;
    }
};


int main() {
    Graph g(7);

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(0, 4);
    g.addEdge(1, 5);
    g.addEdge(1, 3);
    g.addEdge(2, 6);
    g.addEdge(4, 5);

    g.printGraph();

    g.depth_first_traversal(0);

    std::vector<int> path = g.depth_first_search(0, 3);

    for (int i = 0 ; i < path.size() ; i++) {
        std::cout << path[i] << " ";
    }
    
}