//
// Created by Wenxuan on 9/18/2016.
//

#include "symbol_graph.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " filename delimiter" << endl;
        return 1;
    }

    const auto graph = create_symbol_graph(argv[1], argv[2]);

    string symbol;
    while (getline(cin, symbol))
        if (graph.contains(symbol))
            for (const auto & id : graph.adjacent(symbol))
                cout << "\t" << graph.symbol_of(id) << endl;
        else
            cout << symbol << " not exist in graph" << endl;
}
