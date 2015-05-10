//
// Created by Janusz Grzesik on 10.05.15.
//

#include <iostream>
#include "../Drzewa/drzewa.h"

using namespace std;

struct PositionNode{
    int key;
    int rank;
    PositionNode* parent;
    PositionNode* left;
    PositionNode* right;

    PositionNode(int k, PositionNode* par){
        key = k;
        rank= 1;
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
        root->rank++;
        return;
    }
    create_new_node_by_key(root->right, key_to_create);
    root->rank++;
}

PositionNode* get_node_at_position(PositionNode* root, int position){
    // Returns the node at the i-th position in the tree
    // The first position in the tree is 1 and it represents the smallest element
    // If given position does not exist in the tree nullptr is returned

    if(root== nullptr || position==1){
        return root; // Valid exit
    }
    if(root->left== nullptr){
        return get_node_at_position(root->right, position-1);
    }
    if(root->left->rank==position-1){
        return root;    // Valid exit
    }
    if( root->left->rank < position ) {
        return get_node_at_position(root->right, position - root->left->rank -1);
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