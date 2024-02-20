#pragma once
#include <networkit/graph/Graph.hpp>
#include <networkit/graph/GraphTools.hpp>

//Graph的包装类，并提供C形式的访问接口
class GraphCInterface {
private:
    std::unique_ptr<NetworKit::Graph> m_graph;
    //所有的节点
    std::unordered_set<NetworKit::node> m_nodeIdMap;
    //节点介数中心度
    std::unordered_map<NetworKit::node, float> m_betweennessMap;
    //节点K-Core中心度
    std::unordered_map<NetworKit::node, uint64_t> m_KCoreMap;

    //外部接口的中间容器，用于存储和管理接口返回的数据
    //线性表表示的Id
    std::vector<uint64_t> m_nodeIdArray;
    //线性表表示的边起点
    std::vector<uint64_t> m_edgeFromArray;
    //线性表表示的边终点
    std::vector<uint64_t> m_edgeToArray;
    //线性表表示的介数中心度，与nodeIdArray对应
    std::vector<float> m_betweennessArray;
    //线性表表示的K-Core中心度，与nodeIdArray对应
    std::vector<uint64_t> m_KCoreArray;
    //线性表表示的度分布，从0~maxDegree
    std::vector<float> m_degreeProbabilityArray;

public:
    GraphCInterface();;

    GraphCInterface(NetworKit::Graph* graph);;

    ~GraphCInterface() = default;

    /**
     * @brief 获取本对象管理的NetworKit中的原始Graph对象，可在C++中使用
     * @return NetworKit中的Graph
    */
    NetworKit::Graph* getNetworKitGraph();

    /**
     * @brief 获取图的子图，c接口
     * @param size 子图的节点数
     * @param node_ids 子图的节点id
     * @return 子图对象指针
    */
    GraphCInterface* subGraph(uint64_t size, uint64_t* node_ids);

    /**
     * @brief 获取图是否是有向的
     * @return 是否是有向的
    */
    bool isDirected();

    /**
     * @brief 获取图是否是带权重的
     * @return 是否是带权重的
    */
    bool isWeighted();

    /**
     * @brief 获取图的节点数
     * @return 节点个数
    */
    uint64_t getNodeCount();

    /**
     * @brief 获取图的所有节点，c接口
     * @param out_node_ids 指向节点id数组的指针
     * @return 节点个数
    */
    uint64_t getAllNodes(uint64_t* out_node_ids);

    /**
     * @brief 获取图的边数
     * @return 图的边数
    */
    uint64_t getEdgeCount();

    /**
     * @brief 获取图的所有边，c接口
     * @param out_edges_from 指向边起点数组的指针
     * @param out_edges_to 指向边终点数组的指针
     * @return 图的边数
    */
    uint64_t getAllEdges(uint64_t* out_edges_from, uint64_t* out_edges_to);

    /**
     * @brief 节点是否存在
     * @param node_id 节点id
     * @return 是否存在
    */
    bool hasNode(uint64_t node_id);

    /**
     * @brief 边是否存在
     * @param edge_from 边的起点
     * @param edge_to 边的终点
     * @return 是否存在
    */
    bool hasEdge(uint64_t edge_from, uint64_t edge_to);

    /**
     * @brief 获取边权重
     * @param edge_from 边起点
     * @param edge_to 边终点
     * @param out_widget 边权重
     * @return 如果成功返回true，无权图或边不存在返回false
    */
    bool getEdgeWidget(uint64_t edge_from, uint64_t edge_to, float* out_widget);

    /**
     * @brief 设置边的权重
     * @param edge_from 边起点
     * @param edge_to 边终点
     * @param widget 权重
     * @return 设置成功返回true，图是无权图或者边不存在返回false
    */
    bool setEdgeWidget(uint64_t edge_from, uint64_t edge_to, float widget);

    /**
     * @brief 添加新的节点
     * @return 新添加的节点id
    */
    uint64_t addNode();

    /**
     * @brief 添加多个新节点
     * @param num 节点数量
    */
    void addNodes(uint64_t num);

    /**
     * @brief 删除节点
     * @param nodeId 节点id
     * @return 删除成功返回True，如果节点不存在返回false
    */
    bool removeNode(uint64_t nodeId);

    /**
     * @brief 删除多个节点，c接口
     * @param size node_ids数组长度
     * @param node_ids node_ids数组指针
     * @return 删除成功返回True，有不存在的节点返回False
    */
    bool removeNodes(uint64_t size, uint64_t* node_ids);

    /**
     * @brief 添加新的边
     * @param edge_from 边起点
     * @param edge_to 边终点
     * @return 添加成功返回True，如果节点不存在，或者边已经存在返回false
    */
    bool addEdge(uint64_t edge_from, uint64_t edge_to);

    /**
     * @brief 添加多条新的边，c接口
     * @param size 边数量
     * @param edge_from 指向边起点数组的指针
     * @param edge_to 指向边终点数组的指针
     * @return 添加成功返回True，有节点不存在或者边已经存在返回False
    */
    bool addEdges(uint64_t size, uint64_t* edge_from, uint64_t* edge_to);

    /**
     * @brief 删除边
     * @param edge_from 边起点
     * @param edge_to 边终点
     * @return 删除成功返回True，如果节点不存在，或者边不存在返回false
    */
    bool removeEdge(uint64_t edge_from, uint64_t edge_to);

    /**
     * @brief 删除多条边，c接口
     * @param size 边数量
     * @param edge_from 指向边起点数组的指针
     * @param edge_to 指向边终点数组的指针
     * @return 删除成功返回True，有节点不存在或者边不存在返回False
    */
    bool removeEdges(uint64_t size, uint64_t* edge_from, uint64_t* edge_to);
};