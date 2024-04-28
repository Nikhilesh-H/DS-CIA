#include <gtest/gtest.h>

#include "treap.h"

treap t;

// Test Case 1 - Inserting a Node
TEST(InsertNode, InsertingNode) {
  EXPECT_EQ(t.insert(10, 100), true);
}

// Test Case 2 - Inserting Duplicate Key
TEST(InsertNode, InsertingDuplicateKey) {
  EXPECT_EQ(t.insert(10, 100), true);
}

// Test Case 3 - Inserting Multiple Nodes
TEST(InsertNode, InsertingMultipleNodes) {
  EXPECT_EQ(t.insert(5, 50), true);
  EXPECT_EQ(t.insert(15, 150), true);
  EXPECT_EQ(t.insert(3, 30), true);
  EXPECT_EQ(t.insert(7, 70), true);
  EXPECT_EQ(t.insert(12, 120), true);
  EXPECT_EQ(t.insert(17, 170), true);
}

// Test Case 1 - Deleting a Leaf Node
TEST(DeleteNode, DeleteLeafNode) {
  EXPECT_NE(t.del(3), nullptr);
}

// Test Case 2 - Deleting a Node with One Child
TEST(DeleteNode, DeleteNodeWithOneChild) {
  EXPECT_NE(t.del(15), nullptr);
}

// Test Case 3 - Deleting a Node with Two Children
TEST(DeleteNode, DeleteNodeWithTwoChildren) {
  EXPECT_NE(t.del(10), nullptr);
}

// Test Case 1 - Searching for an Existing Key
TEST(SearchNode, SearchingExistingKey) {
  EXPECT_EQ(t.search(7), true);
}

// Test Case 2 - Searching for a Non-Existing Key
TEST(SearchNode, SearchingNonExistingKey) {
  EXPECT_EQ(t.search(20), false);
}

// Test Case 3 - Searching in an Empty Treap
TEST(SearchNode, SearchingInEmptyTreap) {
  treap t;
  EXPECT_EQ(t.search(5), false);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
