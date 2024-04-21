#include <math.h>
#include <stdlib.h>

class VEBTree {
private:
  bool *bitvec;
  bool *summary;
  int u_size;

  int root(int);
  int index(int, int);
  int high(int);
  int low(int);

public:
  VEBTree(int size) : u_size(size) {
    bitvec = (bool *)malloc(sizeof(bool) * size);
    summary = (bool *)malloc(sizeof(bool) * root(size));

    for (int i = 0; i < size; i++) {
      bitvec[i] = false;
    }

    for (int i = 0; i < root(size); i++) {
      summary[i] = false;
    }
  }

  ~VEBTree() {
    free(bitvec);
    free(summary);
  }

  void insert(int);
  void remove(int);
  int successor(int);
  int predecessor(int);
  int minimum();
  int maximum();
};

int VEBTree::root(int num) {
  return pow(2, ceil(log2(num) / 2));
}

int VEBTree::index(int high, int low) {
  return high * root(u_size) + low;
}

int VEBTree::high(int num) {
  return floor(num / root(u_size));
}

int VEBTree::low(int num) {
  return num % root(u_size);
}

void VEBTree::insert(int num) {
  bitvec[num] = true;
  summary[high(num)] = true;
}

void VEBTree::remove(int num) {
  bitvec[num] = false;

  for (int i = 0; i < root(u_size); i++) {
    if (bitvec[index(high(num), i)]) {
      return;
    }
  }

  summary[high(num)] = false;
}

int VEBTree::successor(int num) {
  if (num < 0 || num >= u_size) {
    return -1;
  }

  int high_num = high(num);
  int low_num = low(num);
  int offset = low_num;

  while (offset < root(u_size)) {
    if (bitvec[index(high_num, offset)]) {
      return index(high_num, offset);
    }
    offset++;
  }

  for (int i = high_num + 1; i < root(u_size); i++) {
    if (summary[i]) {
      for (int j = 0; j < root(u_size); ++j) {
        if (bitvec[index(i, j)]) {
          return index(i, j);
        }
      }
    }
  }

  return -1;
}

int VEBTree::predecessor(int num) {
  if (num < 0 || num >= u_size) {
    return -1;
  }

  int high_num = high(num);
  int low_num = low(num);
  int offset = low_num;

  while (offset >= 0) {
    if (bitvec[index(high_num, offset)]) {
      return index(high_num, offset);
    }
    --offset;
  }

  for (int i = high_num - 1; i >= 0; --i) {
    if (summary[i]) {
      for (int j = root(u_size) - 1; j >= 0; --j) {
        if (bitvec[index(i, j)]) {
          return index(i, j);
        }
      }
    }
  }

  return -1;
}

int VEBTree::minimum() {
  for (int i = 0; i < root(u_size); i++) {
    if (summary[i]) {
      int cluster_min = i * root(u_size);
      for (int j = 0; j < root(u_size); j++) {
        if (bitvec[index(i, j)]) {
          return cluster_min + j;
        }
      }
    }
  }
  return -1;
}

int VEBTree::maximum() {
  for (int i = root(u_size) - 1; i >= 0; i--) {
    if (summary[i]) {
      int cluster_max = (i + 1) * root(u_size) - 1;
      for (int j = root(u_size) - 1; j >= 0; j--) {
        if (bitvec[index(i, j)]) {
          return cluster_max - (root(u_size) - 1 - j);
        }
      }
    }
  }
  return -1;
}
