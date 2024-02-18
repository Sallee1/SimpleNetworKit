#pragma once
//本类导出了图操作和图算法的通用接口，基于NetworKit封装
//如果在C++上使用此类，可以使用static_cast<NetworKit::Graph*>(graph)转换void* graph参数以获取实际对象

#ifdef _WIN32  //for win32
#ifdef LIBGRAPHALGORITHM_EXPORTS
#define LIBGRAPHALGORITHM_PORT __declspec(dllexport)
#else
#define LIBGRAPHALGORITHM_PORT __declspec(dllimport)
#endif // LIBGRAPHALGORITHM_EXPORTS
#define LIBGRAPHALGORITHM_CALL __stdcall
#else  // otherwise
#define LIBGRAPHALGORITHM_PORT
#define LIBGRAPHALGORITHM_CALL
#endif  // _WIN32
#define LIBGRAPHALGORITHM_API LIBGRAPHALGORITHM_PORT LIBGRAPHALGORITHM_CALL

typedef void* pGraph;
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
    /**
     * @brief 创建图
     * @param isDirected 是否是有向图
     * @return 空白图对象的指针
    */
    pGraph LIBGRAPHALGORITHM_API graph_create(bool isDirected);

    /**
     * @brief 拷贝构造图
     * @param graph 图对象指针
     * @return 图对象副本的指针
    */
    pGraph LIBGRAPHALGORITHM_API graph_clone(pGraph graph);

    /**
     * @brief 构造子图
     * @param graph 图对象指针
     * @param size 子图的节点数
     * @param nodeIds 子图的节点id
     * @return 子图对象的指针
    */
    pGraph LIBGRAPHALGORITHM_API graph_subGraph(pGraph graph, int size, int* nodeIds);

    /**
     * @brief 获取图是否是有向的
     * @param graph 图对象指针
    */
    bool LIBGRAPHALGORITHM_API graph_isDirected(pGraph graph);

    /**
     * @brief 获取图的节点数
     * @param graph 图对象指针
     * @return 节点数
    */
    int LIBGRAPHALGORITHM_API graph_getNodeCount(pGraph graph);

    /**
     * @brief 获取图的所有节点
     * @param graph 图对象指针
     * @return 节点数
    */
    int LIBGRAPHALGORITHM_API graph_getAllNodes(pGraph graph, int* nodeIds);

    /**
     * @brief 获取图的边数
     * @param graph 图对象指针
     * @return 图的边数
    */
    int LIBGRAPHALGORITHM_API graph_getEdgeCount(pGraph graph);

    /**
     * @brief 获取图的所有边
     * @param graph 图对象指针
     * @return 图的边数
    */
    int LIBGRAPHALGORITHM_API graph_getAllEdges(pGraph graph, int* edgeFrom, int* edgeTo);

    /**
     * @brief 设定边权重
     * @param graph 图对象指针
     * @param edgeFrom 边的起点
     * @param edgeTo 边的终点
     * @param widget 边的权重
     * @return 是否设置成功，边不存在，返回false
    */
    bool LIBGRAPHALGORITHM_API graph_setEdgeWidget(pGraph graph, int edgeFrom, int edgeTo, int widget);

    /**
     * @brief 在图中添加一个新节点
     * @param graph 图对象指针
     * @param nodeId 节点id，如果节点已经存在，返回false
    */
    bool LIBGRAPHALGORITHM_API graph_addNode(pGraph graph, int nodeId);

    /**
     * @brief 在图中删除节点
     * @param graph 图对象指针
     * @return 是否删除成功，如果节点不存在，返回false
    */
    bool LIBGRAPHALGORITHM_API graph_removeNode(pGraph graph, int nodeId);

    /**
     * @brief 在图中添加一个新边
     * @paran graph 图对象指针
     * @param edgeFrom 边的起点
     * @param edgeTo 边的终点
     * @return 是否添加成功，如果边已经存在，返回false
     */
    bool LIBGRAPHALGORITHM_API graph_addEdge(pGraph graph, int edgeFrom, int edgeTo);

    /**
     * @brief 在图中删除边
     * @param graph 图对象指针
     * @param edgeFrom 边的起点
     * @param edgeTo 边的终点
     * @return 是否删除成功，如果边不存在，返回false
     */
    bool LIBGRAPHALGORITHM_API graph_removeEdge(pGraph graph, int edgeFrom, int edgeTo);

    /**
     * @brief 销毁图
     * @param graph 图对象指针
     * @return 是否销毁成功
     */
    bool LIBGRAPHALGORITHM_API graph_destroy(pGraph graph);

    /**
     * @brief 获取图中节点的度
     * @param graph 图对象指针
     * @param node 节点
     * @param degree 节点的度
     * @return 是否获取成功，如果节点不存在，返回false
    */
    bool LIBGRAPHALGORITHM_API graphAlgorithm_getDegree(pGraph graph, int node, int* out_degree);

    /**
     * @brief 获取图中的节点介数
     * @param graph 图对象指针
     * @param node 节点
     * @param out_betweenness 节点介数
     * @return 是否获取成功，如果节点不存在，返回false
    */
    float LIBGRAPHALGORITHM_API graphAlgorithm_getBetweenness(pGraph graph, int node, float* out_betweenness);

    /**
     * @brief 获取图中节点的K核值
     * @param graph 图对象指针
     * @param node 节点
     * @param out_KCore 节点的K核
     * @return 是否获取成功，如果节点不存在，返回false
    */
    int LIBGRAPHALGORITHM_API graphAlgorithm_getKCore(pGraph graph, int node, int* out_KCore);

    /**
     * @brief 获取图中节点的度分布
     * @param graph 图对象指针
     * @param out_size 概率分布数组的长度
     * @param out_degree 非0概率的度值
     * @param out_probability 度对应的概率
     * @return 是否获取成功
    */
    bool LIBGRAPHALGORITHM_API graphAlgorithm_getDegreeDistribution(pGraph graph, int* out_size, int* out_degree, float out_probability);

    /**
     * @brief 获取图的网络密度
     * @param graph 图对象指针
     * @param out_density 图的网络密度
     * @return 是否获取成功
    */
    bool LIBGRAPHALGORITHM_API graphAlgorithm_getDensity(pGraph graph, float out_density);

    //异步调用方法，后面再写

#ifdef __cplusplus
}
#endif // __cplusplus