//
// Created by Janusz Grzesik on 10.05.15.
//

#include "sum_tree.h"
int main(int argc, const char * argv[]) {
//    PositionNode *my_tree = new PositionNode(8, nullptr);
//    create_new_node_by_key(my_tree, 4);
//    create_new_node_by_key(my_tree, 2);
//    create_new_node_by_key(my_tree, 1);
//    create_new_node_by_key(my_tree, 3);
//    create_new_node_by_key(my_tree, 6);
//    create_new_node_by_key(my_tree, 5);
//    create_new_node_by_key(my_tree, 7);
//    compute_ranks(get_node_at_position(my_tree,7));
//    cout << position_tree_to_string_with_tabs(my_tree);
////    cout << "\n"<< get_node_at_position(my_tree,6)->key<<"\n";


    SumTreeNode* my_tree = nullptr;
    insert_sum_node(my_tree, 10);
    insert_sum_node(my_tree, 5);
    insert_sum_node(my_tree, 7);
    insert_sum_node(my_tree, 4);
    insert_sum_node(my_tree, 12);
    insert_sum_node(my_tree, 11);
    insert_sum_node(my_tree, 30);
    cout<<sum_tree_to_string(my_tree);
    cout<<"\n"<<query(my_tree, 29, 31);


    return 0;
}