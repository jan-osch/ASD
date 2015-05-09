//
//  main.cpp
//  DrzewaTest
//
//  Created by Janusz Grzesik on 20.04.2015.
//  Copyright (c) 2015 Janusz Grzesik. All rights reserved.
//


#include "../Drzewa/drzewa.h"
#include <iostream>
#include <gtest/gtest.h>


TEST (insertTest,insertToEmptyTree)
{
    node* root = nullptr;
    root=insert(root, 5);
    
    // root -> key is now 5
    EXPECT_EQ(5,root->key);
    
    // left == nullpt
    EXPECT_EQ(NULL, root->left);

    // right == nullptr
    EXPECT_EQ(nullptr,root->left);

    // parent == nullptr
    EXPECT_EQ(nullptr, root->parent);
}

TEST (insertTest,insertToNonEmptyTree)
{
    node* root = new node(5);
    root =insert(root, 5);
    
    EXPECT_EQ(5,root->right->key);
    
    EXPECT_EQ(NULL, root->left);
    
    EXPECT_EQ(root, root->right->parent);
}

TEST (isLeafTest,labelSmallTree)
{
    node* root = new node(5);
    root = insert(root, 2);
    
    EXPECT_FALSE(isLeaf(root));
    
    EXPECT_TRUE(isLeaf(root->left));
}

TEST (treeBuilderTest,buildSmallTree)
{
    int arr[] = {2,1,3,4};
    node* root = treeBuilder(arr, 4);
    
    EXPECT_EQ(2, root->key);
    
    EXPECT_EQ(1, root->left->key);
    
    EXPECT_EQ(3, root->right->key);
    
    EXPECT_EQ(4, root->right->right->key);
    
    EXPECT_TRUE(isLeaf(root->right->right));

}

TEST (printInOrderTest,printSmallTree)
{
    int arr[] = {2,1,3,4};
    node* root = treeBuilder(arr, 4);
    
    /* Expected tree structure
            4
        3
     2
        1
     
     */
    
    string actual = printInOrder(root);
    string expected = "1\n2\n3\n4\n";
    
    EXPECT_EQ(actual,expected);
}

TEST (printInOrderRecursivelyTest,printSmallTree)
{
    int arr[] = {2,1,3,4};
    /* Expected tree structure
            4
        3
     2
        1
     
     */
    node* root = treeBuilder(arr, 4);
    
    string actual = printInOrderRecursively(root);
    string expected = "1\n2\n3\n4\n";
    
    EXPECT_EQ(actual,expected);
}

TEST (findMinTest,findMinimumInSmallTree)
{
    int arr[] = {2,1,3,4};
    /* Expected tree structure
                4
            3
        2
            1
     
     */
    node* root = treeBuilder(arr, 4);
    
    EXPECT_EQ(1, findMin(root));
    
    EXPECT_EQ(1, findMin(root->left));
    
    EXPECT_EQ(3, findMin(root->right));
}

TEST (findMaxTest,findMaximumInSmallTree)
{
    int arr[] = {2,1,3,4};
    node* root = treeBuilder(arr, 4);
    
    EXPECT_EQ(4, findMax(root));
    
    EXPECT_EQ(1, findMax(root->left));
    
    EXPECT_EQ(4, findMax(root->right));
}

TEST (findSuccessor,findSuccessorInSmallTree)
{
    int arr[] = {3,1,2,4};
    node* root = treeBuilder(arr, 4);
    /* Expected tree structure
        4
     3
            2
        1
     
     */
  
    EXPECT_EQ(4, findSuccessor(root)->key);
    
    EXPECT_EQ(2, findSuccessor(root->left)->key);
    
    EXPECT_EQ(nullptr, findSuccessor(root->right));
    
    EXPECT_EQ(3, findSuccessor(root->left->right)->key);
}

TEST (findPredecessor,findPredecessorInSmallTree)
{
    int arr[] = {3,1,2,4};
    node* root = treeBuilder(arr, 4);
    /* Expected tree structure
        4
     3
            2
        1
     
     */
    
    EXPECT_EQ(4, findSuccessor(root)->key);
    
    EXPECT_EQ(2, findSuccessor(root->left)->key);
    
    EXPECT_EQ(nullptr, findSuccessor(root->right));
    
    EXPECT_EQ(3, findSuccessor(root->left->right)->key);
}

TEST (remove_from_tree, removeFromTreeExampleCormenPolishPage292){
    int arr[] = {15,16,20,18,23,5,3,12,13,10,6,7};
    node* my_tree_leaf = treeBuilder(arr,12);
    node* my_tree_single_son = treeBuilder(arr,12);
    node* my_tree_two_sons = treeBuilder(arr,12);

    node* leaf_to_remove = find_node_by_key(my_tree_leaf,13);
    node* single_son_to_remove = find_node_by_key(my_tree_single_son,16);
    node* two_sons_to_remove = find_node_by_key(my_tree_two_sons,5);

    remove_from_tree(my_tree_leaf, leaf_to_remove);
    remove_from_tree(my_tree_single_son, single_son_to_remove);
    remove_from_tree(my_tree_two_sons, two_sons_to_remove);

    EXPECT_EQ(nullptr,find_node_by_key(my_tree_leaf, 12)->right);
    EXPECT_EQ(nullptr,find_node_by_key(my_tree_leaf, 13));

    EXPECT_EQ(20,find_node_by_key(my_tree_single_son, 15)->right->key);
    EXPECT_EQ(nullptr,find_node_by_key(my_tree_single_son, 16));

    EXPECT_EQ(6,find_node_by_key(my_tree_two_sons, 15)->left->key);
    EXPECT_EQ(nullptr,find_node_by_key(my_tree_two_sons, 5));

}

int main(int argc, char * argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}