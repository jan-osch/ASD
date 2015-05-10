#include <iostream>
#include "drzewa.h"

using namespace std;

int main(int argc, const char * argv[]) {
    int arr[] = {15,16,20,18,23,5,3,12,13,10,6,7};
    node* my_tree = treeBuilder(arr,12);
    cout<< tree_to_string_with_tabs(my_tree);
    cout<<"\n AFTRER DELETING\n";
    node* to_remove = find_node_by_key(my_tree,5);

    remove_from_tree(my_tree, to_remove);
    cout<< tree_to_string_with_tabs(my_tree);
}
