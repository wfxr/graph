//
// Created by wenxuan-zhang on 16-9-18.
//

#pragma once

#include "digraph.h"
#include <queue>
#include <vector>

class BFS {
public:
    BFS(const Digraph &digraph, size_t src) : marked_(digraph.vertex_count()) {
        dfs(digraph, src);
    }

    bool connected(size_t dest) const { return marked_[dest]; }

private:
    void dfs(const Digraph &digraph, size_t src) {
        std::queue<size_t> queue;
        queue.push(src);
        marked_[src] = true;
        while (!queue.empty()) {
            auto v = queue.front();
            queue.pop();
            for (auto w : digraph.adjacent(v))
                if (!marked_[w]) {
                    marked_[w] = true;
                    queue.push(w);
                }
        }
    }
    std::vector<bool> marked_;
};