#include <math.h>
#include <unordered_map>

using namespace std;

class VEBTree {
private:
  std::unordered_map<int, VEBTree *> clusters;
  VEBTree *summary;
  int u_size;
  int min, max;

  int high(int);
  int low(int);
  int index(int, int);
  int root(int);

public:
  VEBTree(int size) : u_size(size), min(-1), max(-1), summary(nullptr) {
    if (size > 2) {
      int cluster_size = root(size);
      summary = new VEBTree(cluster_size);
    }
  }

  ~VEBTree() {
    for (auto &cluster : clusters) {
      delete cluster.second;
    }
    clusters.clear();

    delete summary;
  }

  void insert(int);
  void remove(int);
  bool search(int);
  int successor(int);
  int predecessor(int);
  int getmin();
  int getmax();
};

void VEBTree::insert(int num) {
  if (min == -1) {
    min = max = num;
    return;
  }
  if (num < min) {
    int tmp = num;
    num = min;
    min = tmp;
  }
  if (num > max) {
    max = num;
  }
  int high_x = high(num);
  if (clusters.find(high_x) == clusters.end()) {
    summary->insert(high_x);
    clusters[high_x] = new VEBTree(root(u_size));
  }
  clusters[high_x]->insert(low(num));
}

void VEBTree::remove(int num) {
  if (min == max) {
    min = max = -1;
  } else if (u_size == 2) {
    if (num == 0) {
      min = max = 1;
    } else {
      min = max = 0;
    }
  } else {
    if (num == min) {
      int summary_min = summary->getmin();
      if (summary_min == -1) {
        min = max = -1;
        return;
      }
      int cluster_max = clusters[summary_min]->getmax();
      if (cluster_max == -1) {
        min = max = -1;
        return;
      }
      min = index(summary_min, cluster_max);
      num = min;
    }

    int high_x = high(num);
    VEBTree *cluster_node = clusters[high_x];
    cluster_node->remove(low(num));

    if (cluster_node->getmin() == -1) {
      clusters.erase(high_x);
      summary->remove(high_x);
    }

    if (num == max) {
      int summary_max = summary->getmax();
      if (summary_max == -1) {
        max = min;
      } else {
        int cluster_max = clusters[summary_max]->getmax();
        if (cluster_max == -1) {
          max = min;
        } else {
          max = index(summary_max, cluster_max);
        }
      }
    }
  }
}

bool VEBTree::search(int x) {
  if (min == -1) {
    return false;
  }

  if (x == min || x == max) {
    return true;
  }

  if (u_size <= 2) {
    return false;
  }

  VEBTree *cluster = clusters[high(x)];
  if (cluster == nullptr) {
    return false;
  } else {
    return cluster->search(low(x));
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

    if (clusters[i] != nullptr && low(num) < clusters[i]->max) {
      j = clusters[i]->successor(low(num));
    } else if (summary != nullptr) {
      i = summary->successor(i);
      if (i != -1 && clusters[i] != nullptr) {
        j = clusters[i]->getmin();
      } else {
        return -1;
      }
    } else {
      return -1;
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

    if (clusters[i] != nullptr && low(num) > clusters[i]->min) {
      j = clusters[i]->predecessor(low(num));
    } else {
      i = summary->predecessor(i);
      if (i == -1) {
        if (min != -1 && num > min) {
          return min;
        } else {
          return -1;
        }
      }
      j = clusters[i]->max;
    }

    return index(i, j);
  }
}

int VEBTree::getmin() {
  return min;
}

int VEBTree::getmax() {
  return max;
}

int VEBTree::high(int num) {
  return floor(num / root(u_size));
}

int VEBTree::low(int num) {
  return num % root(u_size);
}

int VEBTree::index(int high, int low) {
  return high * root(u_size) + low;
}

int VEBTree::root(int num) {
  return pow(2, ceil(log2(num) / 2));
}
