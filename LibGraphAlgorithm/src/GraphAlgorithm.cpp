#include "GraphAlgorithm.h"
#include "GraphAlgorithmImpl.h"
#include <networkit/graph/Graph.hpp>

namespace nk = NetworKit;

pGraph graph_create(bool is_directed, bool is_weighted)
{
    return graph_object::create(is_directed, is_weighted);
}

pGraph graph_clone(pGraph graph)
{
    return graph_object::clone(static_cast<nk::Graph*>(graph));
}

pGraph graph_subGraph(pGraph graph, uint64_t size, uint64_t* node_ids)
{
    return graph_object::subGraph(static_cast<nk::Graph*>(graph), size, node_ids);
}

bool graph_isDirected(pGraph graph)
{
    return graph_object::isDirected(static_cast<nk::Graph*>(graph));
}

bool graph_isWeighted(pGraph graph)
{
    return graph_object::isWeighted(static_cast<nk::Graph*>(graph));
}

uint64_t graph_getNodeCount(pGraph graph)
{
    return graph_object::getNodeCount(static_cast<nk::Graph*>(graph));
}

uint64_t graph_getAllNodes(pGraph graph, uint64_t* node_ids)
{
    return graph_object::getAllNodes(static_cast<nk::Graph*>(graph), node_ids);
}

uint64_t graph_getEdgeCount(pGraph graph)
{
    return graph_object::getEdgeCount(static_cast<nk::Graph*>(graph));
}

uint64_t graph_getAllEdges(pGraph graph, uint64_t* edge_from, uint64_t* edge_to)
{
    return graph_object::getAllEdges(static_cast<nk::Graph*>(graph), edge_from, edge_to);
}

bool graph_setEdgeWidget(pGraph graph, uint64_t edge_from, uint64_t edge_to, float widget)
{
    return graph_object::setEdgeWidget(static_cast<nk::Graph*>(graph), edge_from, edge_to, widget);
}

bool graph_addNode(pGraph graph, uint64_t node_id)
{
    return graph_object::addNode(static_cast<nk::Graph*>(graph), node_id);
}

bool graph_removeNode(pGraph graph, uint64_t node_id)
{
    return graph_object::removeNode(static_cast<nk::Graph*>(graph), node_id);
}

bool graph_addEdge(pGraph graph, uint64_t edge_from, uint64_t edge_to)
{
    return graph_object::addEdge(static_cast<nk::Graph*>(graph), edge_from, edge_to);
}

bool graph_removeEdge(pGraph graph, uint64_t edge_from, uint64_t edge_to)
{
    return graph_object::removeEdge(static_cast<nk::Graph*>(graph), edge_from, edge_to);
}

bool graph_destroy(pGraph graph)
{
    return graph_object::destroy(static_cast<nk::Graph*>(graph));
}

bool graphAlgorithm_getDegree(pGraph graph, uint64_t node, uint64_t* out_degree)
{
    return graph_algorithm::getDegree(static_cast<nk::Graph*>(graph), node, out_degree);
}

float graphAlgorithm_getBetweenness(pGraph graph, uint64_t node, float* out_betweenness)
{
    return graph_algorithm::getBetweenness(static_cast<nk::Graph*>(graph), node, out_betweenness);
}

bool graphAlgorithm_getKCore(pGraph graph, uint64_t node, uint64_t* out_k_core)
{
    return graph_algorithm::getKCore(static_cast<nk::Graph*>(graph), node, out_k_core);
}

bool graphAlgorithm_getDegreeDistribution(pGraph graph, uint64_t* out_size, uint64_t* out_degree, float out_probability)
{
    return graph_algorithm::getDegreeDistribution(static_cast<nk::Graph*>(graph), out_size, out_degree, out_probability);
}

bool graphAlgorithm_getDensity(pGraph graph, float out_density)
{
    return graph_algorithm::getDensity(static_cast<nk::Graph*>(graph), out_density);
}
