//
// Created by Janusz Grzesik on 14.06.15.
//

#ifndef ASD_DIJKSTRA_H
#define ASD_DIJKSTRA_H

#define MAX_INT 1000000
#include <queue>
#include <string>
#include "vector"
#include "relax.h"
using namespace std;


vector<int> dijkstra(vector<vector<int> > graph, vector<string> &labels, int final_index) {
    int size = graph[0].size();

    //Create helper structures
    vector<int> parents(size);
    vector<int> distance(size, MAX_INT);
    for (int i = 0; i < size; i++) {
        parents[i] = i;
    }
    vector<bool> processed(size, false);
    int count_processed = 0;
    int temp_index;
    int min;
    if(labels.size()==0){
        labels = vector<string>(size);
        for(int i=0; i<size; i++){
            labels[i]=to_string(i);
        }
    }

    //initialise final_index the destination of the search
    distance[final_index] = 0;

    //As long as non-processed vertices exist process them
    while (count_processed < size) {

        //linear search for smallest distance
        min = MAX_INT;
        for (int i = 0; i < size; i++) {
            if (distance[i] <= min && !processed[i]) {
                min = distance[i];
                temp_index = i;
            }
        }
        count_processed++;
        processed[temp_index] = true;

        for (int j = 0; j < size; j++) {
            if (graph[j][temp_index] != 0 ) {
                relax(j, temp_index, graph[j][temp_index], distance, parents);
            }
        }
    }

    //change the labels
    vector<string> new_labels(size);
    for(int i=0; i<size;i++){
        new_labels[i]=labels[i]+"/"+to_string(distance[i])+"/"+labels[parents[i]];
    }
    for(int i=0; i<size; i++){
        labels[i]=new_labels[i];
    }
    return distance;
}
#endif //ASD_DIJKSTRA_H
