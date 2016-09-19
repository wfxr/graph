//
// Created by Wenxuan on 9/17/2016.
//

#pragma once

#include "graph.h"
#include <vector>

class DFSPaths {
public:
    DFSPaths(const Graph &graph, size_t src)
            : src_(src), marked_(graph.vertex_count()), edge_to_(graph.vertex_count()) {
        dfs(graph, src);
    }

    bool connected(size_t dest) const { return marked_[dest]; }

    std::vector<size_t> path_to(size_t dest) const{
        std::vector<size_t> path;
        if (!connected(dest)) return path;

        for (size_t x = dest;; x = edge_to_[x]) {
            path.push_back(x);
            if (x == src_) break;
        }

        std::reverse(path.begin(), path.end());
        return path;
    }

private:
    void dfs(const Graph &graph, size_t src) {
        marked_[src] = true;
        for (auto w : graph.adjacent(src))
            if (!marked_[w]) {
                edge_to_[w] = src;
                dfs(graph, w);
            }
    }

    size_t src_;
    std::vector<bool> marked_;
    std::vector<size_t> edge_to_;
};
