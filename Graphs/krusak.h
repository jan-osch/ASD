//
// Created by Janusz Grzesik on 14.06.15.
//

#ifndef ASD_KRUSAK_H
#define ASD_KRUSAK_H

#include <iostream>
#include "vector"
#include "string"
#include "graphs.h"
#include "union_find.h"

vector<vector<bool> > krusak(vector<vector<int> > graph){
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

    vector<vector<bool> > result(size, vector<bool>(size, false));


    //iterate found edges
    int temp_from, temp_to;
    for(int i=0; i<weights.size(); i++){
        temp_from = from[i];
        temp_to = to[i];

        //if the edge does not create a cycle add it to MST
        if(find(union_find_structure[temp_to])!=find(union_find_structure[temp_from])){
            union_nodes(union_find_structure[temp_to], union_find_structure[temp_from]);
            result[temp_from][temp_to]= true;
        }
    }
    return result;
}


#endif //ASD_KRUSAK_H
