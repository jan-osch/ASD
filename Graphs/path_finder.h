//
// Created by Janusz Grzesik on 14.06.15.
//

#ifndef ASD_PATH_FINDER_H
#define ASD_PATH_FINDER_H

#include <iostream>
#include <stack>
#include "vector"
#include "string"
#include "graphs.h"

bool path_exists(vector<vector<int> > graph, int start, int end){
    stack<int> older_indices;
    older_indices.push(start);
    int temp;
    int size = graph[0].size();
    vector<bool> already_checked(size, false);
    while(!older_indices.empty()){
        temp = older_indices.top();
        older_indices.pop();
        already_checked[temp]= true;
        for(int i =0; i<size; i++){
            if(graph[temp][i]!=0){
                if(i==end){
                    return true;
                }
                if(!already_checked[i]){
                    older_indices.push(i);
                }
            }
        }
    }
    return false;
}

#endif //ASD_PATH_FINDER_H
