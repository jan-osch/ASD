//
// Created by Janusz Grzesik on 14.06.15.
//

#ifndef ASD_PRIM_H
#define ASD_PRIM_H

#include <iostream>
#include "vector"
#include "union_find.h"

vector<vector<bool> > prim(vector<vector<int> > graph){
    vector<int> weights;
    vector<int> from;
    vector<int> to;
    int size = graph[0].size();

    int temp;

    int k;
    //create three mirror vectors that are sorted by weight in non-descending order
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            temp = graph[i][j];
            if(temp!=0){
                k=0;
                while(k<weights.size() && weights[k]<= temp){
                    k++;
                }
                if(k==0){
                    k=1;
                }
                weights.insert(weights.begin()+k-1, temp);
                from.insert(from.begin()+k-1, i);
                to.insert(to.begin()+k-1, j);
            }
        }
    }

    //crete Union find structure
    vector<Node*> union_find_structure(size);
    for(int i=0; i<size; i++){
        union_find_structure[i]= new Node;
        union_find_structure[i]->next = union_find_structure[i];
        union_find_structure[i]->value=i;
    }

    //create result
    vector<vector<bool> > result(size, vector<bool>(size, false));

    Node* MSThead = nullptr;
    //iterate found edges
    int temp_from, temp_to;
    for(int i=0; i<weights.size(); i++){
        temp_from = from[i];
        temp_to = to[i];
        if(MSThead== nullptr || find(union_find_structure[temp_to])!=MSThead || find(union_find_structure[temp_from])!=MSThead){
            union_nodes(union_find_structure[temp_to], union_find_structure[temp_from]);
            result[temp_from][temp_to]= true;
            MSThead = find(union_find_structure[temp_to]);
        }
    }
    return result;
}

#endif //ASD_PRIM_H
