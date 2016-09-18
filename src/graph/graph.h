//
// Created by Wenxuan on 9/15/2016.
//

#pragma once

#include <algorithm>
#include <exception>
#include <forward_list>
#include <fstream>
#include <iostream>
#include <istream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using size_t = std::size_t;

class Graph {
public:
    using AdjacentList = std::forward_list<size_t>;
    using Edge = std::pair<size_t, size_t>;

    Graph(size_t vertex_count = 0) : adjacent_lists_(vertex_count), edges_count_(0) {}

    Graph(size_t vertex_count, const std::vector<Edge> &edges)
        : Graph(vertex_count) {
        for (const auto &edge : edges)
            add_edge(edge.first, edge.second);
    }

    void assign(size_t vertex_count, const std::vector<Edge> &edges) {
        assign(vertex_count);
        for (const auto &edge : edges)
            add_edge(edge.first, edge.second);
    }

    void assign(size_t vertex_count) {
        edges_count_ = 0;
        adjacent_lists_.assign(vertex_count, AdjacentList());
    }

    // 顶点数
    size_t vertex_count() const { return adjacent_lists_.size(); }

    // 边数
    size_t edge_count() const { return edges_count_; }

    // 指定顶点的相邻顶点列表
    const AdjacentList &adjacent(size_t v) const { return adjacent_lists_[v]; }

    // 添加一条边
    void add_edge(size_t v, size_t w) {
        adjacent_lists_[v].push_front(w);
        adjacent_lists_[w].push_front(v);
        ++edges_count_;
    }

    // 顶点v的度数
    size_t degree(size_t v) const { return list_size(adjacent(v)); }

    // 平均度数
    double avg_degree() const { return 2.0 * edge_count() / vertex_count(); }

    // 最大度数
    size_t max_degree() const {
        size_t max = 0;
        for (const auto &adj : adjacent_lists_) {
            auto degree = list_size(adj);
            if (degree > max) max = degree;
        }
        return max;
    }

    // 自环的个数
    size_t selfloops_count() const {
        size_t count = 0;
        for (size_t v = 0; v < vertex_count(); ++v)
            for (auto w : adjacent(v))
                if (w == v) ++count;
        return count / 2;
    }

    std::string to_string() const {
        std::ostringstream os;
        os << "vertex count: " << vertex_count() << std::endl
           << "edge count: " << edge_count() << std::endl;
        for (size_t v = 0; v < vertex_count(); ++v) {
            os << v << ": ";
            for (auto w : adjacent(v))
                os << w << " ";
            os << std::endl;
        }
        return os.str();
    }

private:
    size_t list_size(const AdjacentList &list) const {
        size_t size = 0;
        for (auto it = list.begin(); it != list.end(); ++it)
            ++size;
        return size;
    }

    std::vector<AdjacentList> adjacent_lists_;
    size_t edges_count_;
};

Graph create_graph(std::istream &is) {
    if (!is) {
        std::cerr << "bad istream" << std::endl;
        return Graph(0);
    }
    size_t vertex_count = 0;
    is >> vertex_count;
    std::vector<Graph::Edge> edges;
    Graph::Edge edge;
    while (is >> edge.first >> edge.second)
        edges.push_back(edge);
    return Graph(vertex_count, edges);
}

Graph create_graph(const std::string &file_name) {
    std::ifstream is(file_name);
    return create_graph(is);
}
