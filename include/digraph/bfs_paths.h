//
// Created by wenxuan-zhang on 16-9-19.
//

#pragma once

#include "digraph.h"
#include <algorithm>
#include <queue>
#include <vector>

class BFSPaths {
public:
    BFSPaths(const Digraph &digraph, size_t src)
        : src_(src), marked_(digraph.vertex_count()), path_to_(digraph.vertex_count()) {
        bfs(digraph, src);
    }

    bool connected(size_t dest) const { return marked_[dest]; }

    std::vector<size_t> path_to(size_t dest) const {
        std::vector<size_t> path;
        if (!connected(dest)) return path;
        for (auto x = dest;; x = path_to_[x]) {
            path.push_back(x);
            if (x == src_) break;
        }
        std::reverse(path.begin(), path.end());
        return path;
    }

private:
    void bfs(const Digraph &digraph, size_t src) {
        std::queue<size_t> queue;
        queue.push(src);
        marked_[src] = true;
        while (!queue.empty()) {
            auto v = queue.front();
            queue.pop();
            for (auto w : digraph.adjacent(v))
                if (!marked_[w]) {
                    marked_[w] = true;
                    path_to_[w] = v;
                    queue.push(w);
                }
        }
    }

    size_t src_;
    std::vector<bool> marked_;
    std::vector<size_t> path_to_;
};