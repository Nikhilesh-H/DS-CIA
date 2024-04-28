#include <cmath>
#include <vector>

using namespace std;

class VEBTree
{
  private:
    vector<VEBTree *> clusters;
    VEBTree *summary;
    int u_size;
    int min, max;

    int high(int);
    int low(int);
    int index(int, int);
    int root(int);

  public:
    VEBTree(int size) : u_size(size), min(-1), max(-1), summary(nullptr)
    {
        if (size > 2)
        {
            int cluster_size = root(size);
            summary = new VEBTree(cluster_size);
            clusters.resize(cluster_size, nullptr);

            for (int i = 0; i < cluster_size; i++)
            {
                clusters[i] = new VEBTree(cluster_size);
            }
        }
    }

    ~VEBTree()
    {
        for (auto &cluster : clusters)
        {
            delete cluster;
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

void VEBTree::insert(int num)
{
    if (min == -1)
    {
        // If the tree is empty, set both min and max to the inserted value
        min = max = num;
        return;
    }

    if (num < min)
    {
        // Swap min and num
        swap(min, num);
    }

    if (num > max)
    {
        // Update max if necessary
        max = num;
    }

    // Check if the tree has more than two elements
    if (u_size > 2)
    {
        int high_x = high(num);
        int low_x = low(num);

        // If the cluster doesn't exist, create it
        if (clusters[high_x] == nullptr)
        {
            summary->insert(high_x);                      // Insert the high-order bit into the summary
            clusters[high_x] = new VEBTree(root(u_size)); // Create a new cluster
        }

        // Insert the low-order bits into the corresponding cluster
        clusters[high_x]->insert(low_x);
    }
}

void VEBTree::remove(int num)
{
    if (min == -1)
        return;

    if (num == min)
    {
        int i = summary->getmin();
        if (i == -1)
        {
            min = max = -1;
            return;
        }
        num = min = index(i, clusters[i]->getmin());
    }

    int high_x = high(num);
    int low_x = low(num);

    if (clusters[high_x] != nullptr)
    {
        clusters[high_x]->remove(low_x);
        if (clusters[high_x]->getmin() == -1)
        {
            summary->remove(high_x);
            delete clusters[high_x];
            clusters[high_x] = nullptr;
        }
    }

    if (num == max)
    {
        int i = summary->getmax();
        if (i == -1)
        {
            max = min;
        }
        else
        {
            max = index(i, clusters[i]->getmax());
        }
    }
}

bool VEBTree::search(int x)
{
    if (min == -1)
    {
        return false;
    }

    if (x == min || x == max)
    {
        return true;
    }

    if (u_size <= 2)
    {
        return false;
    }

    VEBTree *cluster = clusters[high(x)];
    if (cluster == nullptr)
    {
        return false;
    }
    else
    {
        return cluster->search(low(x));
    }
}

int VEBTree::successor(int num)
{
    if (u_size == 2)
    {
        if (num == 0 && max == 1)
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }
    else if (min != -1 && num < min)
    {
        return min;
    }
    else
    {
        int i = high(num);
        int j;

        if (clusters[i] != nullptr && low(num) < clusters[i]->max)
        {
            j = clusters[i]->successor(low(num));
        }
        else if (summary != nullptr)
        {
            i = summary->successor(i);
            if (i != -1 && clusters[i] != nullptr)
            {
                j = clusters[i]->getmin();
            }
            else
            {
                return -1;
            }
        }
        else
        {
            return -1;
        }

        return index(i, j);
    }
}

int VEBTree::predecessor(int num)
{
    if (u_size == 2)
    {
        if (num == 1 && min == 0)
        {
            return 0;
        }
        else
        {
            return -1;
        }
    }
    else if (max != -1 && num > max)
    {
        return max;
    }
    else
    {
        int i = high(num);
        int j;

        if (clusters[i] != nullptr && low(num) > clusters[i]->min)
        {
            j = clusters[i]->predecessor(low(num));
        }
        else
        {
            i = summary->predecessor(i);
            if (i == -1)
            {
                if (min != -1 && num > min)
                {
                    return min;
                }
                else
                {
                    return -1;
                }
            }
            j = clusters[i]->max;
        }

        return index(i, j);
    }
}

int VEBTree::getmin()
{
    return min;
}

int VEBTree::getmax()
{
    return max;
}

int VEBTree::high(int num)
{
    return floor(num / root(u_size));
}

int VEBTree::low(int num)
{
    return num % root(u_size);
}

int VEBTree::index(int high, int low)
{
    return high * root(u_size) + low;
}

int VEBTree::root(int num)
{
    return pow(2, ceil(log2(num) / 2));
}
