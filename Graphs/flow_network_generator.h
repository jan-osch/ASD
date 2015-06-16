//
// Created by Janusz Grzesik on 15.06.15.
//

#ifndef ASD_FLOW_NETWORKS_H
#define ASD_FLOW_NETWORKS_H

#define MAX_INT 1000000
#include <queue>
#include <string>
#include "vector"
#include "relax.h"
#include "graph_builder.h"
#include "dijkstra.h"
using namespace std;

vector<vector<int> > generate_flow_network(int size, int density, int weight_limit){
    //Very clumsy method that generates a flow_network with single source and single destination
    vector<vector<int> > result;
    vector<int> distances;
    vector<string> some_labels;
    bool flag= true;
    int i, count;
    int max_dist=0;
    do{
        //create a randon graph and remove duplicate edges
        result = generate_graph_on_matrix(size,density, true, weight_limit);
        for(int i=0; i<size; i++){
            count =0;
            for(int j=0; j<size; j++){
                if(j==0){
                    result[i][j]=0;
                }
                if(j==size-1){
                    result[j][i]=0;
                }
                if(result[i][j]!=0 && result[j][i]!=0){
                    if(result[i][j]>result[j][i]){
                        result[j][i]=0;
                    }else{
                        result[i][j]=0;
                    }
                }
                if(result[j][i]!=0){
                    count++;
                }
            }
            if(count==0 && i!=0){
                result[0][i]=max(1,rand() % weight_limit);
            }
        }

        //Linear check if all distances are smaller than MAX_INT
        distances = dijkstra(result,some_labels,size-1);
        i=0;
        while(i<size && flag){
            if(distances[i]==MAX_INT){
                flag=false;
            }
            if(distances[i]>distances[max_dist]){
                max_dist=i;
            }
            i++;
        }
    }while(!flag);
    result[max_dist][size-1]=max(1,rand() % weight_limit);
    return result;
}

#endif //ASD_FLOW_NETWORKS_H
