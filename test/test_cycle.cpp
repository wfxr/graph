//
// Created by Wenxuan on 9/17/2016.
//

#include "cycle.h"
#include <iostream>


using namespace std;

int main(int argc, char **argv) {
    {
        const auto graph = create_graph("tiny_graph.txt");
        cout << graph.to_string();

        Cycle cycle(graph);
        cout << "the graph has " << (cycle.has_cycle() ? "" : "no ") << "cycle."
             << endl;
    }

    cout << endl;

    {
        std::vector<Graph::Edge> edges{
                {0, 5},
                {1, 0},
                {2, 4},
                {3, 2},
                {4, 2},
                {2, 0}
        };
        const auto graph = Graph(6, edges);
        cout << graph.to_string();

        Cycle cycle(graph);
        cout << "the graph has " << (cycle.has_cycle() ? "" : "no ") << "cycle."
             << endl;
    }
}
