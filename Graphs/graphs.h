//
// Created by Janusz Grzesik on 10.05.15.
//
#include <vector>
#include <string>
#include <queue>

using namespace std;
enum GraphNodeColor{
    // Enum that represents the current state of BFS
    WHITE,
    BLACK,
    GREY
};

struct GraphNode{
    // A standard element of a graph
    // val represents the label of the node
    int val;
    GraphNode* parent;
    GraphNodeColor color;
    int distance;
};

struct Graph{
    GraphNode** nodes;
    vector < vector <int> > edges;
    int number_of_nodes;
};

string BFS(Graph* graph, int index_to_start){

    for(int i=0; i<graph->number_of_nodes; i++){
        // Initialise all nodes in graph
        graph->nodes[i]->color=WHITE;
        graph->nodes[i]->distance=0;
        graph->nodes[i]->parent= nullptr;
    }

    queue<int> bfs_queue;
    string result;

    GraphNode* current =graph->nodes[index_to_start];
    current->color=GREY;
    bfs_queue.push(index_to_start);

    int previous_distance=0;
    int current_index;

    while(!bfs_queue.empty()){
        current_index = bfs_queue.front();
        bfs_queue.pop();
        current=graph->nodes[current_index];
        current->color=GREY;
        for(int i=0; i < graph->edges[current_index].size(); i++ ){
            if(graph->nodes[graph->edges[current_index][i]]->color==WHITE){
                bfs_queue.push(graph->edges[current_index][i]);
                graph->nodes[graph->edges[current_index][i]]->color=GREY;
                graph->nodes[graph->edges[current_index][i]]->distance=current->distance+1;
                graph->nodes[graph->edges[current_index][i]]->parent=current;
            }
        }
        current->color=BLACK;
        if(current->distance>previous_distance){
            result+="\n";
            previous_distance=current->distance;
        }
        result+=to_string(current->val)+" ";
    }
    return result;
}