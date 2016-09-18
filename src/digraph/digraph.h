//
// Created by wenxuan-zhang on 16-9-18.
//

#pragma once

#include <forward_list>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using size_t = std::size_t;

class Digraph {
public:
    using Edge = std::pair<size_t, size_t>;
    using AdjacentList = std::forward_list<size_t>;
    using string = std::string;
    Digraph(size_t vertex_count = 0) : adjacent_lists_(vertex_count) {}
    Digraph(size_t vertex_count, std::vector<Edge> edges)
        : Digraph(vertex_count) {
        for (const auto &edge : edges)
            add_edge(edge.first, edge.second);
    }

    size_t vertex_count() const { return adjacent_lists_.size(); }

    size_t edges_count() const { return edges_count_; }

    const AdjacentList &adjacent(size_t vertex) const {
        return adjacent_lists_.at(vertex);
    }

    Digraph reverse() const {
        Digraph ret{vertex_count()};
        for (size_t v = 0; v < vertex_count(); ++v)
            for (auto w : adjacent(v))
                ret.add_edge(w, v);
        return ret;
    }

    string to_string() const {
        std::ostringstream os;
        os << "vertex count: " << vertex_count() << '\n'
           << "edges count: " << edges_count() << '\n';
        for (size_t v = 0; v < vertex_count(); ++v) {
            os << v << ": ";
            for (auto w : adjacent(v))
                os << w << " ";
            os << '\n';
        }
        return os.str();
    }

private:
    void add_edge(size_t src, size_t dest) {
        adjacent_lists_[src].push_front(dest);
        ++edges_count_;
    }

    size_t edges_count_ = 0;
    std::vector<AdjacentList> adjacent_lists_;
};

Digraph create_graph(std::istream &is) {
    if (!is) {
        std::cerr << "bad istream" << std::endl;
        return Digraph(0);
    }
    size_t vertex_count = 0;
    is >> vertex_count;
    std::vector<Digraph::Edge> edges;
    Digraph::Edge edge;
    while (is >> edge.first >> edge.second)
        edges.push_back(edge);
    return Digraph(vertex_count, edges);
}

Digraph create_graph(const std::string &file_name) {
    std::ifstream is(file_name);
    return create_graph(is);
}
