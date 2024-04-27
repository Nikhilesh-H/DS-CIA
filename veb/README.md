# TODOS

## High priority

- Free memory properly (shucks)
- Maybe try to increase the size of universe to uint64_t (ask team)
- Formatting style to use: `Microsoft`
- Find way to reduce space from O(n log log u) to O(n)

## Low Priority

- Construct a better hash table
    - Hashtable should use better hash function
    - Hashtable should resize properly
- Current Implementation has zero error checking. Negative numbers and numbers
  greater than VEBTree in main function break the program. Hence need more
  error checking. To achieve this, insert and delete might have to return true
  or falses

# Note

## Time

- Insertion: O(log log u)
- Deletion: O(log log u)
- Predecessor: O(log log u)
- Successor: O(log log u)
- Min: O(1)
- Max: O(1)

## Space

- O(n log log u)

## Ideas

- Only create nonempty clusters
    – If V.min becomes None, deallocate V
- Each insert may create a new structure Θ(log log u) times (each empty insert)
    – Can actually happen
- Charge pointer to structure (and associated hash table entry) to the structure
This gives us O(n log log u) space (but randomized).

## Indirection

We can further reduce to O(n) space.
- Store vEB structure with n = O(log log u) using BST or even an array
> O(log log n) time once in base case
- We use O(n/ log log u) such structures (disjoint)
> O( · log log u) = O(n) space for smalllog log u
- Larger structures “store” pointers to them
> O( · log log u) = O(n) space for largelog log u
- Details: Split/Merge small structures
