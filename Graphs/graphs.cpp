#include <iostream>
#include "graph_builder.h"
#include "graphs.h"
#include "graph_plotter.h"
#include "dfs.h"
#include "topological_sorting.h"
#include "find_cycles.h"
#include "krusak.h"
#include "prim.h"
#include "dijkstra.h"
#include "bellman_ford.h"
#include "flow_network_generator.h"

using namespace std;

int main(int argc, const char * argv[]) {
    srand (time(NULL));
    int size = 10;
    int second_size= size;
    int density = 50;
    int weight_limit = 10;
    bool directional = true;
    bool weighted = true;
//    vector<vector<int> > graph_matrix = generate_graph_on_matrix(size, density, directional, weight_limit);
//    vector<vector<int> > graph_matrix = generate_DAG_matrix(size, density, weight_limit);
    vector<vector<int> > graph_matrix = generate_flow_network(size, density, weight_limit);

    vector<string> labels ={ "A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","W","X","Y","Z"};
//    vector<string> labels;
//    vector<vector<bool>> highlights(second_size, vector<bool>(second_size,false));
//    wrap_with_start_and_finish(graph_matrix, labels);

//    vector<vector<bool>> highlights = krusak(graph_matrix);
//    vector<vector<bool>> highlights = prim(graph_matrix);
//    vector<vector<bool>> highlights = prim(graph_matrix);
//    plot_graph(second_size, printer_matrix_from_matrix(graph_matrix), directional, weighted, create_labels(labels), create_highlight(highlights));
    dijkstra(graph_matrix, labels, size-1);
//    bellman_ford(graph_matrix, labels, 0);
    plot_graph(second_size, printer_matrix_from_matrix(graph_matrix), directional, weighted, create_labels(labels), "");
    return 0;
}

