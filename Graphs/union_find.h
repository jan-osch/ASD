//
// Created by Janusz Grzesik on 14.06.15.
//

#ifndef ASD_UNION_FIND_H
#define ASD_UNION_FIND_H


struct Node{
    int value;
    Node* next;
};

Node* find(Node* suspect){
    if(suspect->next != suspect){
        suspect->next = find(suspect->next);
    }
    return suspect->next;
}

void union_nodes(Node *first, Node *second) {
    first->next = find(second);
}


#endif //ASD_UNION_FIND_H
