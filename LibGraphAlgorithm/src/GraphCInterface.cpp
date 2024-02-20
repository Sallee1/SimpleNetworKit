#include "GraphCInterface.h"

GraphCInterface::GraphCInterface()
{
    m_graph.reset(new NetworKit::Graph);
}

GraphCInterface::GraphCInterface(NetworKit::Graph* graph)
{
    m_graph.reset(graph);
}

NetworKit::Graph* GraphCInterface::getNetworKitGraph()
{
    return m_graph.get();
}

GraphCInterface* GraphCInterface::subGraph(uint64_t size, uint64_t* node_ids) {
    std::unordered_set<NetworKit::node> nodes;
    for (uint64_t i = 0; i < size; i++)
    {
        nodes.emplace(NetworKit::node(node_ids[i]));
    }
    return new GraphCInterface(new NetworKit::Graph(NetworKit::GraphTools::subgraphFromNodes(*m_graph, nodes)));
}

bool GraphCInterface::isDirected()
{
    return m_graph->isDirected();
}

bool GraphCInterface::isWeighted()
{
    return m_graph->isWeighted();
}

uint64_t GraphCInterface::getNodeCount()
{
    return m_graph->numberOfNodes();
}

uint64_t GraphCInterface::getAllNodes(uint64_t* out_node_ids)
{
    m_nodeIdArray.clear();
    m_nodeIdArray.resize(m_graph->numberOfNodes());

    int i = 0;
    for (auto node : m_graph->nodeRange())
    {
        m_nodeIdArray[i] = node;
        i++;
    }
    out_node_ids = m_nodeIdArray.data();
    return m_graph->numberOfNodes();
}

uint64_t GraphCInterface::getEdgeCount()
{
    return m_graph->numberOfEdges();
}

uint64_t GraphCInterface::getAllEdges(uint64_t* out_edges_from, uint64_t* out_edges_to)
{
    m_edgeFromArray.clear();
    m_edgeToArray.clear();
    m_edgeFromArray.resize(m_graph->numberOfEdges());
    m_edgeToArray.resize(m_graph->numberOfEdges());

    int i = 0;
    for (auto edge : m_graph->edgeRange())
    {
        m_edgeFromArray[i] = edge.u;
        m_edgeToArray[i] = edge.v;
        i++;
    }

    out_edges_from = m_edgeFromArray.data();
    out_edges_to = m_edgeToArray.data();
    return m_graph->numberOfEdges();
}

bool GraphCInterface::hasNode(uint64_t node_id)
{
    return m_graph->hasNode(node_id);
}

bool GraphCInterface::hasEdge(uint64_t edge_from, uint64_t edge_to)
{
    return m_graph->hasEdge(edge_from, edge_to);
}

bool GraphCInterface::getEdgeWidget(uint64_t edge_from, uint64_t edge_to, float* out_widget)
{
    if (!m_graph->isWeighted()) return false;
    if (!m_graph->hasEdge(edge_from, edge_to)) return false;
    *out_widget = m_graph->weight(edge_from, edge_to);
    return true;
}

bool GraphCInterface::setEdgeWidget(uint64_t edge_from, uint64_t edge_to, float widget)
{
    if (!m_graph->isWeighted()) return false;
    if (!m_graph->hasEdge(edge_from, edge_to)) return false;
    m_graph->setWeight(edge_from, edge_to, widget);
    return true;
}

uint64_t GraphCInterface::addNode()
{
    return m_graph->addNode();
}

void GraphCInterface::addNodes(uint64_t num)
{
    m_graph->addNodes(num);
}

bool GraphCInterface::removeNode(uint64_t nodeId)
{
    if (!m_graph->hasNode(nodeId))return false;
    m_graph->removeNode(nodeId);
    return true;
}

bool GraphCInterface::removeNodes(uint64_t size, uint64_t* node_ids)
{
    for (int i = 0; i < size; i++)
    {
        if (!m_graph->hasNode(node_ids[i]))return false;
    }

    for (int i = 0; i < size; i++)
    {
        m_graph->removeNode(node_ids[i]);
    }
}

bool GraphCInterface::addEdge(uint64_t edge_from, uint64_t edge_to)
{
    if (!m_graph->hasNode(edge_from) || !m_graph->hasNode(edge_to)) return false;
    if (m_graph->hasEdge(edge_from, edge_to))return false;
    m_graph->addEdge(edge_from, edge_to);
    return true;
}

bool GraphCInterface::addEdges(uint64_t size, uint64_t* edge_from, uint64_t* edge_to)
{
    for (int i = 0; i < size; i++)
    {
        if (!m_graph->hasNode(edge_from[i]) || !m_graph->hasNode(edge_to[i])) return false;
        if (m_graph->hasEdge(edge_from[i], edge_to[i]))return false;
    }
    for (int i = 0; i < size; i++)
    {
        m_graph->addEdge(edge_from[i], edge_to[i]);
    }
}

bool GraphCInterface::removeEdge(uint64_t edge_from, uint64_t edge_to)
{
    if (!m_graph->hasEdge(edge_from, edge_to))return false;
    m_graph->removeEdge(edge_from, edge_to);
    return true;
}

bool GraphCInterface::removeEdges(uint64_t size, uint64_t* edge_from, uint64_t* edge_to)
{
    for (int i = 0; i < size; i++)
    {
        if (!m_graph->hasEdge(edge_from[i], edge_to[i]))return false;
    }
    for (int i = 0; i < size; i++)
    {
        m_graph->removeEdge(edge_from[i], edge_to[i]);
    }
}
