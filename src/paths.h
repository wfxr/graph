//
// Created by Wenxuan on 9/17/2016.
//

#pragma once

#include "graph.h"
#include <vector>

class Paths {
public:
    Paths(const Graph &graph, Graph::VertexType src)
            : src_(src), marked_(graph.vertex_count()), edge_to_(graph.vertex_count()) {
        dfs(graph, src);
    }

    bool connected(Graph::VertexType dest) { return marked_[dest]; }

    std::vector<Graph::VertexType> path_to(Graph::VertexType dest) {
        std::vector<Graph::VertexType> path;
        if (!connected(dest)) return path;

        for (Graph::VertexType x = dest;; x = edge_to_[x]) {
            path.push_back(x);
            if (x == src_) break;
        }

        std::reverse(path.begin(), path.end());
        return path;
    }

private:
    void dfs(const Graph &graph, Graph::SizeType src) {
        marked_[src] = true;
        for (auto w : graph.adjacent(src))
            if (!marked_[w]) {
                edge_to_[w] = src;
                dfs(graph, w);
            }
    }

    Graph::VertexType src_;
    std::vector<bool> marked_;
    std::vector<Graph::SizeType> edge_to_;
};
