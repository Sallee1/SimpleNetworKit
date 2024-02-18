#include "GraphAlgorithmImpl.h"

namespace nk = NetworKit;

namespace graph_object {
    nk::Graph* create(bool isDirected)
    {
        return nullptr;
    }

    nk::Graph* clone(nk::Graph* graph)
    {
        return nullptr;
    }

    nk::Graph* subGraph(nk::Graph* graph, int size, int* nodeIds)
    {
        return nullptr;
    }

    bool isDirected(nk::Graph* graph)
    {
        return false;
    }

    int getNodeCount(nk::Graph* graph)
    {
        return 0;
    }

    int getAllNodes(nk::Graph* graph, int* nodeIds)
    {
        return 0;
    }

    int getEdgeCount(nk::Graph* graph)
    {
        return 0;
    }

    int getAllEdges(nk::Graph* graph, int* edgeFrom, int* edgeTo)
    {
        return 0;
    }

    bool setEdgeWidget(nk::Graph* graph, int edgeFrom, int edgeTo, int widget)
    {
        return false;
    }

    bool addNode(nk::Graph* graph, int nodeId)
    {
        return false;
    }

    bool removeNode(nk::Graph* graph, int nodeId)
    {
        return false;
    }

    bool addEdge(nk::Graph* graph, int edgeFrom, int edgeTo)
    {
        return false;
    }

    bool removeEdge(nk::Graph* graph, int edgeFrom, int edgeTo)
    {
        return false;
    }

    bool destroy(nk::Graph* graph)
    {
        return false;
    }
}

namespace graph_algorithm {
    bool getDegree(nk::Graph* graph, int node, int* out_degree)
    {
        return false;
    }

    float getBetweenness(nk::Graph* graph, int node, float* out_betweenness)
    {
        return 0.0f;
    }

    int getKCore(nk::Graph* graph, int node, int* out_KCore)
    {
        return 0;
    }

    bool getDegreeDistribution(nk::Graph* graph, int* out_size, int* out_degree, float out_probability)
    {
        return false;
    }

    bool getDensity(nk::Graph* graph, float out_density)
    {
        return false;
    }
}