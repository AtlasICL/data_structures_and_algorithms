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
private:
    size_t m_V;
    std::vector<Edge> m_edgeList;

public:
    /**
     * @brief Checks whether two given nodes are neighbors.
     * @param fromNode Node which the edge originates from.
     * @param toNode Node which the edge arrives at.
     * @return Returns true if an edge exists from fromNode to toNode, false otherwise.
     * @throws std::out_of_range if either param is not in the graph.
     */
    bool edgeConnects(const size_t fromNode, const size_t toNode) const {
        if (fromNode >= m_V || toNode >= m_V) {
            throw std::out_of_range("No such node exists - WeightedDigraph::edgeConnects");
        }
        for (const Edge& edge : m_edgeList) {
            if (edge.from == fromNode && edge.to == toNode) return true;
        }
        return false;
    }

    /**
     * @brief Gets the weight of a given edge.
     * @param fromNode Node which the edge originates from.
     * @param toNode Node which the edge arrives at.
     * @return Returns the weight of the edge connceting two nodes.
     * @throws std::out_of_range if either param is not in the graph.
     * @throws std::invalid_argument if no edge connects fromNode and toNode.
     */
    int edgeWeight(const size_t fromNode, const size_t toNode) const {
        if (fromNode >= m_V || toNode >= m_V) {
            throw std::out_of_range("No such node exists - WeightedDigraph::edgeWeight");
        }
        if (!edgeConnects(fromNode, toNode)) {
            throw std::invalid_argument("No edge connects the given nodes - WeightedDigraph::edgeWeight");
        }
        for (const Edge& edge : m_edgeList) {
            if (edge.from == fromNode && edge.to == toNode) return edge.weight;
        }
    }

    /**
     * @brief Adds an edge connecting the given nodes.
     * @param fromNode Node which the edge originates from.
     * @param toNode Node which the edge arrives at.
     * @param weight Weight of the new edge.
     * @throws std::out_of_range if either param is not in the graph.
     * @throws std::invalid_argument if the edge already exists.
     */
    void addEdge(const std::size_t fromNode, const std::size_t toNode, const int weight) {
        if (!nodeExists(fromNode) || !nodeExists(toNode)) {
            throw std::out_of_range("Given node does not exist - WeightedDigraph::addEdge");
        }
        if (edgeConnects(fromNode, toNode)) {
            throw std::invalid_argument("Attempted to add an edge which already exists - WeightedDigraph::addEdge");
        }
        m_edgeList.push_back(Edge(fromNode, toNode, weight));
    }

    /**
     * @brief Sets the weight of the edge connecting the given nodes.
     * @param fromNode Node which the edge originates from.
     * @param toNode Node which the edge arrives at.
     * @param newWeight Weight which the edge will be set to.
     * @return Returns the old weight of the edge.
     * @throws std::out_of_range if fromNode or toNode are not in the graph.
     * @throws std::invalid_argument if no edge exists connecting the two nodes.
     */
    int setEdgeWeight(const std::size_t fromNode, const std::size_t toNode, const int newWeight) {
        if (!nodeExists(fromNode) || !nodeExists(toNode)) {
            throw std::out_of_range("Given node does not exist - WeightedDigraph::setEdgeWeight");
        }
        if (!edgeConnects(fromNode, toNode)) {
            throw std::invalid_argument("Given nodes are not connected - WeightedDigraph::setEdgeWeight");
        }
        const int oldWeight = edgeWeight(fromNode, toNode);
        for (Edge& edge : m_edgeList) {
            if (edge.from == fromNode && edge.to == toNode) {
                edge.weight = newWeight;
            }
        }
        return oldWeight;
    }

    /**
     * @brief Adds a new node into the graph.
     */
    void addNode() {
        m_V++;
    }

private:
    bool nodeExists(const size_t node) {
        return node < m_V;
    }
};

int main() {

}