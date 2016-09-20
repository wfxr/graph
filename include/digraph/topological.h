#pragma once

#include "depth_first_order.h"
#include "digraph.h"
#include <stack>
#include <vector>
#include "topological.h"
#include <algorithm>

using std::vector;
using std::invalid_argument;
using std::reverse;

bool is_dag(const Digraph &digraph);

void topological_dfs(const Digraph &digraph, size_t v, vector<bool> &marked,
                     vector<bool> &on_path, vector<size_t> &ret);

vector<size_t> topological_sort(const Digraph &digraph) {
    if (!is_dag(digraph))
        throw invalid_argument("error: the digraph is not an DAG");
    return DepthFirstOrder(digraph).reverse_post_order();
}

vector<size_t> topological_sort2(const Digraph &digraph) {
    vector<bool> marked(digraph.vertex_count());
    vector<bool> on_path(digraph.vertex_count());
    vector<size_t> ret;
    ret.reserve(digraph.vertex_count());
    for (size_t v = 0; v < digraph.vertex_count(); ++v)
        if (!marked[v]) topological_dfs(digraph, v, marked, on_path, ret);
    reverse(ret.begin(), ret.end());
    return ret;
}

// 拓扑排序和环检测同时进行
void topological_dfs(const Digraph &digraph, size_t v, vector<bool> &marked,
                     vector<bool> &on_path, vector<size_t> &ret) {
    marked[v] = true;
    on_path[v] = true;
    for (auto w : digraph.adjacent(v)) {
        if (!marked[w])
            topological_dfs(digraph, w, marked, on_path, ret);
        else if (on_path[w])
            throw invalid_argument("error: the digraph is not an DAG");
    }
    on_path[v] = false;
    ret.push_back(v);
}

void _has_circle(const Digraph &digraph, size_t v, vector<bool> &marked,
                 vector<bool> &on_path, bool &cycle) {
    marked[v] = true;
    on_path[v] = true;
    for (auto w : digraph.adjacent(v)) {
        if (cycle) return;
        if (!marked[w])
            _has_circle(digraph, w, marked, on_path, cycle);
        else if (on_path[w]) {
            cycle = true;
            return;
        }
    }
    on_path[v] = false;
}

bool has_circle(const Digraph &digraph) {
    vector<bool> on_path(digraph.vertex_count());
    vector<bool> marked(digraph.vertex_count());
    bool cycle = false;
    for (size_t v = 0; v < digraph.vertex_count(); ++v)
        if (!marked[v]) {
            _has_circle(digraph, v, on_path, marked, cycle);
            if (cycle) return true;
        }
    return false;
}

bool _has_circle2(const Digraph &digraph, size_t v, vector<bool> &marked,
                  vector<bool> &on_path) {
    marked[v] = true;
    on_path[v] = true;
    for (auto w : digraph.adjacent(v)) {
        if (!marked[w]) {
            if (_has_circle2(digraph, w, marked, on_path)) return true;
        } else if (on_path[w])
            return true;
    }
    on_path[v] = false;
    return false;
}

bool has_circle2(const Digraph &digraph) {
    vector<bool> on_path(digraph.vertex_count());
    vector<bool> marked(digraph.vertex_count());
    for (size_t v = 0; v < digraph.vertex_count(); ++v) {
        if (marked[v]) continue;
        if (_has_circle2(digraph, v, on_path, marked)) return true;
    }
    return false;
}

bool is_dag(const Digraph &digraph) { return !has_circle2(digraph); }

