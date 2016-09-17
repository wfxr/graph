//
// Created by Wenxuan on 9/15/2016.
//

#pragma once

#include <vector>
#include <exception>
#include <utility>
#include <forward_list>
#include <algorithm>
#include <istream>
#include <string>
#include <numeric>
#include <iterator>
#include <sstream>
#include <fstream>

class Graph {
public:
    using SizeType = std::size_t;
    using VertexType = std::size_t;
    using VertexList = std::forward_list<VertexType>;
    using Edge = std::pair<VertexType, VertexType>;

    Graph(SizeType vetex_count) : graph_(vetex_count), edges_count_(0) {}

    Graph(SizeType vetex_count, const std::vector<Edge> &edges) : Graph(vetex_count) {
        for (const auto &edge : edges)
            addEdge(edge.first, edge.second);
    }

    // 顶点数
    SizeType vertex_count() const { return graph_.size(); }

    // 边数
    SizeType edge_count() const { return edges_count_; }

    // 指定顶点的相邻顶点列表
    const VertexList &adjacent(VertexType i) const { return graph_[i]; }

    // 添加一条边
    void addEdge(VertexType v, VertexType w) {
        graph_[v].push_front(w);
        graph_[w].push_front(v);
        ++edges_count_;
    }

    // 顶点v的度数
    SizeType degree(VertexType v) const {
        return list_size(adjacent(v));
    }

    // 平均度数
    double avg_degree() const {
        return 2.0 * edge_count() / vertex_count();
    }

    // 最大度数
    SizeType max_degree() const {
        SizeType max = 0;
        for (const auto &adj : graph_) {
            auto degree = list_size(adj);
            if (degree > max)
                max = degree;
        }
        return max;
    }

    // 自环的个数
    SizeType selfloops_count() const {
        SizeType count = 0;
        for (SizeType v = 0; v < graph_.size(); ++v)
            for (auto w : adjacent(v))
                if (w == v) ++count;
        return count / 2;
    }

    std::string to_string() const {
        std::ostringstream os;
        os << "vertex count: " << vertex_count() << std::endl
           << "edge count: " << edge_count() << std::endl;
        for (SizeType v = 0; v < graph_.size(); ++v) {
            os << v << ": ";
            for (auto w : adjacent(v))
                os << w << " ";
            os << std::endl;
        }
        return os.str();
    }

private:
    SizeType list_size(const VertexList &list) const {
        SizeType size = 0;
        for (auto it = list.begin(); it != list.end(); ++it)
            ++size;
        return size;
    }

    std::vector<VertexList> graph_;
    SizeType edges_count_;
};

Graph create_graph(std::istream &is) {
    Graph::SizeType vertex_count = 0;
    is >> vertex_count;
    std::vector<Graph::Edge> edges;
    Graph::Edge edge;
    while (is >> edge.first >> edge.second)
        edges.push_back(edge);
    return Graph(vertex_count, edges);
}

Graph create_graph(const std::string &file_name) {
    std::ifstream is("tiny_graph.txt");
    if (!is) throw std::invalid_argument("open file failed.");
    return create_graph(is);
}
