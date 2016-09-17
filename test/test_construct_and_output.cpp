//
// Created by Wenxuan on 9/15/2016.
//

#include "graph.h"
#include <iostream>

using namespace std;

int main() {
    const Graph::SizeType tiny_graph_v = 13;
    const vector<Graph::Edge> tiny_graph_edges{
            {0,  5},
            {4,  3},
            {0,  1},
            {9,  12},
            {6,  4},
            {5,  4},
            {0,  2},
            {11, 12},
            {9,  10},
            {0,  6},
            {7,  8},
            {9,  11},
            {5,  3}
    };
    const Graph tiny_graph(tiny_graph_v, tiny_graph_edges);

    cout << tiny_graph.to_string();
}
