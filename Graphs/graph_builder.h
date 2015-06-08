#ifndef GRAPH_BUILDER_H
#define GRAPH_BUILDER_H
//
// Created by Janusz Grzesik on 11.05.15.
//
#include "graphs.h"
#include <iostream>

Graph* graph_builder(){
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
    vector <vector<int>> edges(number_of_nodes);
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
    Graph* result = new Graph();
    result->edges=edges;
    result->nodes=nodes;
    result->number_of_nodes=number_of_nodes;
    return result;
}

void display_graph(Graph* graph){
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