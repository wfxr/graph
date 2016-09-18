//
// Created by wenxuan-zhang on 16-9-18.
//

#include "digraph/dfs.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char **argv) {
    auto digraph = create_graph("tinyDG.txt");

    size_t src;
    while (cin) {
        string line;
        getline(cin, line);
        istringstream iss(line);
        vector<size_t> srcs;
        while (iss >> src)
            srcs.push_back(src);

        DFS dfs(digraph, srcs);
        for (size_t v = 0; v < digraph.vertex_count(); ++v)
            if (dfs.connected(v)) cout << v << " ";
        cout << endl;
    }
}
