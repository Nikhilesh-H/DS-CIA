#include <math.h>

#include "map.h"

class VEBTree {
private:
  HashMap clusters;
  VEBTree *summary;
  int u_size;
  int min, max;

  int high(int);
  int low(int);
  int index(int, int);
  int root(int);

public:
  VEBTree(int size) : u_size(size), min(-1), max(-1) {
    if (size > 2) {
      int cluster_size = root(size);
      summary = new VEBTree(cluster_size);
    } else {
      summary = NULL;
    }
  }

  ~VEBTree() {
    // TODO Free memory properly
  }

  void insert(int);
  void remove(int);
  bool search(int);
  int successor(int);
  int predecessor(int);
  int getmin();
  int getmax();
};

void VEBTree::insert(int x) {
  if (min == -1) {
    min = max = x;
    return;
  }
  if (x < min) {
    int tmp = x;
    x = min;
    min = tmp;
  }
  if (x > max) {
    max = x;
  }
  int high_x = high(x);
  if (clusters.get(high_x) == nullptr) {
    summary->insert(high_x);
    clusters.insert(high_x, new VEBTree(root(u_size)));
  }
  clusters.get(high_x)->insert(low(x));
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
    int high_x = high(num);
    if (num == min) {
      int min_low = clusters.get(high_x)->getmin();
      if (min_low != -1) {
        num = index(high_x, min_low);
        min = num;
      } else {
        if (summary != nullptr) {
          int summary_min = summary->getmin();
          if (summary_min != -1) {
            min = index(summary_min, clusters.get(summary_min)->getmin());
          } else {
            min = max;
          }
        } else {
          min = max;
        }
      }
    }

    VEBTree *cluster_node = clusters.get(high_x);

    if (cluster_node != nullptr) {
      cluster_node->remove(low(num));
      if (cluster_node->getmin() == -1) {
        // TODO Delete cluster node here
        clusters.remove(high_x);
        if (summary != nullptr) {
          summary->remove(high_x);
        }
      }
    }

    if (num == max && summary != nullptr) {
      int summary_max = summary->getmax();
      if (summary_max != -1) {
        max = index(summary_max, clusters.get(summary_max)->getmax());
      } else {
        max = min;
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

  VEBTree *cluster = clusters.get(high(x));
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

    if (clusters.get(i) != nullptr && low(num < clusters.get(i)->max)) {
      j = clusters.get(i)->successor(low(num));
    } else {
      i = summary->successor(i);
      if (i == -1) {
        return -1;
      }
      j = clusters.get(i)->min;
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

    if (clusters.get(i) != nullptr && low(num) > clusters.get(i)->min) {
      j = clusters.get(i)->predecessor(low(num));
    } else {
      i = summary->predecessor(i);
      if (i == -1) {
        if (min != -1 && num > min) {
          return min;
        } else {
          return -1;
        }
      }
      j = clusters.get(i)->max;
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
