//
// Created by Wenxuan on 9/17/2016.
//

#include "tow_color.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
    {
        const auto graph = create_graph("tiny_graph.txt");
        cout << graph.to_string();

        TwoColor two_color(graph);
        cout << "the graph is " << (two_color.two_colorable() ? "" : "not ") << "two colorable."
             << endl;
    }

    cout << endl;

    {
        std::vector<Graph::Edge> edges{
                {0, 1},
                {1, 2},
                {2, 3},
                {3, 0}
        };
        const auto graph = Graph(4, edges);
        cout << graph.to_string();

        TwoColor two_color(graph);
        cout << "the graph is " << (two_color.two_colorable() ? "" : "not ") << "two colorable."
             << endl;
    }
}
