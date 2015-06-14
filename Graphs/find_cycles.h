//
// Created by Janusz Grzesik on 13.06.15.
//

#ifndef ASD_FIND_CYCLES_H
#define ASD_FIND_CYCLES_H

using namespace std;

#include <iostream>
#include "vector"
#include "string"
#include "graphs.h"

bool DFSVisit_cycle(vector<vector<int> > graph,
              vector<GraphNodeColor> &colors,
              vector<int> &distances,
              vector<int> &parents,
              vector<int> &times_in,
              vector<int> &times_out,
              vector<string> labels,
              int index_to_visit,
              int & time,
              bool directed){

    colors[index_to_visit] = GREY;
    times_in[index_to_visit]=time;
    bool flag = false;

    for(int i=0; i<distances.size(); i++){
        if( colors[i] == WHITE) {
            if (graph[index_to_visit][i] != 0 ) {
                parents[i] = index_to_visit;
                distances[i] = distances[index_to_visit] + graph[index_to_visit][i];
                time++;
                flag = flag || DFSVisit_cycle(graph, colors, distances, parents, times_in, times_out, labels, i, time, directed);
            }
            if (!directed && graph[i][index_to_visit] != 0 && colors[i] == WHITE){
                parents[i] = index_to_visit;
                distances[i] = distances[index_to_visit] + graph[i][index_to_visit];
                time++;
                flag = flag || DFSVisit_cycle(graph, colors, distances, parents, times_in, times_out, labels, i, time, directed);
            }
        }
        else{
            if (!directed && graph[index_to_visit][i] != 0 && parents[index_to_visit]!=i){
                cout<<"CYCLE! "<<labels[i]<<endl;
                flag = true;
            }
            if (directed && graph[index_to_visit][i] != 0 && colors[i]==GREY ){
                cout<<"CYCLE! "<<labels[i]<<endl;
                flag = true;
            }
        }
    }
    time++;
    colors[index_to_visit]=BLACK;
    times_out[index_to_visit]=time;
    return flag;
}

bool DFS_cycle(vector<vector<int> > graph, vector<string> &labels, bool directed){
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
    bool flag = false;
    int time=0;
    for(int i=0; i<size; i++ ){
        if(colors[i]==WHITE){
            time++;
            if (DFSVisit_cycle(graph, colors, distances, parents, time_in, time_out, labels, i, time, directed)){
                flag = true;
            }
        }
    }
    return flag;
};

#endif //ASD_FIND_CYCLES_H
