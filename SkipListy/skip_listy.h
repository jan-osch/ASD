//
// Created by Janusz Grzesik on 07.05.15.
//

#include <stdlib.h>

#ifndef ASD_SKIP_LISTY_H
#define ASD_SKIP_LISTY_H

#define MAX_LEVEL 10
#define MIN_VALUE -1000

#endif //ASD_SKIP_LISTY_H

using namespace std;


struct SLNode{
    int data;
    int level;
    SLNode ** next;

    SLNode(int d, int l) {
        /*
         * Initialises a new Skip List Node
         * All next values will be set to nullptr for this node
         */
        next = new SLNode* [l+1];
        data = d;
        level = l;
    }
};

struct SkipList{
    SLNode * head;


    SkipList() {
        SLNode * new_head = new SLNode(MIN_VALUE, MAX_LEVEL) ;
        for( int i =0 ; i< MAX_LEVEL; i++){
            new_head->next[i]= nullptr;
        }
        head = new_head;
    }
};

int getLevel(){
    int result = 0;
    while(result < MAX_LEVEL && rand() % 2 >0){
        result++;
    }
    return result;
}

void insert(SkipList l , int key){
    /*
     * Creates a new SLNode with the value of key
     * Inserts the Node at before first occurrence of the same key or a bigger key
     */
    int new_level = getLevel();
    SLNode* new_node = new SLNode(key, new_level);
    SLNode** update_table = new SLNode*[new_level+1];
    SLNode* current_node = l.head;

    for(int i = new_level; i>=0; i--){
        while(current_node->next[i]!= nullptr && current_node->next[i]->data < key){
            current_node= current_node->next[i];
        }
        update_table[i]=current_node;
    }

    for(int i=new_level; i>=0; i--){
        new_node->next[i] = update_table[i]->next[i];
        update_table[i] -> next[i] = new_node;
    }
}

bool remove(SkipList l, int key){
    /* Removes selected key from SkipList
     * If key does not exist in the SkipList function will return false
     */
    SLNode ** update_table = new SLNode * [MAX_LEVEL];
    SLNode * current_node = l.head;
    for(int i=MAX_LEVEL-1; i>=0; i--){
        while(current_node->next[i]!= nullptr && current_node->next[i]->data<key){
            current_node=current_node->next[i];
        }
        update_table[i]=current_node;
    }
    if(update_table[0]->next[0]== nullptr || update_table[0]->next[0]->data!=key){
        return false;
    }
    SLNode* to_remove = update_table[0]->next[0];
    for(int i=to_remove->level; i>=0; i--){
        update_table[i]->next[i]=to_remove->next[i];
    }
    return true;
}

SLNode* find(SkipList l, int key){
    /*
     * Returns a Skip List Node with selected key
     * If the key is not present in Skip List a nullptr is returned
     */

    int current_level = MAX_LEVEL-1;
    SLNode* current_node = l.head;

    while (current_level >= 0){
        while(current_node->next[current_level]!= nullptr && current_node->next[current_level]->data <=key){
            if(current_node->next[current_level]->data==key){
                return current_node->next[current_level];
            }
            current_node= current_node->next[current_level];
        }
        current_level --;
    }
    return nullptr;
}

void printSkipList(SkipList l ){
    /*
     * Prints a representation of a SkipList
     */
    SLNode* current;
    SLNode* bottom;
    for(int i = MAX_LEVEL-1; i>=0; i--){
        current = l.head;
        bottom = l.head;

        while(current != nullptr){
            cout<< current->data;
            current = current->next[i];

            while(current!= nullptr && bottom!=current){
                cout<<"\t";
                bottom = bottom->next[0];
            }
        }
        cout<<"\n";
    }
}

string skipListToString(SkipList l ){
    /*
     * Creates a string that represents the SkipList
     * The string will be the same as result of printSkipList
     */
    string result = "";
    SLNode* current;
    SLNode* bottom;
    for(int i = MAX_LEVEL-1; i>=0; i--){
        current = l.head;
        bottom = l.head;

        while(current != nullptr){
            result += to_string(current->data);
            current = current->next[i];

            while(current!= nullptr && bottom!=current){
                result+="\t";
                bottom = bottom->next[0];
            }
        }
        result +="\n";
        return result;
    }
}


SkipList* skip_list_builder(int * k, int n){
    SkipList* list = new SkipList();
    for(int i=0; i<n; i++){
        insert(*list, k[i]);
    }
    return list;
}