#include <vector>

class VEBTree {
private:
  std::vector<bool> bitvec;

public:
  VEBTree(int size) {
    bitvec.resize(size);

    for (int i = 0; i < size; i++) {
      bitvec[i] = false;
    }
  }

  void insert(int);
  void remove(int);
  int successor(int);
  int predecessor(int);
  int minimum();
  int maximum();
};

void VEBTree::insert(int num) {
  bitvec[num] = true;
}

void VEBTree::remove(int num) {
  bitvec[num] = false;
}

int VEBTree::successor(int num) {
  for (int i = num + 1; i < bitvec.size(); i++) {
    if (bitvec[i]) {
      return i;
    }
  }

  return -1;
}

int VEBTree::predecessor(int num) {
  for (int i = num - 1; i >= 0; i--) {
    if (bitvec[i]) {
      return i;
    }
  }

  return -1;
}

int VEBTree::minimum() {
  for (int i = 0; i < bitvec.size(); i++) {
    if (bitvec[i]) {
      return i;
    }
  }

  return -1;
}

int VEBTree::maximum() {
  for (int i = bitvec.size() - 1; i >= 0; i--) {
    if (bitvec[i]) {
      return i;
    }
  }

  return -1;
}
