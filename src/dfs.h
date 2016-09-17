//
// Created by Wenxuan on 9/16/2016.
//

#pragma once

#include "graph.h"
#include <vector>

class DFS {
public:
    DFS(const Graph &graph, Graph::VertexType source) : marked_(graph.vertex_count()) {
        dfs(graph, source);
    }

    bool connected(Graph::VertexType v) const {
        return marked_[v];
    }

    auto count() const { return count_; }

private:
    void dfs(const Graph &graph, Graph::VertexType v) {
        marked_[v] = true;
        ++count_;
        for (auto w : graph.adjacent(v))
            if (!marked_[w])
                dfs(graph, w);
    }

    std::vector<bool> marked_;
    size_t count_ = 0;
};


