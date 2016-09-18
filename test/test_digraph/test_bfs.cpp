//
// Created by Wenxuan on 9/17/2016.
//

#include "digraph/bfs.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
    const auto graph = create_graph("tinyDG.txt");
    size_t s;
    while (cin >> s) {
        BFS bfs(graph, s);
        for (size_t v = 0; v < graph.vertex_count(); ++v)
            if (bfs.connected(v)) cout << v << " ";
        cout << endl;
    }
}
