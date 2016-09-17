//
// Created by Wenxuan on 9/17/2016.
//

#include "dfs.h"
#include "graph.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
    const auto graph = create_graph("tiny_graph.txt");

    Graph::SizeType s;
    while (cin >> s) {
        DFS dfs(graph, s);
        for (Graph::SizeType v = 0; v < graph.vertex_count(); ++v)
            cout << v << ": "
                 << (dfs.connected(v) ? "" : "not ") << "connected"
                 << endl;
    }
}
