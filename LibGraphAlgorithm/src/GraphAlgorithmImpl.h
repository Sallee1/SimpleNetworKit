#pragma once

namespace NetworKit {
    class Graph;
};

namespace graph_object {
    NetworKit::Graph* create(bool isDirected);

    NetworKit::Graph* clone(NetworKit::Graph* graph);

    NetworKit::Graph* subGraph(NetworKit::Graph* graph, int size, int* nodeIds);

    bool isDirected(NetworKit::Graph* graph);

    int getNodeCount(NetworKit::Graph* graph);

    int getAllNodes(NetworKit::Graph* graph, int* nodeIds);

    int getEdgeCount(NetworKit::Graph* graph);

    int getAllEdges(NetworKit::Graph* graph, int* edgeFrom, int* edgeTo);

    bool setEdgeWidget(NetworKit::Graph* graph, int edgeFrom, int edgeTo, int widget);

    bool addNode(NetworKit::Graph* graph, int nodeId);

    bool removeNode(NetworKit::Graph* graph, int nodeId);

    bool addEdge(NetworKit::Graph* graph, int edgeFrom, int edgeTo);

    bool removeEdge(NetworKit::Graph* graph, int edgeFrom, int edgeTo);

    bool destroy(NetworKit::Graph* graph);
}

namespace graph_algorithm
{
    bool getDegree(NetworKit::Graph* graph, int node, int* out_degree);

    float getBetweenness(NetworKit::Graph* graph, int node, float* out_betweenness);

    int getKCore(NetworKit::Graph* graph, int node, int* out_KCore);

    bool getDegreeDistribution(NetworKit::Graph* graph, int* out_size, int* out_degree, float out_probability);

    bool getDensity(NetworKit::Graph* graph, float out_density);
}