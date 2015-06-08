#include <iostream>
#include "graph_builder.h"
#include "graphs.h"

using namespace std;

int main(int argc, const char * argv[]) {
    Graph* example = graph_builder();
//    cout<<BFS(example,2);
    DFS(example);
    display_graph(example);
    return 0;
}

