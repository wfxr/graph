//
// Created by Wenxuan on 9/17/2016.
//

#pragma once

#include "graph.h"
#include <vector>

class ConnectedComponent {
public:
    ConnectedComponent(const Graph &graph)
            : count_(0), marked_(graph.vertex_count()), id_(graph.vertex_count()) {
        for (size_t v = 0; v < graph.vertex_count(); ++v)
            if (!marked_[v]) {
                dfs(graph, v);
                ++count_;
            }
    }

    bool connected(size_t v, size_t w) const { return id_of(v) == id_of(w); }

    size_t count() const { return count_; }

    size_t id_of(size_t v) const { return id_[v]; }

    std::vector<size_t> component(size_t id) const {
        std::vector<size_t> ret;
        for (size_t v = 0; v < id_.size(); ++v)
            if (id_of(v) == id)
                ret.push_back(v);
        return ret;
    }

    std::vector<std::vector<size_t>> components() const {
        std::vector<std::vector<size_t>> ret(count());
        for (size_t v = 0; v < id_.size(); ++v)
            ret[id_of(v)].push_back(v);
        return ret;
    }

private:
    void dfs(const Graph &graph, size_t src) {
        marked_[src] = true;
        id_[src] = count_;
        for (auto w : graph.adjacent(src))
            if (!marked_[w]) dfs(graph, w);
    }

    size_t count_;
    std::vector<bool> marked_;
    std::vector<size_t> id_;
};


