#ifndef ASD_TOPOLOGICAL_SORTING_H
#define ASD_TOPOLOGICAL_SORTING_H

//
// Created by Janusz Grzesik on 13.06.15.
//
using namespace std;

#include <stack>
#include "string"
#include "vector"
#include "graphs.h"

void DFSVisit_topological(vector<vector<int> > graph,
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


    for(int i=0; i<distances.size(); i++){
        if( i!=index_to_visit && colors[i] == WHITE) {
            if (graph[index_to_visit][i] != 0 ) {
                parents[i] = index_to_visit;
                distances[i] = distances[index_to_visit] + graph[index_to_visit][i];
                time++;
                DFSVisit_topological(graph, colors, distances, parents, times_in, times_out, labels, i, time, result, directed);
            }
            if (!directed && graph[i][index_to_visit] != 0 && colors[i] == WHITE){
                parents[i] = index_to_visit;
                distances[i] = distances[index_to_visit] + graph[i][index_to_visit];
                time++;
                DFSVisit_topological(graph, colors, distances, parents, times_in, times_out, labels, i, time, result, directed);
            }
        }
    }
    time++;
    colors[index_to_visit]=BLACK;
    string new_result = labels[index_to_visit]+"\n";
    new_result+=result;
    result=new_result;
    times_out[index_to_visit]=time;
}

string DFS_topological(vector<vector<int> > graph, vector<string> &labels, bool directed){
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
            DFSVisit_topological(graph, colors, distances, parents, time_in, time_out, labels, i, time, result, directed);
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

vector<int> topological_sorting(vector<vector<int> > graph, vector<string> &labels){


    int size = graph[0].size();
    vector<int> order(size,0);
    for(int i =0; i<size; i++){
        for(int j=0; j<size; j++){
            if(graph[j][i]!=0){
                order[j]++;
            }
        }
    }
    stack<int> zero_order;
    for(int i =0; i<size; i++) {
        if (order[i] == 0) {
            zero_order.push(i);
        }
    }

    vector<int> final_order(size);
    int counter = 0;

    int x;
    while(!zero_order.empty()){
        x = zero_order.top();
        zero_order.pop();
        final_order[x]=counter++;

        for(int j=0; j<size; j++){
            if(graph[j][x]!=0){
                order[j]--;
                if(order[j]==0){
                    zero_order.push(j);
                }
            }
        }
    }
    if(labels.size()==0){
        labels = vector<string>(size);
        for(int i=0; i<size; i++){
            labels[i]=to_string(i);
        }
    }

    for(int i=0; i<size; i++){
        labels[i]+="/"+to_string(final_order[i]);
    }
    return final_order;
}

int find_parent_by_order(vector<vector<int> > graph, vector<int> order, int index){
    int size = graph[0].size();
    int max_index = index;
    int temp;
    for(int i =0; i < size; i++){
        if(graph[i][index]!=0){
            temp = find_parent_by_order(graph,order,i);
            if(order[temp]  > order[max_index]){
                max_index = temp;
            }
        }
    }
    return max_index;
}

int find_child_by_order(vector<vector<int> > graph, vector<int> order, int index){
    int size = graph[0].size();
    int min_index = index;
    int temp;
    for(int i =0; i < size; i++){
        if(graph[index][i]!=0){
            temp = find_child_by_order(graph,order,i);
            if(order[temp]  < order[min_index]){
                min_index = temp;
            }
        }
    }
    return min_index;
}

void wrap_with_start_and_finish(vector<vector<int> > &graph, vector<string> &labels ){
    int original_size = graph[0].size();
    vector<int> order = topological_sorting(graph, labels);
    vector<vector<int> > result (original_size+2, vector<int>(original_size+2, 0));

    int suspect_parent;
    int suspect_child;
    for(int i=0; i< original_size; i++){
        suspect_parent = find_parent_by_order(graph, order, i);
        suspect_child = find_child_by_order(graph, order, i);

        if(result[0][suspect_parent+1]!=1){
            result[0][suspect_parent+1]=1;
        }
        if(result[suspect_child+1][original_size+1]!=1){
            result[suspect_child+1][original_size+1]=1;
        }
        for(int j=0; j<original_size; j++){
            result[i+1][j+1]=graph[i][j];
        }
    }
    vector<string> new_labels(original_size+2);
    new_labels[0]="START";
    for(int i=0; i<original_size; i++){
        new_labels[i+1]=labels[i];
    }
    new_labels[original_size+1]="END";
    graph=result;
    labels=new_labels;
}


#endif //ASD_TOPOLOGICAL_SORTING_H
