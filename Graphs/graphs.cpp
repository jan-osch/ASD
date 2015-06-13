#include <iostream>
#include "graph_builder.h"
#include "graphs.h"
#include "graph_plotter.h"
#include "dfs.h"
#include "topological_sorting.h"
#include "find_cycles.h"

using namespace std;

int main(int argc, const char * argv[]) {
    int size = 10;
    int density = 10;
    int weight_limit = 10;
    bool directional = true;
    bool weighted = true;
    vector<vector<int>> graph_matrix = generate_graph_on_matrix(size, density, directional, weight_limit);
    vector<string> labels ={ "A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","W","X","Y","Z"};

    cout<<DFS_cycle(graph_matrix,labels, directional)<<endl;

    plot_graph(size, printer_matrix_from_matrix(graph_matrix), directional, weighted, create_labels(labels));
}

