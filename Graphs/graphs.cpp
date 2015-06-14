#include <iostream>
#include "graph_builder.h"
#include "graphs.h"
#include "graph_plotter.h"
#include "dfs.h"
#include "topological_sorting.h"
#include "find_cycles.h"

using namespace std;

int main(int argc, const char * argv[]) {
    int size = 15;
    int density = 5;
    int weight_limit = 10;
    bool directional = true;
    bool weighted = true;
//    vector<vector<int> > graph_matrix = generate_graph_on_matrix(size, density, directional, weight_limit);
    vector<vector<int> > graph_matrix = generate_DAG_matrix(size, density, weight_limit);

    vector<string> labels ={ "A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","W","X","Y","Z"};
//    vector<string> labels;
    vector<vector<bool>> highlights(size+2, vector<bool>(size+2,true));
    wrap_with_start_and_finish(graph_matrix, labels);

    plot_graph(size +2 , printer_matrix_from_matrix(graph_matrix), directional, weighted, create_labels(labels), create_highlight(highlights));
    return 0;
}

