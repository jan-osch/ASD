//
// Created by Janusz Grzesik on 14.06.15.
//

#ifndef ASD_KRUSAK_H
#define ASD_KRUSAK_H

#include <iostream>
#include "vector"
#include "string"
#include "graphs.h"

vector<vector<bool> > krusak(vector<vector<int> > graph){
    vector<int> weights;
    vector<int> from;
    vector<int> to;
    int size = graph[0].size();

    int temp;

    int k;
    for(int i=0; i<size; i++){
        //create three mirror vectors that are sorted by weight in non-descending order
        for(int j=0; j<size; j++){
            temp = graph[i][j];
            if(temp!=0){
                k=0;
                while(k<weights.size() && weights[k]<= temp){
                    k++;
                }
                weights.insert(weights.begin()+k+1, weights.begin()+k, weights.end());
                from.insert(from.begin()+k+1, from.begin()+k, from.end());
                to.insert(to.begin()+k+1, to.begin()+k, to.end());

                weights.insert(weights.begin()+k,temp);
                from.insert(from.begin()+k,i);
                to.insert(to.begin()+k,j);
            }
        }
    }



}

#endif //ASD_KRUSAK_H
