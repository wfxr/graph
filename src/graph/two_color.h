//
// Created by Wenxuan on 9/17/2016.
//

#pragma once

#include "graph.h"
#include <vector>
#include <stack>

class TwoColor {
public:
    TwoColor(const Graph &graph) : marked_(graph.vertex_count()), color_(graph.vertex_count()) {
        for (size_t v = 0; v < graph.vertex_count(); ++v)
            if (!marked_[v])
                dfs2(graph, v);
    }

    bool two_colorable() { return two_colorable_; }

private:
    void dfs(const Graph &graph, size_t v) {
        marked_[v] = true;
        for (auto w : graph.adjacent(v))
            if (!marked_[w]) {
                marked_[w] = true;
                color_[w] = !color_[v];
                dfs(graph, w);
            } else if (color_[w] == color_[v]) {
                two_colorable_ = false;
                return;
            }
    }

    // 迭代实现
    void dfs2(const Graph &graph, size_t src) {
        std::stack<size_t> stack;
        stack.push(src);
        while (!stack.empty()) {
            auto v = stack.top();
            stack.pop();
            marked_[v] = true;
            for (auto w : graph.adjacent(v))
                if (!marked_[w]) {
                    color_[w] = !color_[v];
                    stack.push(w);
                } else if (color_[w] == color_[v]) {
                    two_colorable_ = false;
                    return;
                }
        }
    }

    std::vector<bool> marked_;
    std::vector<bool> color_;
    bool two_colorable_ = true;
};


