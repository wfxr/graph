//
// Created by Wenxuan on 9/17/2016.
//

#include "digraph/dfs_paths.h"
#include <iostream>

using namespace std;

int main() {
    const auto graph = create_graph("tinyDG.txt");
    size_t src;
    while (cin >> src) {
        DFSPaths paths(graph, src);
        for (size_t dest = 0; dest < graph.vertex_count(); ++dest) {
            cout << src << " to " << dest << ": ";
            if (!paths.connected(dest))
                cout << "not connect";
            else
                for (auto v : paths.path_to(dest))
                    cout << v << (v == dest ? "" : "-");
            cout << endl;
        }
    }
}
