#pragma once
#include <stdint.h>
#include <vector>

namespace NetworKit {
    class Graph;
};

class GraphCInterface {

};

namespace graph_object {
    NetworKit::Graph* create(bool is_directed, bool is_weighted);

    NetworKit::Graph* clone(NetworKit::Graph* graph);

    NetworKit::Graph* subGraph(NetworKit::Graph* graph, uint64_t size, uint64_t* node_ids);

    bool isDirected(NetworKit::Graph* graph);

    bool isWeighted(NetworKit::Graph* graph);

    uint64_t getNodeCount(NetworKit::Graph* graph);

    uint64_t getAllNodes(NetworKit::Graph* graph, uint64_t* node_ids);

    uint64_t getEdgeCount(NetworKit::Graph* graph);

    uint64_t getAllEdges(NetworKit::Graph* graph, uint64_t* edge_from, uint64_t* edge_to);

    bool setEdgeWidget(NetworKit::Graph* graph, uint64_t edge_from, uint64_t edge_to, float widget);

    uint64_t addNode(NetworKit::Graph* graph);

    bool removeNode(NetworKit::Graph* graph, uint64_t node_id);

    bool addEdge(NetworKit::Graph* graph, uint64_t edge_from, uint64_t edge_to);

    bool removeEdge(NetworKit::Graph* graph, uint64_t edge_from, uint64_t edge_to);

    bool destroy(NetworKit::Graph* graph);
}
namespace graph_algorithm
{
    bool getDegree(NetworKit::Graph* graph, uint64_t node, uint64_t* out_degree);

    bool getBetweenness(NetworKit::Graph* graph, uint64_t node, float* out_betweenness);

    bool getKCore(NetworKit::Graph* graph, uint64_t node, uint64_t* out_KCore);

    bool getDegreeDistribution(NetworKit::Graph* graph, uint64_t* out_size, uint64_t* out_degree, float out_probability);

    bool getDensity(NetworKit::Graph* graph, float* out_density);
}