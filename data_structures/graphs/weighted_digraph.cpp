/**
 * Implementation of a weighted directed graph.
 */

#include <vector>
#include <stdexcept>

struct Edge {
    size_t from;
    size_t to;
    int weight;

    Edge(size_t from, size_t to, int weight) : from(from), to(to), weight(weight) {}
};

class WeightedDigraph {

};