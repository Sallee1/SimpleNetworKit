#include <chrono>
#include <future>
#include <iostream>
#include <networkit/auxiliary/Random.hpp>
#include <networkit/centrality/EstimateBetweenness.hpp>
#include <networkit/centrality/DynBetweenness.hpp>
#include <networkit/centrality/CoreDecomposition.hpp>
#include <networkit/generators/BarabasiAlbertGenerator.hpp>
#include <networkit/generators/ErdosRenyiGenerator.hpp>
#include <networkit/graph/Graph.hpp>
#include <networkit/graph/GraphTools.hpp>

#define RUN_INIT std::chrono::steady_clock::time_point begin, end;\
    std::chrono::duration<double, std::milli> elapsed_milliseconds;
#define RUN_BEGIN begin = std::chrono::steady_clock::now();
#define RUN_END end = std::chrono::steady_clock::now();\
    elapsed_milliseconds = end - begin;\
    std::cout << "运行时间: " << elapsed_milliseconds.count() << "ms\n";

namespace nk = NetworKit;

void printWaitInfo(std::chrono::duration<double, std::milli> run_time)
{
    printf("\r计算中，已运行%7.3lf s", run_time.count() / 1000.0);
}

auto test_getERGraph(uint64_t n, float p)
{
    RUN_INIT;
    printf("==========随机网络生成测试开始==========\n");
    printf("随机生成ER随机网络，n = %llu, p = %lf\n", n, p);
    RUN_BEGIN;
    auto graph = nk::ErdosRenyiGenerator(n, p).generate();
    RUN_END;
    printf("==========随机网络生成测试结束==========\n\n");
    return graph;
}

auto test_getBAGraph(uint64_t k, uint64_t n)
{
    RUN_INIT;
    printf("==========无标度网络生成测试开始==========\n");
    printf("随机生成BA无标度网络，k = %llu, n = %llu\n", k, n);
    RUN_BEGIN;
    auto graph = nk::BarabasiAlbertGenerator(k, n).generate();
    RUN_END;
    printf("==========无标度网络生成测试结束==========\n\n");
    return graph;
}

void test_getDegree(const nk::Graph& graph, const std::vector<uint64_t>& test_sample)
{
    RUN_INIT;
    printf("==========节点度数测试开始==========\n");
    std::vector<std::pair<uint64_t, uint64_t>> degree_array;
    degree_array.resize(test_sample.size());
    RUN_BEGIN;
    for (uint64_t i = 0; i < 10; i++)
    {
        uint64_t node_id = test_sample[i];
        auto degree = graph.degree(node_id);
        degree_array[i] = { node_id, degree };
    }
    RUN_END;
    for (auto& degree : degree_array)
    {
        printf("%5llu节点的度数为%5llu\n", degree.first, degree.second);
    }
    printf("==========节点度数测试结束==========\n\n");
}

/**
 * @brief 获取标准化介值中心度的分母系数
 * @param graph 求标准化介值中心度的图
 * @return 系数
*/
uint64_t getBetweenessNormalizeCoefficient(const nk::Graph& graph)
{
    const uint64_t n = graph.numberOfNodes();
    const uint64_t pairs = (n - 2) * (n - 1);
    return pairs;
}

//因为要修改图，所以这里传的不是引用
void test_getBetweeness(nk::Graph graph, const std::vector<uint64_t>& test_sample)
{
    //因为要修改图所以复制一下以免影响到输入
    RUN_INIT;
    printf("==========静态介数中心度测试开始==========\n");
    RUN_BEGIN;
    nk::DynBetweenness betweeness_object(graph);
    std::future<void> calculation_future = std::async(std::launch::async, [&]() {
        betweeness_object.run();
        });
    while (!betweeness_object.hasFinished()) {
        printWaitInfo(std::chrono::steady_clock::now() - begin);
    }
    std::vector<std::pair<uint64_t, double>> betweeness_array;
    betweeness_array.resize(test_sample.size());

    for (uint64_t i = 0; i < 10; i++)
    {
        uint64_t node_id = test_sample[i];
        auto betweeness = betweeness_object.score(node_id);
        //DynBetweenness输出的值不是规格化的，需要转换
        betweeness /= getBetweenessNormalizeCoefficient(graph);
        betweeness_array[i] = { node_id, betweeness };
    }
    RUN_END;
    for (auto& betweeness : betweeness_array)
    {
        printf("%5llu节点的介数中心度为%lf\n", betweeness.first, betweeness.second);
    }
    printf("==========静态介数中心度测试结束==========\n\n");


    printf("==========动态介数中心度测试开始==========\n");
    auto u = Aux::Random::integer(0, graph.numberOfNodes() - 1);
    auto v = Aux::Random::integer(0, graph.numberOfNodes() - 1);
    printf("随机添加从%llu到%llu的边\n", u, v);
    graph.addEdge(u, v);
    RUN_BEGIN;
    calculation_future = std::async(std::launch::async, [&]() {
        betweeness_object.update(nk::GraphEvent(nk::GraphEvent::EDGE_ADDITION, u, v));
        });

    while (!betweeness_object.hasFinished()) {
        printWaitInfo(std::chrono::steady_clock::now() - begin);
    }

    for (uint64_t i = 0; i < 10; i++)
    {
        uint64_t node_id = test_sample[i];
        auto betweeness = betweeness_object.score(node_id);
        //DynBetweenness输出的值不是规格化的，需要转换
        betweeness /= getBetweenessNormalizeCoefficient(graph);
        betweeness_array[i] = { node_id, betweeness };
    }
    RUN_END;
    for (auto& betweeness : betweeness_array)
    {
        printf("%5llu节点的介数中心度为%lf\n", betweeness.first, betweeness.second);
    }
    printf("==========动态介数中心度测试结束==========\n\n");
}

