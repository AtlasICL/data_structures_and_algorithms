/**
 * Implementation of Kruskal's algorithm for finding
 * the MST or MSF of a weighted, undirected graph.
 */

/**
 * NOTE:
 * 
 * Q: What is an MST ?
 * A: A minimum spanning tree (MST) is a subset of the edges of a connected, edge-weighted graph that connects all vertices 
 * without any cycles and with the minimum possible total edge weight. 
 * It is a way of finding the most economical way to connect a set of vertices. 
 * A minimum spanning tree is not necessarily unique.
 */

#include <vector>
#include <iostream>
#include <stdexcept>
#include <algorithm>

// struct to represent an edge in the graph
struct Edge {
    int u;
    int v;
    int weight;
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

// Graph class for a weighted undirected graph, using an edge list
class Graph {
private:
    int V; // vertex count
    std::vector<Edge> edges; // edges

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

    // Kruskal's algorithm to compute the MST
    // @returns the MST as an std::vector<Edge>
    // @attention This assumes the Graph is connected!
    std::vector<Edge> kruskalMST() {
        std::vector<Edge> mst; // vector which stores the edges which comprise the MST

        // sort the edges of the graph by ascending weight (using a lambda to compare weights)
        std::sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b){return a.weight < b.weight;});

        // initialise a UnionFind class for V vertices 
        UnionFind uf(V);

        // process edges in sorted order
        for (const auto& edge : edges) {
            // only add the edge to the MST if it does not create a cycle
            // we check this using UnionFind
            if (uf.unionSets(edge.u, edge.v) == true) {
                mst.push_back(edge);
                // if we have V-1 edges, the MST is complete (property of trees) IF GRAPH IS CONNECTED!
                if (mst.size() == V - 1) {
                    break;
                }
            }
        }
        return mst;
    }

    // Kruskal's algorithm to compute the MSF (Minimum Spanning Forest)
    // @returns the MSF as an std::vector<Edge>
    // @attention This version accomodates graphs which are not connected
    std::vector<Edge> kruskalMSF() {
        std::vector<Edge> msf; // vector which stores the edges which comprise the MSF

        // sort the edges of the graph by ascending weight (using a lambda to compare weights)
        std::sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b){return a.weight < b.weight;});

        // initialise a UnionFind class for V vertices 
        UnionFind uf(V);

        // process edges in sorted order
        for (const auto& edge : edges) {
            // only add the edge to the MSF if it does not create a cycle
            // we check this using UnionFind
            if (uf.unionSets(edge.u, edge.v) == true) {
                msf.push_back(edge);
            }
        }
        return msf;
    }
};
