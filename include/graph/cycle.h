//
// Created by Wenxuan on 9/17/2016.
//

#pragma once

#include "graph.h"
#include <stack>
#include <tuple>

class Cycle {
public:
    Cycle(const Graph &graph) : marked_(graph.vertex_count()) {
        for (size_t v = 0; v < graph.vertex_count() && has_cycle(); ++v)
            if (!marked_[v]) dfs(graph, v);
    }

    bool has_cycle() const { return has_cycle_; }

private:
    void dfs(const Graph &graph, size_t v, size_t src) {
        marked_[v] = true;
        for (auto w : graph.adjacent(v))
            if (!marked_[w])
                dfs(graph, w, v);
            else if (w != src) {
                has_cycle_ = true;
                return;
            }
    }

    // 迭代版本
    void dfs(const Graph &graph, size_t v) {
        std::stack<std::pair<size_t, size_t>> stack;
        stack.emplace(v, v);
        size_t cur, src;
        while (!stack.empty()) {
            std::tie(cur, src) = stack.top();
            marked_[cur] = true;
            stack.pop();
            for (auto w : graph.adjacent(cur)) {
                if (!marked_[w])
                    stack.emplace(w, cur);
                else if (w != src) {
                    has_cycle_ = true;
                    return;
                }
            }
        }
    }

    std::vector<bool> marked_;
    bool has_cycle_ = false;
};
