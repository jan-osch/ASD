//
// Created by Janusz Grzesik on 12.05.15.
//

#ifndef ASD_SUM_TREE_H
#define ASD_SUM_TREE_H

#endif //ASD_SUM_TREE_H

#include <iostream>
#include "wzbogacone_drzewa.h"
using namespace std;


struct SumTreeNode{
    int key;
    int sum;
    SumTreeNode * left;
    SumTreeNode * right;
    SumTreeNode * parent;


    SumTreeNode(int key) : key(key) {
        left= nullptr;
        right= nullptr;
        parent= nullptr;
        sum = key;
    }
};

void compute_sum(SumTreeNode* node){
    int left_sum=0;
    int right_sum=0;
    if(node->left!= nullptr){
        left_sum=node->left->sum;
    }
    if(node->right!= nullptr){
        right_sum=node->right->sum;
    }
    node->sum = left_sum + right_sum + node->key;
}

void insert_sum_node(SumTreeNode* &root, int key_to_insert){
    if(root== nullptr){
        root=new SumTreeNode(key_to_insert);
        return;
    }
    if(root->key>key_to_insert){
        insert_sum_node(root->left, key_to_insert);
        root->left->parent=root;
        root->sum+=key_to_insert;
        return;
    }
    insert_sum_node(root->right, key_to_insert);
    root->right->parent=root;
    root->sum+=key_to_insert;
    return;
}

string sum_tree_to_string(SumTreeNode * root){
    if(root==nullptr){
        return "";
    }
    string result=sum_tree_to_string(root->right);
    replaceAll(result,"\n","\n\t");
    result+="\n"+to_string(root->key)+"|"+to_string(root->sum);
    string result2=sum_tree_to_string(root->left);
    replaceAll(result2,"\n","\n\t");
    result+=result2;
    return result;
}

int query(SumTreeNode* root, int x, int y) {
    SumTreeNode *left_border = root;
    SumTreeNode *right_border = root;

    int result = root->sum;
    while (left_border->left != nullptr && left_border->right != nullptr) {
        if(left_border->key<x){
            result -= left_border->key;
            if(left_border->left!= nullptr){
                result-=left_border->left->sum;
            }
            left_border=left_border->right;
        }else if(left_border->key==x){
            if(left_border->left!= nullptr){
                result-=left_border->left->sum;
            }
            break;
        }
        else{
            left_border=left_border->left;
        }
    }
    while (right_border->left != nullptr && right_border->right != nullptr) {
        if(right_border->key>y) {
            result -= right_border->key;
            if(right_border->right!= nullptr){
                result-=right_border->right->sum;
            }
            right_border=right_border->left;
        }else if(right_border->key==y){
            if(right_border->right!= nullptr){
                result-=right_border->right->sum;
            }
            break;
        }else{
            right_border=right_border->right;
        }
    }
    return result;
}