//
// Created by Janusz Grzesik on 15.06.15.
//

#ifndef ASD_RELAX_H
#define ASD_RELAX_H
using namespace std;

#include "vector"

void relax (int start, int end, int weight, vector<int> &distances, vector<int> &parent){
    if(distances[start] > distances[end] + weight){
        distances[start] = distances[end]+ weight;
        parent[start]=end;
    }
}

#endif //ASD_RELAX_H
