//
// Created by Janusz Grzesik on 10.05.15.
//

#include <iostream>
#include "../Drzewa/drzewa.h"

using namespace std;

struct PositionNode{
    int key;
    int rank;
    int size;
    PositionNode* parent;
    PositionNode* left;
    PositionNode* right;

    PositionNode(int k, PositionNode* par){
        key = k;
        size= 1;
        rank = 0;
        left= nullptr;
        right= nullptr;
        parent=par;
    };
};

void create_new_node_by_key(PositionNode* &root, int key_to_create){
    if(root== nullptr){
        root = new PositionNode(key_to_create, nullptr);
        return;
    }
    if(root->key>key_to_create){
        create_new_node_by_key(root->left, key_to_create);
        root->left->parent=root;
        root->size++;
        return;
    }
    create_new_node_by_key(root->right, key_to_create);
    root->right->parent=root;
    root->size++;
}

PositionNode* get_node_at_position(PositionNode* root, int position){
    // Returns the node at the i-th position in the tree
    // The first position in the tree is 1 and it represents the smallest element
    // If given position does not exist in the tree nullptr is returned

    if(root== nullptr){
        return root; // Valid exit
    }
    if(root->left== nullptr && position==1){
        return root;
    }
    if(root->left== nullptr){
        return get_node_at_position(root->right, position-1);
    }
    if(root->left->size==position-1){
        return root;    // Valid exit
    }
    if( root->left->size < position ) {
        return get_node_at_position(root->right, position - root->left->size -1);
    }
    return get_node_at_position(root->left, position);
}

string position_tree_to_string_with_tabs(PositionNode * root){
    if(root==nullptr){
        return "";
    }
    string result=position_tree_to_string_with_tabs(root->right);
    replaceAll(result,"\n","\n\t");
    result+="\n"+to_string(root->key)+"|"+to_string(root->rank);
    string result2=position_tree_to_string_with_tabs(root->left);
    replaceAll(result2,"\n","\n\t");
    result+=result2;
    return result;
}

void compute_ranks(PositionNode* root){
    if(root== nullptr){
        return;
    }
    int new_rank=1;
    if(root->left!= nullptr) {
        new_rank += root->left->size;
    }
    PositionNode* current = root;
    while(current->parent!= nullptr){
        if(current == current->parent->right && current->parent->left!= nullptr){
            new_rank+=current->parent->left->size +1;
        }
        current=current->parent;
    }
    root->rank=new_rank;
}

