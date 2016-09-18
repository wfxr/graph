//
// Created by wenxuan-zhang on 16-9-18.
//

#include "digraph/digraph.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
    auto digraph = create_graph("tinyDG.txt");

    cout << digraph.to_string();
}
