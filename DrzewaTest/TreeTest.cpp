//
//  main.cpp
//  DrzewaTest
//
//  Created by Janusz Grzesik on 20.04.2015.
//  Copyright (c) 2015 Janusz Grzesik. All rights reserved.
//


#include "../Drzewa/Drzewa.h"
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

void moveArrayInPlace(int array[], int n, int k){
    
    
}

int main(int argc, char * argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}