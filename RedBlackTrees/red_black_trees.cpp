//
// Created by Janusz Grzesik on 09.05.15.
//

#include "red_black_trees.h"
int main(int argc, const char * argv[]) {
    RedBlackNode *mytree = new RedBlackNode(10, 'B');
    red_black_insert(mytree,12);
    red_black_insert(mytree,11);
    red_black_insert(mytree,100);
    red_black_insert(mytree,95);
    red_black_insert(mytree,25);
    red_black_insert(mytree,55);
    red_black_insert(mytree,16);

//    insert_BST_style(mytree,12);
//    insert_BST_style(mytree,11);
    cout<<tree_to_string_with_tabs(mytree);

    return 0;
}