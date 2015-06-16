//
// Created by Janusz Grzesik on 14.06.15.
//

#ifndef ASD_BELLMAN_FORD_H
#define ASD_BELLMAN_FORD_H


#include "relax.h"
#include "iostream"
#include "string"
using namespace std;

#define MAX_INT 1000000

void bellman_ford(vector<vector<int> > graph, vector<string> &labels, int final_index) {
    int size = graph[0].size();

    //Create helper structures
    vector<int> parents(size);
    vector<int> distances(size, MAX_INT);
    for (int i = 0; i < size; i++) {
        parents[i] = i;
    }
    if(labels.size()==0){
        labels = vector<string>(size);
        for(int i=0; i<size; i++){
            labels[i]=to_string(i);
        }
    }

    //initialise final_index the destination of the search
    distances[final_index] = 0;

    //Main loop: iterates all vertices
    for(int k=0; k<size-1;k++ ) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (graph[i][j] != 0) {
                    relax(i, j, graph[i][j], distances, parents);
                }
            }
        }
    }

    //Verification loop: check if graph still relaxes
    int old_distance;
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            if(graph[i][j]!=0){
                old_distance = distances[i];
                relax(i, j,graph[i][j], distances, parents);
                if (old_distance != distances[i]){
                    cout<<"CYCLE WITH MINUS WEIGHT"<< endl;
                    cout<<old_distance - distances[i]<<endl;
                }
            }
        }
    }

    //change the labels
    vector<string> new_labels(size);
    for(int i=0; i<size;i++){
        new_labels[i]=labels[i]+"/"+to_string(distances[i])+"/"+labels[parents[i]];
    }
    for(int i=0; i<size; i++){
        labels[i]=new_labels[i];
    }
}


#endif //ASD_BELLMAN_FORD_H
