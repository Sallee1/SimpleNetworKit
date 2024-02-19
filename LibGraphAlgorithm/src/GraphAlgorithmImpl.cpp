#include "GraphAlgorithmImpl.h"
#include <networkit/graph/Graph.hpp>
#include <networkit/graph/GraphTools.hpp>

namespace nk = NetworKit;

namespace graph_object {
    nk::Graph* create(bool is_directed, bool is_weighted)
    {
        nk::Graph* graph = new nk::Graph(0, is_weighted, is_directed);
        return graph;
    }

    nk::Graph* clone(nk::Graph* graph)
    {
        return new nk::Graph(*graph);
    }

    nk::Graph* subGraph(nk::Graph* graph, uint64_t size, uint64_t* node_ids)
    {
        std::unordered_set<nk::node> nodes;
        for (uint64_t i = 0; i < size; i++)
        {
            nodes.emplace(nk::node(node_ids[i]));
        }
        return new nk::Graph(nk::GraphTools::subgraphFromNodes(*graph, nodes));
    }

    bool isDirected(nk::Graph* graph)
    {
        return graph->isDirected();
    }

    bool isWeighted(nk::Graph* graph)
    {
        return graph->isWeighted();
    }

    uint64_t getNodeCount(nk::Graph* graph)
    {
        return graph->numberOfNodes();
    }

    uint64_t getAllNodes(nk::Graph* graph, uint64_t* node_ids)
    {
        auto node_ids_vec = new std::vector<uint64_t>;
        for (auto node : graph->nodeRange())
        {
            node_ids_vec->push_back(node);
        }
        node_ids = node_ids_vec->data();
        return graph->numberOfNodes();
    }

    uint64_t getEdgeCount(nk::Graph* graph)
    {
        return graph->numberOfEdges();
    }

    uint64_t getAllEdges(nk::Graph* graph, uint64_t* edge_from, uint64_t* edge_to)
    {
        return graph->numberOfEdges();
    }

    bool setEdgeWidget(nk::Graph* graph, uint64_t edge_from, uint64_t edge_to, float widget)
    {
        return false;
    }

    bool addNode(nk::Graph* graph, uint64_t nodeId)
    {
        return false;
    }

    bool removeNode(nk::Graph* graph, uint64_t nodeId)
    {
        return false;
    }

    bool addEdge(nk::Graph* graph, uint64_t edge_from, uint64_t edge_to)
    {
        return false;
    }

    bool removeEdge(nk::Graph* graph, uint64_t edge_from, uint64_t edge_to)
    {
        return false;
    }

    bool destroy(nk::Graph* graph)
    {
        return false;
    }
}

namespace graph_algorithm {
    bool getDegree(nk::Graph* graph, uint64_t node, uint64_t* out_degree)
    {
        return false;
    }

    float getBetweenness(nk::Graph* graph, uint64_t node, float* out_betweenness)
    {
        return 0.0f;
    }

    uint64_t getKCore(nk::Graph* graph, uint64_t node, uint64_t* out_KCore)
    {
        return 0;
    }

    bool getDegreeDistribution(nk::Graph* graph, uint64_t* out_size, uint64_t* out_degree, float out_probability)
    {
        return false;
    }

    bool getDensity(nk::Graph* graph, float out_density)
    {
        return false;
    }
}