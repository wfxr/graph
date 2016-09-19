//
// Created by wenxuan-zhang on 16-9-19.
//

#pragma once

#include "digraph.h"
#include <algorithm>
#include <stack>
#include <vector>

class Cycle {
public:
    Cycle(const Digraph &digraph)
        : marked_(digraph.vertex_count()), on_path_(digraph.vertex_count()),
          path_to_(digraph.vertex_count()) {
        for (size_t v = 0; v < digraph.vertex_count() && !has_cycle(); ++v)
            if (!marked_[v]) dfs(digraph, v);
    }

    bool has_cycle() const { return !cycle_.empty(); }

    const std::vector<size_t> &cycle() const { return cycle_; }

private:
    void dfs(const Digraph &digraph, size_t v) {
        on_path_[v] = true;
        marked_[v] = true;
        for (auto w : digraph.adjacent(v)) {
            if (has_cycle()) return;
            if (!marked_[w]) {
                path_to_[w] = v;
                dfs(digraph, w);
            } else if (on_path_[w]) { // find cycle
                cycle_.push_back(w);
                for (auto x = v;; x = path_to_[x]) {
                    cycle_.push_back(x);
                    if (x == w) break;
                }
                std::reverse(cycle_.begin(), cycle_.end());
            }
        }
        on_path_[v] = false;
    }

    std::vector<bool> marked_;
    std::vector<bool> on_path_;
    std::vector<size_t> cycle_;
    std::vector<size_t> path_to_;
};