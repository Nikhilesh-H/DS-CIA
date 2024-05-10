#include <gtest/gtest.h>

#include "veb.h"

#define SIZE 65536

// Test Case 1 - Inserting a value
TEST(Insert, InsertValue)
{
    VEBTree veb(SIZE);

    veb.insert(3);
    veb.insert(10);

    EXPECT_EQ(veb.getmin(), 3);
    EXPECT_EQ(veb.getmax(), 10);
    EXPECT_EQ(veb.search(3), true);
    EXPECT_EQ(veb.search(10), true);
}

// Test Case 2 - Inserting many values
TEST(Insert, InsertingManyValues)
{
    VEBTree veb(SIZE);

    for (int i = 0; i < 10000; i++)
    {
        veb.insert(i);
    }

    EXPECT_EQ(veb.getmin(), 0);
    EXPECT_EQ(veb.getmax(), 9999);

    int count = 0;
    for (int i = 0; i < 10000; i++)
    {
        if (veb.search(i))
        {
            count++;
        }
    }
    EXPECT_EQ(count, 10000);

    count = 0;
    for (int i = 10000; i < 20000; i++)
    {
        if (veb.search(i))
        {
            count++;
        }
    }
    EXPECT_EQ(count, 0);
}

// Test Case 3 - Inserting duplicates
TEST(Insert, InsertDuplicates)
{
    VEBTree veb(SIZE);

    for (int i = 0; i < 10000; i++)
    {
        veb.insert(1);
    }

    EXPECT_EQ(veb.getmin(), 1);
    EXPECT_EQ(veb.getmax(), 1);
}

// Test Case 4 - Delete a value
TEST(Delete, DeleteValue)
{
    VEBTree veb(SIZE);

    veb.insert(3);
    veb.insert(5);
    veb.insert(10);
    veb.insert(15);

    veb.remove(3);
    veb.remove(15);

    EXPECT_EQ(veb.getmin(), 5);
    EXPECT_EQ(veb.getmax(), 10);
}

// Test Case 5 - Delete an already deleted value
TEST(Delete, DeleteValueAgain)
{
    VEBTree veb(SIZE);

    veb.insert(3);
    veb.insert(5);
    veb.insert(10);
    veb.insert(15);

    veb.remove(3);
    veb.remove(15);

    EXPECT_EQ(veb.getmin(), 5);
    EXPECT_EQ(veb.getmax(), 10);

    veb.remove(3);
    veb.remove(15);

    EXPECT_EQ(veb.getmin(), 5);
    EXPECT_EQ(veb.getmax(), 10);
}

// Test Case 5 - Delete an already deleted value
TEST(Delete, DeleteMultiple)
{
    VEBTree veb(SIZE);

    for (int i = 0; i < 10000; i++)
    {
        veb.remove(i);
    }

    EXPECT_EQ(veb.getmin(), -1);
    EXPECT_EQ(veb.getmax(), -1);

    veb.insert(1);

    for (int i = 0; i < 10000; i++)
    {
        veb.remove(i);
    }

    EXPECT_EQ(veb.getmin(), -1);
    EXPECT_EQ(veb.getmax(), -1);

    veb.remove(3);
    veb.remove(15);

    for (int i = 0; i < 10000; i++)
    {
        veb.remove(1);
    }

    EXPECT_EQ(veb.getmin(), -1);
    EXPECT_EQ(veb.getmax(), -1);
}

// Test Case 7 - Find successors
TEST(Successor, FindSuccessor)
{
    VEBTree veb(SIZE);

    veb.insert(3);
    veb.insert(5);
    veb.insert(10);
    veb.insert(15);

    EXPECT_EQ(veb.successor(1), 3);
    EXPECT_EQ(veb.successor(5), 10);
    EXPECT_EQ(veb.successor(15), -1);
}

// Test Case 8 - Find predecessor
TEST(Predecessor, FindPredecessor)
{
    VEBTree veb(SIZE);

    veb.insert(3);
    veb.insert(5);
    veb.insert(10);
    veb.insert(15);

    EXPECT_EQ(veb.predecessor(1), -1);
    EXPECT_EQ(veb.predecessor(3), -1);
    EXPECT_EQ(veb.predecessor(5), 3);
    EXPECT_EQ(veb.predecessor(20), 15);
}

// Test Case 9 - Search
TEST(Search, SearchValue)
{
    VEBTree veb(SIZE);

    veb.insert(5);
    veb.insert(10);
    veb.insert(3);
    veb.insert(15);

    EXPECT_EQ(veb.search(5), true);
    EXPECT_EQ(veb.search(10), true);
    EXPECT_EQ(veb.search(20), false);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
