#ifndef GRAPH_BUILDER_H
#define GRAPH_BUILDER_H
//
// Created by Janusz Grzesik on 11.05.15.
//
#include "graphs.h"
#include "find_cycles.h"
#include "path_finder.h"
#include <iostream>
#include <assert.h>

NonWeightedDirectionalGraphOnLists * graph_builder(){
    // A function that helps to build a graph
    // In first line number of nodes is read
    // Then in second line lables for all nodes are read
    // Then in each consecutive line number of edges for the node and then nodes
    int number_of_nodes;
    cin>>number_of_nodes;
    GraphNode** nodes = new GraphNode*[number_of_nodes];
    for(int i=0; i<number_of_nodes;i++){
        nodes[i]=new GraphNode();
        cin>>nodes[i]->val;
    }
    vector <vector<int> > edges(number_of_nodes);
    int size;
    int temp;
    for(int i=0; i<number_of_nodes; i++){
        cin>>size;
        while(size>0){
            size--;
            cin>>temp;
            edges[i].push_back(temp);
        }
    }
    NonWeightedDirectionalGraphOnLists * result = new NonWeightedDirectionalGraphOnLists();
    result->edges=edges;
    result->nodes=nodes;
    result->number_of_nodes=number_of_nodes;
    return result;
}

vector<vector<int> > generate_graph_on_matrix(int number_of_nodes, int density, bool directional, int weight_limit){
    assert (density>0 && density<=100);
    assert (weight_limit>=1);
    vector<vector<int> > result(number_of_nodes, vector<int>(number_of_nodes, 0)); // initalise everything to zero

    for(int i=0; i<number_of_nodes; i++) {
        for (int j = 0; j < number_of_nodes; j++) {
            if (rand() % 100 <= density) {
                //generate node
                if (directional) {
                    result[i][j] = max(1, rand() % weight_limit);
                }else{
                    result[i][j] = max(1, rand() % weight_limit);
                    result[j][i] = result[i][j];
                }
            }
        }
    }
    return result;
}

vector<vector<int> > generate_DAG_matrix(int number_of_nodes, int density, int weight_limit){
    assert (density>0 && density<=100);
    assert (weight_limit>=1);
    bool directional = true;
    vector<vector<int> > result(number_of_nodes, vector<int>(number_of_nodes, 0)); // initalise everything to zero

    for(int i=0; i<number_of_nodes; i++) {
        for (int j = 0; j < number_of_nodes; j++) {
            if (rand() % 100 <= density) {
                //generate node
                if(!path_exists(result, j, i) && i!=j) {
                    result[i][j] = max(1, rand() % weight_limit);
                }
            }
        }
    }
    return result;
}

void display_graph(NonWeightedDirectionalGraphOnLists * graph){
    std::cout<<endl;
    for(int i =0; i<graph->number_of_nodes; i++){
        std::cout<<graph->nodes[i]->val<<
                "\tIn: "<< graph->nodes[i]->time_in <<
                "\tOut: "<< graph->nodes[i]->time_out <<
                "\tDistance: "<< graph->nodes[i]->distance<<
                "\tParent: ";

        if(graph->nodes[i]->parent!= nullptr) {
            std::cout << graph->nodes[i]->parent->val << std::endl;
        }
        else{
            std::cout<<"_"<<std::endl;
        }
    }
}

#endif

/*
Example graph Cormen page 541

6
A B C D E F
2 1 5
1 4
2 4 3
1 5
1 5
1 1

Example graph Cormen page 541 modified

6
A B C D E F
2 1 5
1 4
1 4
2 3 0
2 5 3
1 1

Example graph Cormen page 527

4
A B C D
2 1 4
4 0 2 4 3
2 1 3
3 2 1 4


sample_graph_1

5
1 2 3 4 5
2 3 1
1 2
1 0
2 1 4
2 2 1

*/