//
// Created by Wenxuan on 9/17/2016.
//

#include "paths.h"
#include "graph.h"
#include <iostream>
#include <fstream>

using namespace std;

int main() {
    const auto graph = create_graph("tiny_graph.txt");

    Graph::VertexType src, dest;
    cout << "source vertex: ";
    cin >> src;

    Paths paths(graph, src);
    while (cin >> dest) {
        for (auto v : paths.path_to(dest))
            cout << v << " ";
        cout << endl;
    }
}
