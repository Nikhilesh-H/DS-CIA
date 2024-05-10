#include <math.h>
#include <unordered_map>

using namespace std;

class VEBTree
{
  private:
    VEBTree *summary;
    unordered_map<int, VEBTree *> cluster;
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
        }
    }

    ~VEBTree()
    {
        for (auto pair : cluster)
        {
            delete pair.second;
        }
        cluster.clear();

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
        min = max = num;
        return;
    }

    if (num < min)
    {
        swap(min, num);
    }

    if (num > max)
    {
        max = num;
    }

    if (u_size > 2)
    {
        if (cluster.find(high(num)) == cluster.end())
        {
            summary->insert(high(num));
            cluster[high(num)] = new VEBTree(root(u_size));
        }

        cluster[high(num)]->insert(low(num));
    }
}

void VEBTree::remove(int num)
{
    if (num == min)
    {
        int i = summary->getmin();
        if (i == -1)
        {
            min = max = -1;
            return;
        }
        num = min = index(i, cluster[i]->getmin());
    }

    if (cluster.find(high(num)) != cluster.end())
    {
        cluster[high(num)]->remove(low(num));
        if (cluster[high(num)]->getmin() == -1)
        {
            summary->remove(high(num));
            delete cluster[high(num)];
            cluster.erase(high(num));
        }
    }

    if (num == max)
    {
        if (summary->getmax() == -1)
        {
            max = min;
        }
        else
        {
            int i = summary->getmax();
            max = index(i, cluster[i]->getmax());
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

    if (cluster.find(high(x)) != cluster.end())
    {
        return cluster[high(x)]->search(low(x));
    }

    return false;
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

        if (cluster[i] != nullptr && low(num) < cluster[i]->max)
        {
            j = cluster[i]->successor(low(num));
        }
        else
        {
            i = summary->successor(high(num));
            if (i != -1 && cluster[i] != nullptr)
            {
                j = cluster[i]->getmin();
            }
            else
            {
                return -1;
            }
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

        if (cluster[i] != nullptr && low(num) > cluster[i]->min)
        {
            j = cluster[i]->predecessor(low(num));
        }
        else
        {
            i = summary->predecessor(high(num));
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
            j = cluster[i]->getmax();
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
