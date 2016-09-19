//
// Created by Wenxuan on 9/17/2016.
//

#pragma once

#include "graph.h"
#include <vector>
#include <queue>

class BFS {
public:
    BFS(const Graph &graph, size_t src) : marked_(graph.vertex_count()) {
        bfs(graph, src);
    }

    bool connected(size_t dest) const { return marked_[dest]; }

private:
    void bfs(const Graph &graph, size_t src) {
        std::queue<size_t> queue;
        queue.push(src);
        marked_[src] = true;
        while (!queue.empty()) {
            auto v = queue.front();
            queue.pop();
            for (auto w : graph.adjacent(v))
                if (!marked_[w]) {
                    queue.push(w);
                    marked_[v] = true;
                }
        }
    }

    std::vector<bool> marked_;
};


