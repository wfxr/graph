//
// Created by Wenxuan on 9/17/2016.
//

#include "bfs.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
    const auto graph = create_graph("tiny_graph.txt");
    size_t s;
    while (cin >> s) {
        BFS bfs(graph, s);
        for (size_t v = 0; v < graph.vertex_count(); ++v)
            cout << v << ": "
                 << (bfs.connected(v) ? "" : "not ") << "connected"
                 << endl;
    }
}
