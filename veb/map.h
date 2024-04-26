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

  int hash(int);
  void resize();

public:
  HashMap() : size(0), capacity(0), table(NULL) {}

  ~HashMap() {
    if (table != NULL) {
      for (int i = 0; i < capacity; i++) {
        Node *current = table[i];
        while (current) {
          Node *next = current->next;
          // TODO Free the VEBTree here
          free(current->value);
          free(current);
          current = next;
        }
      }
      free(table);
    }
  }

  VEBTree *get(int);
  void insert(int, VEBTree *);
  void remove(int);
  void clear();
};

VEBTree *HashMap::get(int key) {
  if (capacity == 0) {
    return NULL;
  }

  int index = hash(key);

  Node *current = table[index];
  while (current) {
    if (current->key == key) {
      return current->value;
    }
    current = current->next;
  }

  return NULL;
}

void HashMap::insert(int key, VEBTree *value) {
  if (capacity == 0) {
    resize();
  }

  int index = hash(key);

  Node *current = table[index];
  while (current) {
    if (current->key == key) {
      // TODO Free the already existing VEBTree here
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
  Node *prev = NULL;

  while (current) {
    if (current->key == key) {
      if (prev) {
        prev->next = current->next;
      } else {
        table[index] = current->next;
      }
      // TODO Don't think its getting freed properly
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

  for (int i = 0; i < newCapacity; i++) {
    newTable[i] = NULL;
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

// TODO Clear table
void HashMap::clear() {}

int HashMap::hash(int key) {
  return key % capacity;
}