void test_getEstimateBetweeness(const nk::Graph& graph, const std::vector<uint64_t>& test_sample)
{
    RUN_INIT;
    printf("==========近似介数中心度测试开始==========\n");
    RUN_BEGIN;
    nk::EstimateBetweenness betweeness_object(graph, 100, true, true);
    std::future<void> calculation_future = std::async(std::launch::async, [&]() {
        betweeness_object.run();
        });
    while (!betweeness_object.hasFinished()) {
        printWaitInfo(std::chrono::steady_clock::now() - begin);
    }
    std::vector<std::pair<uint64_t, double>> betweeness_array;
    betweeness_array.resize(test_sample.size());

    for (uint64_t i = 0; i < 10; i++)
    {
        uint64_t node_id = test_sample[i];
        auto betweeness = betweeness_object.score(node_id);
        betweeness_array[i] = { node_id, betweeness };
    }
    RUN_END;
    for (auto& betweeness : betweeness_array)
    {
        printf("%5llu节点的近似介数中心度为%lf\n", betweeness.first, betweeness.second);
    }
    printf("==========近似介数中心度测试结束==========\n\n");
}

void test_getKCore(const nk::Graph& graph, const std::vector<uint64_t>& test_sample)
{
    RUN_INIT;
    printf("==========K核值测试开始==========\n");
    RUN_BEGIN;
    nk::CoreDecomposition k_core_obj(graph);
    std::future<void> calculation_future = std::async(std::launch::async, [&]() {
        k_core_obj.run();
        });
    while (!k_core_obj.hasFinished()) {
        printWaitInfo(std::chrono::steady_clock::now() - begin);
    }
    RUN_END;

    std::vector<std::pair<uint64_t, uint64_t>> k_core_array;
    k_core_array.resize(test_sample.size());
    RUN_BEGIN;
    for (uint64_t i = 0; i < 10; i++)
    {
        uint64_t node_id = Aux::Random::integer(0, graph.numberOfNodes() - 1);
        auto k_core = static_cast<uint64_t>(k_core_obj.score(node_id));
        k_core_array[i] = { node_id, k_core };
    }
    RUN_END;
    for (auto& core_decomposition : k_core_array)
    {
        printf("%5llu节点k核值为%llu\n", core_decomposition.first, core_decomposition.second);
    }
    printf("==========K核值测试结束==========\n\n");
}

void test_degreeDistribution(const nk::Graph& graph)
{
    RUN_INIT;
    printf("==========度分布测试开始==========\n");
    RUN_BEGIN;
    //NetworKit没有封装度分布接口，自己实现
    std::map<uint64_t, uint64_t> degree_count;
    for (auto node : graph.nodeRange())
    {
        degree_count[graph.degree(node)]++;
    }
    std::vector<float> degree_distribution;
    degree_distribution.resize(graph.numberOfNodes());
    for (auto& count : degree_count)
    {
        degree_distribution[count.first] = static_cast<float>(count.second) / graph.numberOfNodes();
    }
    RUN_END;

    //绘制直方图，将度分布均分为blocks_count份
    uint64_t blocks_count = 15;
    std::vector<float> histogram(blocks_count, 0);
    for (uint64_t i = 0; i < blocks_count; i++)
    {
        float lower = static_cast<float>(degree_distribution.size()) / (blocks_count)*i;
        float upper = static_cast<float>(degree_distribution.size()) / (blocks_count) * (i + 1);
        for (uint64_t j = std::roundf(lower); j < std::roundf(upper); j++)
        {
            histogram[i] += degree_distribution[j];
        }
    }

    for (uint64_t i = 0; i < blocks_count; i++)
    {
        uint64_t lower = static_cast<float>(degree_distribution.size()) / (blocks_count)*i;
        uint64_t upper = static_cast<float>(degree_distribution.size()) / (blocks_count) * (i + 1);

        printf("%5llu~%5llu ", lower, upper);
        for (uint64_t j = 0; j < histogram[i] * 100; j++)
        {
            putchar('#');
        }
        putchar('\n');
    }
    printf("==========度分布测试结束==========\n\n");
}

void test_networkdensity(const nk::Graph& graph)
{
    RUN_INIT;
    printf("==========网络密度测试开始==========\n");
    RUN_BEGIN;
    float density = nk::GraphTools::density(graph);
    RUN_END;
    printf("网络密度为%lf\n", density);
    printf("==========网络密度测试结束==========\n\n");
}


int main()
{
    system("chcp 65001");
    //测试随机生成ER随机网络
    //auto graph = test_getERGraph(2000, 0.25f);

    //测试随机生成BA无标度网络
    auto graph = test_getBAGraph(250, 2000);

    //获取n个随机数
    uint64_t n = 10;
    std::vector<uint64_t> test_sample(n);
    for (int i = 0; i < n; i++)
    {
        test_sample[i] = Aux::Random::integer(0, graph.numberOfNodes() - 1);
    }
    //测试获取度数
    test_getDegree(graph, test_sample);
    //测试获取介值中心度
    test_getBetweeness(graph, test_sample);
    //测试快速近似介数中心度算法
    test_getEstimateBetweeness(graph, test_sample);

    //测试k核值
    test_getKCore(graph, test_sample);

    //测试度分布
    test_degreeDistribution(graph);
    //测试网络密度
    test_networkdensity(graph);

    printf("==========全部测试结束==========\n\n");
    return 0;
}