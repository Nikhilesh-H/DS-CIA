#include <gtest/gtest.h>

#include "treap.h"

Treap t;

// Test Case 1 - Inserting a Node
TEST(InsertNode, InsertingNode)
{
    EXPECT_EQ(t.insert(10, 100), true);
}

// Test Case 2 - Inserting Duplicate Key
TEST(InsertNode, InsertingDuplicateKey)
{
    EXPECT_EQ(t.insert(10, 100), true);
}

// Test Case 3 - Inserting Multiple Nodes
TEST(InsertNode, InsertingMultipleNodes)
{
    EXPECT_EQ(t.insert(5, 50), true);
    EXPECT_EQ(t.insert(15, 150), true);
    EXPECT_EQ(t.insert(3, 30), true);
    EXPECT_EQ(t.insert(7, 70), true);
    EXPECT_EQ(t.insert(12, 120), true);
    EXPECT_EQ(t.insert(17, 170), true);
}

// Test Case 4 - Deleting a Leaf Node
TEST(DeleteNode, DeleteLeafNode)
{
    EXPECT_EQ(t.del(3), true);
}

// Test Case 5 - Deleting a Node with One Child
TEST(DeleteNode, DeleteNodeWithOneChild)
{
    EXPECT_EQ(t.del(15), true);
}

// Test Case 6 - Deleting a Node with Two Children
TEST(DeleteNode, DeleteNodeWithTwoChildren)
{
    EXPECT_EQ(t.del(10), true);
}

// Test Case 7 - Searching for an Existing Key
TEST(SearchNode, SearchingExistingKey)
{
    EXPECT_EQ(t.search(7), true);
}

// Test Case 8 - Searching for a Non-Existing Key
TEST(SearchNode, SearchingNonExistingKey)
{
    EXPECT_EQ(t.search(20), false);
}

// Test Case 9 - Searching in an Empty Treap
TEST(SearchNode, SearchingInEmptyTreap)
{
    Treap tree;
    EXPECT_EQ(tree.search(5), false);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
