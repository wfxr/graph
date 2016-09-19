//
// Created by Wenxuan on 9/17/2016.
//

#include "digraph/cycle.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
    {
        const auto graph = create_graph("tinyDAG.txt");
        cout << graph.to_string();

        Cycle cycle(graph);
        cout << "the graph has " << (cycle.has_cycle() ? "" : "no ") << "cycle." << endl;

        for (auto v : cycle.cycle())
            cout << v << " ";
        cout << endl;
    }

    cout << endl;

    {
        std::vector<Digraph::Edge> edges{{0, 5}, {1, 0}, {2, 4}, {3, 2}, {2, 0}, {5, 1}};
        const auto graph = Digraph(6, edges);
        cout << graph.to_string();

        Cycle cycle(graph);
        cout << "the graph has " << (cycle.has_cycle() ? "" : "no ") << "cycle." << endl;

        for (auto v : cycle.cycle())
            cout << v << " ";
        cout << endl;
    }
}
