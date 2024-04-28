#include <stdio.h>
#include <stdlib.h>
#include "treap.h"

void assert(bool test, const char* desc) {
    if (test) {
        printf("Test case passed: %s\n", desc);
    } else {
        printf("Test case failed: %s\n", desc);
    }
}

int main() {
    treap t;

    // Test Case 1 - Inserting a Node
    assert(t.insert(10, 100), "Inserting a Node");

    // Test Case 2 - Inserting Duplicate Key
    assert(t.insert(10, 200) != NULL, "Inserting Duplicate Key");  

    // Test Case 3 - Inserting Multiple Nodes
    assert(t.insert(5, 50), "Inserting Multiple Nodes (1)");
    assert(t.insert(15, 150), "Inserting Multiple Nodes (2)");
    assert(t.insert(3, 30), "Inserting Multiple Nodes (3)");
    assert(t.insert(7, 70), "Inserting Multiple Nodes (4)");
    assert(t.insert(12, 120), "Inserting Multiple Nodes (5)");
    assert(t.insert(17, 170), "Inserting Multiple Nodes (6)");

    // Test Case 1 - Deleting a Leaf Node
    assert(t.del(3, t.getroot()), "Deleting a Leaf Node");

    // Test Case 2 - Deleting a Node with One Child
    assert(t.del(15, t.getroot()), "Deleting a Node with One Child");

    // Test Case 3 - Deleting a Node with Two Children
    assert(t.del(10, t.getroot()), "Deleting a Node with Two Children");

    // Test Case 1 - Searching for an Existing Key
    assert(t.search(7, t.getroot()) == 1, "Searching for an Existing Key");

    // Test Case 2 - Searching for a Non-Existing Key
    assert(t.search(20, t.getroot()) == 0, "Searching for a Non-Existing Key");

    // Test Case 3 - Searching in an Empty Treap
    t.~treap();
    assert(t.search(5, t.getroot()) == 0, "Searching in an Empty Treap");

    return 0;
}
