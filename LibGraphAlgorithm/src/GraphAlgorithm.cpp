#include "GraphAlgorithm.h"
#include "GraphAlgorithmImpl.h"
#include <networkit/graph/Graph.hpp>

namespace nk = NetworKit;

pGraph graph_create(bool isDirected)
{
    return graph_object::create(isDirected);
}

pGraph graph_clone(pGraph graph)
{
    return graph_object::clone(static_cast<nk::Graph*>(graph));
}

pGraph graph_subGraph(pGraph graph, int size, int* nodeIds)
{
    return graph_object::subGraph(static_cast<nk::Graph*>(graph), size, nodeIds);
}

bool graph_isDirected(pGraph graph)
{
    return graph_object::isDirected(static_cast<nk::Graph*>(graph));
}

int graph_getAllNodes(pGraph graph, int* nodeIds)
{
    return graph_object::getAllNodes(static_cast<nk::Graph*>(graph), nodeIds);
}

int graph_getEdgeCount(pGraph graph)
{
    return graph_object::getEdgeCount(static_cast<nk::Graph*>(graph));
}

int graph_getAllEdges(pGraph graph, int* edgeFrom, int* edgeTo)
{
    return graph_object::getAllEdges(static_cast<nk::Graph*>(graph), edgeFrom, edgeTo);
}

bool graph_setEdgeWidget(pGraph graph, int edgeFrom, int edgeTo, int widget)
{
    return graph_object::setEdgeWidget(static_cast<nk::Graph*>(graph), edgeFrom, edgeTo, widget);
}

bool graph_addNode(pGraph graph, int nodeId)
{
    return graph_object::addNode(static_cast<nk::Graph*>(graph), nodeId);
}

bool graph_removeNode(pGraph graph, int nodeId)
{
    return graph_object::removeNode(static_cast<nk::Graph*>(graph), nodeId);
}

bool graph_addEdge(pGraph graph, int edgeFrom, int edgeTo)
{
    return graph_object::addEdge(static_cast<nk::Graph*>(graph), edgeFrom, edgeTo);
}

bool graph_removeEdge(pGraph graph, int edgeFrom, int edgeTo)
{
    return graph_object::removeEdge(static_cast<nk::Graph*>(graph), edgeFrom, edgeTo);
}

bool graph_destroy(pGraph graph)
{
    return graph_object::destroy(static_cast<nk::Graph*>(graph));
}

bool graphAlgorithm_getDegree(pGraph graph, int node, int* out_degree)
{
    return graph_algorithm::getDegree(static_cast<nk::Graph*>(graph), node, out_degree);
}

float graphAlgorithm_getBetweenness(pGraph graph, int node, float* out_betweenness)
{
    return graph_algorithm::getBetweenness(static_cast<nk::Graph*>(graph), node, out_betweenness);
}

int graphAlgorithm_getKCore(pGraph graph, int node, int* out_KCore)
{
    return graph_algorithm::getKCore(static_cast<nk::Graph*>(graph), node, out_KCore);
}

bool graphAlgorithm_getDegreeDistribution(pGraph graph, int* out_size, int* out_degree, float out_probability)
{
    return graph_algorithm::getDegreeDistribution(static_cast<nk::Graph*>(graph), out_size, out_degree, out_probability);
}

bool graphAlgorithm_getDensity(pGraph graph, float out_density)
{
    return graph_algorithm::getDensity(static_cast<nk::Graph*>(graph), out_density);
}
