#include <stdlib.h>

class VEBTree;

class Node {
public:
  int key;
  VEBTree *value;
  Node *next;
};

class HashMap {
private:
  float LOAD_FACTOR_THRESHOLD = 0.75;

  int size;
  int capacity;
  Node **table;

  int hash(int key);
  void resize();
  void clear(Node *node);

public:
  HashMap() {
    size = 0;
    capacity = 0;
    table = nullptr;
  }

  ~HashMap() {
    if (table) {
      for (int i = 0; i < capacity; i++) {
        clear(table[i]);
      }
      free(table);
    }
  }

  void insert(int, VEBTree *);
  void remove(int);
  VEBTree *get(int);
};

VEBTree *HashMap::get(int key) {
  if (capacity == 0) {
    return nullptr;
  }
  int index = hash(key);
  Node *current = table[index];
  while (current) {
    if (current->key == key) {
      return current->value;
    }
    current = current->next;
  }
  return nullptr;
}

void HashMap::insert(int key, VEBTree *value) {
  if (capacity == 0) {
    resize();
  }

  int index = hash(key);

  Node *current = table[index];
  while (current) {
    if (current->key == key) {
      free(current->value);
      current->value = value;
      return;
    }
    current = current->next;
  }

  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->key = key;
  newNode->value = value;
  newNode->next = table[index];
  table[index] = newNode;
  size++;

  if ((float)size / capacity > LOAD_FACTOR_THRESHOLD) {
    resize();
  }
}

void HashMap::remove(int key) {
  int index = hash(key);
  Node *current = table[index];
  Node *prev = nullptr;

  while (current) {
    if (current->key == key) {
      if (prev) {
        prev->next = current->next;
      } else {
        table[index] = current->next;
      }
      free(current->value);
      free(current);
      size--;
      return;
    }
    prev = current;
    current = current->next;
  }
}

void HashMap::resize() {
  int newCapacity = capacity == 0 ? 1 : capacity * 2;
  Node **newTable = (Node **)malloc(newCapacity * sizeof(Node *));
  if (!newTable) {
    return;
  }

  for (int i = 0; i < newCapacity; i++) {
    newTable[i] = nullptr;
  }

  for (int i = 0; i < capacity; i++) {
    Node *current = table[i];
    while (current) {
      Node *next = current->next;
      int newIndex = hash(current->key) % newCapacity;
      current->next = newTable[newIndex];
      newTable[newIndex] = current;
      current = next;
    }
  }

  free(table);

  capacity = newCapacity;
  table = newTable;
}

void HashMap::clear(Node *node) {
  while (node) {
    Node *next = node->next;
    free(node->value);
    free(node);
    node = next;
  }
}

int HashMap::hash(int key) {
  return key % capacity;
}
