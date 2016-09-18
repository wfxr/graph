//
// Created by wenxuan-zhang on 16-9-18.
//

#pragma once

#include "digraph.h"
#include <initializer_list>

class DFS {
public:
    DFS(const Digraph &digraph, size_t src) : marked_(digraph.vertex_count()) {
        dfs(digraph, src);
    }

    DFS(const Digraph &digraph, const std::vector<size_t> &srcs)
        : marked_(digraph.vertex_count()) {
        for (auto src : srcs)
            if (!marked_[src]) dfs(digraph, src);
    }

    bool connected(size_t dest) const { return marked_.at(dest); }

private:
    void dfs(const Digraph &digraph, size_t src) {
        marked_[src] = true;
        for (auto w : digraph.adjacent(src))
            if (!marked_[w]) dfs(digraph, w);
    }
    std::vector<bool> marked_;
};