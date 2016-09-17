//
// Created by Wenxuan on 9/17/2016.
//

#pragma once

#include "graph.h"
#include <queue>
#include <algorithm>
#include <vector>

class BFSPaths {
public:
    BFSPaths(const Graph &graph, size_t src)
            : src_(src), marked_(graph.vertex_count()), edge_to_(graph.vertex_count()) {
        bfs(graph, src);
    }

    bool connected(size_t dest) const { return marked_[dest]; }

    std::vector<size_t> path_to(size_t dest) const {
        std::vector<size_t> path;
        if (!connected(dest)) return path;

        for (auto x = dest;; x = edge_to_[x]) {
            path.push_back(x);
            if (x == src_) break;
        }

        std::reverse(path.begin(), path.end());
        return path;
    }

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
                    edge_to_[w] = v;
                    marked_[w] = true;
                    queue.push(w);
                }
        }
    }

    size_t src_;
    std::vector<bool> marked_;
    std::vector<size_t> edge_to_;
};


