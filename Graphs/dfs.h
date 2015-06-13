//
// Created by Janusz Grzesik on 13.06.15.
//

#ifndef ASD_DFS_H
#define ASD_DFS_H

using namespace std;

#include "string"
#include "vector"

void DFSVisit(vector<vector<int>> graph,
              vector<GraphNodeColor> &colors,
              vector<int> &distances,
              vector<int> &parents,
              vector<int> &times_in,
              vector<int> &times_out,
              vector<string> labels,
              int index_to_visit,
              int & time,
              string & result,
              bool directed){

    colors[index_to_visit] = GREY;
    times_in[index_to_visit]=time;
    result+="\n";
    result+=labels[index_to_visit];

    for(int i=0; i<distances.size(); i++){
        if( i!=index_to_visit && colors[i] == WHITE) {
            if (graph[index_to_visit][i] != 0 ) {
                parents[i] = index_to_visit;
                distances[i] = distances[index_to_visit] + graph[index_to_visit][i];
                time++;
                DFSVisit(graph, colors, distances, parents, times_in, times_out, labels, i, time, result, directed);
            }
            if (!directed && graph[i][index_to_visit] != 0 && colors[i] == WHITE){
                parents[i] = index_to_visit;
                distances[i] = distances[index_to_visit] + graph[i][index_to_visit];
                time++;
                DFSVisit(graph, colors, distances, parents, times_in, times_out, labels, i, time, result, directed);
            }
        }
    }
    time++;
    colors[index_to_visit]=BLACK;
    times_out[index_to_visit]=time;
}

string DFS(vector<vector<int>> graph, vector<string> &labels, bool directed){
    // A Cormen style implementation of DFS
    // Recursively searches all nodes that adjust to current node in the graph
    // Changes colors of Nodes that are visited: WHITE->GREY->BLACK


    int size = graph[0].size();

    //initalise additional data
    vector<int> distances(size,0);
    vector<int> parents(size);
    for(int i=0; i<size; i++){
        parents[i]=i;
    }
    vector<int> time_in(size);
    vector<int> time_out(size);
    vector<GraphNodeColor> colors(size,WHITE);

    if(labels.size()==0){
        labels = vector<string>(size);
        for(int i=0; i<size; i++){
            labels[i]=to_string(i);
        }
    }

    int time=0;
    string result = "";
    for(int i=0; i<size; i++ ){
        if(colors[i]==WHITE){
            time++;
            DFSVisit(graph, colors, distances, parents, time_in, time_out, labels, i, time, result, directed);
        }
    }
    vector<string> new_labels(size);
    for(int i=0; i<size;i++){
        new_labels[i]=labels[i]+"/"+to_string(distances[i])+"/"+labels[parents[i]]+"/"+to_string(time_in[i])+"/"+to_string(time_out[i]);
    }
    for(int i=0; i<size; i++){
        labels[i]=new_labels[i];
    }
    return result;
};

#endif //ASD_DFS_H
