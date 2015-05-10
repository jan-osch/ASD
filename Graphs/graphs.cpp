#include <iostream>
#include "graphs.h"
using namespace std;
int main(int argc, const char * argv[]) {
    // Example One a simple graph from Cormen polish edition page 527
    GraphNode** example_one_nodes = new GraphNode*[5];

    for(int i=0; i<5; i++){
        example_one_nodes[i]=new GraphNode();
        example_one_nodes[i]->val=i+1;
    }
    vector <vector<int>> example_one_edges(5);
    example_one_edges[0].push_back(1);
    example_one_edges[0].push_back(4);
    example_one_edges[1].push_back(0);
    example_one_edges[1].push_back(2);
    example_one_edges[1].push_back(4);
    example_one_edges[1].push_back(3);
    example_one_edges[2].push_back(1);
    example_one_edges[2].push_back(3);
    example_one_edges[3].push_back(2);
    example_one_edges[3].push_back(1);
    example_one_edges[3].push_back(4);

    Graph* example_one_graph = new Graph;
    example_one_graph->edges=example_one_edges;
    example_one_graph->nodes=example_one_nodes;
    example_one_graph->number_of_nodes=5;

    cout<<BFS(example_one_graph,3);
    return 0;
}