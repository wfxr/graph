//
// Created by Wenxuan on 9/17/2016.
//

#include "graph/connected_component.h"

using namespace std;

int main(int argc, char **argv) {
    const auto graph = create_graph("tiny_graph.txt");
    ConnectedComponent cc(graph);

    cout << cc.count() << " connected components" << endl;
    auto components = cc.components();
    for (const auto& component :components) {
        for (auto v : component)
            cout << v << " ";
        cout << endl;
    }
}
