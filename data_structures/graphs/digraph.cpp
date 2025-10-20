/*
Implementation of a directed graph (digraph).
*/

#include <iostream>
#include <stdexcept>
#include <vector>

/**
 * Implementation of a directed graph (digraph) using an adjacency list.
 */
class Digraph {
private: 
    size_t m_V; // number of vertices
    std::vector<std::vector<size_t>> m_adj; // adjacency list 

public:
    Digraph() : m_V(0), m_adj(0) {}

    Digraph(size_t V) : m_V(V), m_adj(V) {}
        
    void addEdge(size_t from, size_t to) {
        if (from >= m_V || to >= m_V) {
            throw std::out_of_range("Attempted to add invalid edge - no such node");
        }
        m_adj[from].push_back(to);
    } 
};
