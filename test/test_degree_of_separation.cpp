//
// Created by wenxuan-zhang on 16-9-18.
//

#include "graph/symbol_graph.h"
#include "graph/bfs_paths.h"

using namespace std;

int main(int argc, char **argv) {
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " filename delimiter source" << endl;
        return 1;
    }

    const auto sgraph = create_symbol_graph(argv[1], argv[2]);
    const auto src_id = sgraph.id_of(argv[3]);
    const auto graph = sgraph.graph();
    BFSPaths bfs_paths(graph, src_id);
    string dest;
    while (getline(cin, dest)) {
        if (!sgraph.contains(dest)) {
            cout << "\t" << dest << " do not exist" << endl;
            continue;
        }
        auto dest_id = sgraph.id_of(dest);
        if (!bfs_paths.connected(dest_id)) {
            cout << "\tnot connected" << endl;
            continue;
        }
        for (auto w : bfs_paths.path_to(dest_id))
            cout << "\t" << sgraph.symbol_of(w) << endl;
    }
}
