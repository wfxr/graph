//
// Created by wenxuan-zhang on 16-9-20.
//

#include "digraph/digraph.h"
#include "digraph/topological.h"
#include <iostream>

using namespace std;

int main() {
    {
        const auto graph = create_graph("tinyDAG.txt");
        cout << graph.to_string();

        cout << "topological sort:" << endl;
        try {
            auto result = topological_sort2(graph);
            for (auto v : result)
                cout << v << " ";
        } catch (invalid_argument e) {
            cout << e.what();
        }
        cout << endl;
    }

    cout << endl;

    {
        std::vector<Digraph::Edge> edges{{0, 5}, {1, 0}, {2, 4},
                                         {3, 2}, {2, 0}, {5, 1}};
        const auto graph = Digraph(6, edges);
        cout << graph.to_string();

        cout << "topological sort:" << endl;
        try {
            auto result = topological_sort2(graph);
            for (auto v : result)
                cout << v << " ";
        } catch (invalid_argument e) {
            cout << e.what();
        }
    }
}
