# TODOS

- Incorporate use of hash table over vector to lower space complexity to O(n)
  than O(u)
- Construct a better hash table
    - Hashtable should use better hash function
    - Hashtable should resize properly
- Free memory properly on remove and exit
- Use C Features like malloc and free instead of new and delete
- Current Implementation has zero error checking. Negative numbers and numbers
  greater than VEBTree in main function break the program. Hence need more
  error checking. To achieve this, insert and delete might have to return true
  or falses
- Maybe try to increase the size of universe to uint64_t (ask team)
- Formatting style to use: `Microsoft`
- Search maybe?
- Order functions
- Replace std::swap with some other function
