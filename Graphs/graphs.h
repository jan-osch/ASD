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
    char val;
    GraphNode* parent;
    GraphNodeColor color;
    int distance;
    int time_in;
    int time_out;
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
        result+=current->val;
        result+=" ";
    }
    return result;
}


void DFSVisit(Graph* graph, int index_to_visit, int & time, string & result){
    graph->nodes[index_to_visit]->color=GREY;
    graph->nodes[index_to_visit]->time_in=time;
    result+="\n";
    result+=graph->nodes[index_to_visit]->val;

    for(int i=0; i<graph->edges[index_to_visit].size(); i++){
        if(graph->nodes[graph->edges[index_to_visit][i]]->color==WHITE){
            graph->nodes[graph->edges[index_to_visit][i]]->parent=graph->nodes[index_to_visit];
            graph->nodes[graph->edges[index_to_visit][i]]->distance=graph->nodes[index_to_visit]->distance+1;
            time++;
            DFSVisit(graph, graph->edges[index_to_visit][i], time, result);
        }
    }
    time++;
    graph->nodes[index_to_visit]->color=BLACK;
    graph->nodes[index_to_visit]->time_out=time;
}

string DFS(Graph* graph){
    // A Cormen style implementation of DFS
    // Recursively searches all nodes that adjust to current node in the graph
    // Changes colors of Nodes that are visited: WHITE->GREY->BLACK

    // set all nodes to not visited yet
    for(int i=0; i<graph->number_of_nodes; i++){
        graph->nodes[i]->color=WHITE;
        graph->nodes[i]->distance=0;
        graph->nodes[i]->parent= nullptr;
    }
    int time=0;
    string result = "";
    for(int i=0; i<graph->number_of_nodes; i++ ){
        if(graph->nodes[i]->color==WHITE){
            time++;
            DFSVisit(graph,i, time, result);
        }
    }
    return result;
}
