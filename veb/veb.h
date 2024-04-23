#include <math.h>
#include <vector>

#include "map.h"

class VEBTree {
private:
  std::vector<bool> bitvec;
  std::vector<VEBTree *> clusters;
  VEBTree *summary;
  int u_size;

  int high(int);
  int low(int);
  int index(int, int);

public:
  VEBTree(int size) {
    u_size = size;
    bitvec.resize(size);

    for (int i = 0; i < size; ++i) {
      bitvec[i] = false;
    }

    if (size > 2) {
      int cluster_size = sqrt(size);

      summary = new VEBTree(cluster_size);

      clusters.resize(cluster_size);

      for (int i = 0; i < cluster_size; ++i) {
        clusters[i] = new VEBTree(cluster_size);
      }
    } else {
      summary = nullptr;
    }
  }

  ~VEBTree() {
    for (int i = 0; i < clusters.size(); ++i) {
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

int VEBTree::high(int num) {
  return static_cast<int>(floor(num / sqrt(u_size)));
}

int VEBTree::low(int num) {
  return num % static_cast<int>(sqrt(u_size));
}

int VEBTree::index(int high, int low) {
  return high * static_cast<int>(sqrt(u_size)) + low;
}

void VEBTree::insert(int num) {
  if (u_size == 2) {
    bitvec[num] = true;
  } else {
    clusters[high(num)]->insert(low(num));
    summary->insert(high(num));
  }
}

void VEBTree::remove(int num) {
  if (u_size == 2) {
    bitvec[num] = false;
  } else {
    clusters[high(num)]->remove(low(num));
    if (clusters[high(num)]->minimum() == -1) {
      summary->remove(high(num));
    }
  }
}

int VEBTree::successor(int num) {
  int i = high(num);
  int j = clusters[i]->successor(low(num));

  if (j != -1) {
    return index(i, j);
  } else {
    int succCluster = summary->successor(i);
    if (succCluster == -1) {
      return -1; // No successor found
    } else {
      j = clusters[succCluster]->minimum();
      return index(succCluster, j);
    }
  }
}

int VEBTree::predecessor(int num) {
  if (u_size == 2) {
    if (num == 1 && bitvec[0]) {
      return 0;
    }
    return -1;
  } else {
    int min_low = clusters[high(num)]->minimum();
    if (min_low != -1 && low(num) > min_low) {
      int offset = clusters[high(num)]->predecessor(low(num));
      return index(high(num), offset);
    } else {
      int pred_cluster = summary->predecessor(high(num));
      if (pred_cluster == -1) {
        if (bitvec[0] && num > 0) {
          return 0;
        }
        return -1;
      }
      int offset = clusters[pred_cluster]->maximum();
      return index(pred_cluster, offset);
    }
  }
}

int VEBTree::minimum() {
  if (u_size == 2) {
    if (bitvec[0]) {
      return 0;
    } else if (bitvec[1]) {
      return 1;
    } else {
      return -1;
    }
  } else {
    int min_cluster = summary->minimum();
    if (min_cluster == -1) {
      return -1;
    }
    int offset = clusters[min_cluster]->minimum();
    return index(min_cluster, offset);
  }
}

int VEBTree::maximum() {
  if (u_size == 2) {
    if (bitvec[1]) {
      return 1;
    } else if (bitvec[0]) {
      return 0;
    } else {
      return -1;
    }
  } else {
    int max_cluster = summary->maximum();
    if (max_cluster == -1) {
      return -1;
    }
    int offset = clusters[max_cluster]->maximum();
    return index(max_cluster, offset);
  }
}
