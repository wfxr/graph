//
// Created by wenxuan-zhang on 16-9-19.
//

#pragma once

#include "digraph.h"
#include <vector>

class DepthFirstOrder {
public:
    DepthFirstOrder(const Digraph &digraph) : marked_(digraph.vertex_count()) {
        pre_.reserve(digraph.vertex_count());
        post_.reserve(digraph.vertex_count());
        for (size_t v = 0; v < digraph.vertex_count(); ++v)
            if (!marked_[v]) dfs(digraph, v);
        reverse_post_.assign(post_.rbegin(), post_.rend());
    }

    const std::vector<size_t> &pre_order() const { return pre_; }
    const std::vector<size_t> &post_order() const { return post_; }
    const std::vector<size_t> &reverse_post_order() const { return reverse_post_; }

private:
    void dfs(const Digraph &digraph, size_t v) {
        marked_[v] = true;
        pre_.push_back(v);
        for (auto w : digraph.adjacent(v))
            if (!marked_[w]) dfs(digraph, w);
        post_.push_back(v);
    }

    std::vector<bool> marked_;
    std::vector<size_t> pre_;               // 前序排列
    std::vector<size_t> post_;              // 后续排列
    std::vector<size_t> reverse_post_;      // 逆后序排列
};