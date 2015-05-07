//
//  main.cpp
//  DrzewaTest
//
//  Created by Janusz Grzesik on 20.04.2015.
//  Copyright (c) 2015 Janusz Grzesik. All rights reserved.
//


#include "../SkipListy/skip_listy.h"
#include "../DrzewaTest/gtest-1.7.0/include/gtest/gtest.h"
#include <iostream>

#define MAX_LEVEL = 10

TEST (insertTest,insertToEmptyTree)
{
    SLNode* root =  new SLNode(1);

    EXPECT_EQ(5,root->key);
    
    // left == nullpt
    EXPECT_EQ(NULL, root->left);

    // right == nullptr
    EXPECT_EQ(nullptr,root->left);

    // parent == nullptr
    EXPECT_EQ(nullptr, root->parent);
}

int main(int argc, char * argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}