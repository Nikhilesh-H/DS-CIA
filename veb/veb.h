#include <math.h>
#include <vector>

#include "map.h"

class VEBTree {
private:
  std::vector<VEBTree *> clusters;
  VEBTree *summary;
  int u_size;
  int min;
  int max;

  int high(int);
  int low(int);
  int index(int, int);
  int root(int);

public:
  VEBTree(int size) : u_size(size), min(-1), max(-1) {
    if (size > 2) {
      int cluster_size = root(size);
      summary = new VEBTree(cluster_size);
      clusters.resize(cluster_size);
      for (int i = 0; i < cluster_size; ++i) {
        clusters[i] = new VEBTree(cluster_size);
      }
    } else {
      summary = NULL;
    }
  }

  ~VEBTree() {
    for (int i = 0; i < clusters.size(); i++) {
      delete clusters[i];
    }
    delete summary;
  }

  void insert(int);
  void remove(int);
  int successor(int);
  int predecessor(int);
  int minimum();
  int maximum();
};

void VEBTree::insert(int x) {
  if (min == -1) {
    min = max = x;
    return;
  } else if (x < min) {
    std::swap(x, min);
  } else if (x > max) {
    max = x;
  } else {
    int high_x = high(x);
    if (clusters[high_x]->minimum() == -1) {
      summary->insert(high_x);
      clusters[high_x]->insert(low(x));
    } else {
      clusters[high_x]->insert(low(x));
    }
  }
}

void VEBTree::remove(int x) {
  if (min == -1) {
    return;
  }

  if (x == min) {
    int i = summary->minimum();
    if (i == -1) {
      min = max = -1;
      return;
    }
    x = min = index(i, clusters[i]->maximum());
  }

  clusters[high(x)]->remove(low(x));

  if (clusters[high(x)]->minimum() == -1) {
    summary->remove(high(x));
  }

  if (x == max) {
    if (summary->maximum() == -1) {
      max = min;
    } else {
      int i = summary->maximum();
      max = index(i, clusters[i]->maximum());
    }
  }
}

int VEBTree::successor(int num) {
  if (u_size == 2) {
    if (num == 0 && max == 1) {
      return 1;
    } else {
      return -1;
    }
  } else if (min != -1 && num < min) {
    return min;
  } else {
    int i = high(num);
    int j;
    if (low(num) < clusters[i]->maximum()) {
      j = clusters[i]->successor(low(num));
    } else {
      int succCluster = summary->successor(i);
      if (succCluster == -1) {
        return -1;
      }
      i = succCluster;
      j = clusters[succCluster]->minimum();
    }
    return index(i, j);
  }
}

int VEBTree::predecessor(int num) {
  if (u_size == 2) {
    if (num == 1 && min == 0) {
      return 0;
    } else {
      return -1;
    }
  } else if (max != -1 && num > max) {
    return max;
  } else {
    int i = high(num);
    int j;
    if (clusters[i] != NULL && low(num) > clusters[i]->minimum() &&
        clusters[i]->minimum() != -1) {
      j = clusters[i]->predecessor(low(num));
    } else {
      int predCluster = summary->predecessor(i);
      if (predCluster == -1) {
        if (min != -1 && num > min)
          return min;
        return -1;
      }
      i = predCluster;
      j = clusters[predCluster]->maximum();
    }
    return index(i, j);
  }
}

int VEBTree::minimum() {
  return min;
}

int VEBTree::maximum() {
  return max;
}

int VEBTree::high(int num) {
  return floor(num / root(u_size));
}

int VEBTree::low(int num) {
  return num % (int)root(u_size);
}

int VEBTree::index(int high, int low) {
  return high * root(u_size) + low;
}

int VEBTree::root(int num) {
  return pow(2, ceil(log2(num) / 2));
}
