//
// Created by Janusz Grzesik on 12.05.15.
//

#include "avl_trees.h"
#include <iostream>

using namespace std;


int main(int argc, const char * argv[]) {
    AVLNode* root = nullptr;

    AVL_insert(root, 2);
    AVL_insert(root, 3);
    AVL_insert(root, 4);
    AVL_insert(root, 1);
    AVL_insert(root, 1);
    AVL_insert(root, 5);
    AVL_insert(root, 6);
    AVL_insert(root, 11);
    AVL_insert(root, 12);
    AVL_insert(root, 23);
    AVL_insert(root, 45);
    AVL_insert(root, 74);
    cout<<avl_tree_to_string(root);
    return 0;
}