//
// Created by Wenxuan on 9/16/2016.
//

#pragma once

#include "graph.h"
#include <vector>

class DFS {
public:
    DFS(const Graph &graph, size_t source) : marked_(graph.vertex_count()) {
        dfs(graph, source);
    }

    bool connected(size_t v) const {
        return marked_[v];
    }

private:
    void dfs(const Graph &graph, size_t v) {
        marked_[v] = true;
        for (auto w : graph.adjacent(v))
            if (!marked_[w])
                dfs(graph, w);
    }

    std::vector<bool> marked_;
};


