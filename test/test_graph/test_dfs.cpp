//
// Created by Wenxuan on 9/17/2016.
//

#include "graph/dfs.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
    const auto graph = create_graph("tiny_graph.txt");
    size_t s;
    while (cin >> s) {
        DFS dfs(graph, s);
        for (size_t v = 0; v < graph.vertex_count(); ++v)
            if (dfs.connected(v)) cout << v << " ";
        cout << endl;
    }
}
