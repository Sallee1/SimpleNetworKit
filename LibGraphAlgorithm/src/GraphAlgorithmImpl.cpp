#include "GraphAlgorithmImpl.h"
#include <networkit/graph/Graph.hpp>
#include <networkit/graph/GraphTools.hpp>
#include <networkit/centrality/Betweenness.hpp>
#include <networkit/centrality/CoreDecomposition.hpp>

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
        // TODO: 这里会有内存泄漏的风险
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
        // TODO: 这里会有内存泄漏的风险
        auto edge_from_vec = new std::vector<uint64_t>;
        auto edge_to_vec = new std::vector<uint64_t>;
        for (auto edge : graph->edgeRange())
        {
            edge_from_vec->push_back(edge.u);
            edge_to_vec->push_back(edge.v);
        }
        edge_from = edge_from_vec->data();
        edge_to = edge_to_vec->data();
        return graph->numberOfEdges();
    }

    bool setEdgeWidget(nk::Graph* graph, uint64_t edge_from, uint64_t edge_to, float widget)
    {
        if (!graph->isWeighted()) return false;
        if (!graph->hasEdge(edge_from, edge_to)) return false;
        graph->setWeight(edge_from, edge_to, widget);
        return true;
    }

    uint64_t addNode(nk::Graph* graph)
    {
        return graph->addNode();
    }

    bool removeNode(nk::Graph* graph, uint64_t nodeId)
    {
        if (!graph->hasNode(nodeId))return false;
        graph->removeNode(nodeId);
        return true;
    }

    bool addEdge(nk::Graph* graph, uint64_t edge_from, uint64_t edge_to)
    {
        if (graph->hasNode(edge_from) || graph->hasNode(edge_to)) return false;
        if (graph->hasEdge(edge_from, edge_to))return false;
        graph->addEdge(edge_from, edge_to);
        return true;
    }

    bool removeEdge(nk::Graph* graph, uint64_t edge_from, uint64_t edge_to)
    {
        if (!graph->hasEdge(edge_from, edge_to))return false;
        graph->removeEdge(edge_from, edge_to);
        return true;
    }

    bool destroy(nk::Graph* graph)
    {
        if (graph == nullptr) return false;
        delete graph;
        return true;
    }
}

namespace graph_algorithm {
    bool getDegree(nk::Graph* graph, uint64_t node, uint64_t* out_degree)
    {
        if (!graph->hasNode(node)) return false;
        *out_degree = graph->degree(node);
        return true;
    }

    bool getBetweenness(nk::Graph* graph, uint64_t node, float* out_betweenness)
    {
        //TODO 介数分布是单独的类，需要重构以减少重复计算
        if (!graph->hasEdge(node))return false;
        *out_betweenness = nk::Betweenness(*graph).run().at(node);
        return true;
    }

    bool getKCore(nk::Graph* graph, uint64_t node, uint64_t* out_KCore)
    {
        //TODO K-Core分布是单独的类，需要重构以减少重复计算
        if (!graph->hasNode(node)) return 0;
        *out_KCore = nk::CoreDecomposition(*graph).kCore(node);
        return 0;
    }

    bool getDegreeDistribution(nk::Graph* graph, uint64_t* out_size, uint64_t* out_degree, float out_probability)
    {
        return false;
    }

    bool getDensity(nk::Graph* graph, float* out_density)
    {
        *out_density = static_cast<float>(graph->numberOfEdges()) / (graph->numberOfNodes() * (graph->numberOfNodes() - 1));
        return true;
    }
}