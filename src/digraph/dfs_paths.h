//
// Created by wenxuan-zhang on 16-9-18.
//

#pragma once

#include "digraph.h"
#include <algorithm>
#include <vector>

class DFSPaths {
public:
    DFSPaths(const Digraph &digraph, size_t src)
        : src_(src), marked_(digraph.vertex_count()),
          path_to_(digraph.vertex_count()) {
        dfs(digraph, src);
    }

    bool connected(size_t dest) const { return marked_.at(dest); }

    std::vector<size_t> path_to(size_t dest) const {
        std::vector<size_t> path;
        if (!connected(dest)) return path;
        for (size_t x = dest;; x = path_to_[x]) {
            path.push_back(x);
            if (x == src_) break;
        }
        std::reverse(path.begin(), path.end());
        return path;
    }

private:
    void dfs(const Digraph &digraph, size_t v) {
        marked_[v] = true;
        for (auto w : digraph.adjacent(v))
            if (!marked_[w]) {
                path_to_[w] = v;
                dfs(digraph, w);
            }
    }

    size_t src_;
    std::vector<bool> marked_;
    std::vector<size_t> path_to_;
};