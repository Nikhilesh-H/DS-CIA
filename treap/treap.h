#include "queue.h" // Included for level order display
#include <stdio.h>
#include <stdlib.h>


class Treap
{
  private:
    Node *root;

    Node *insert(int, int, Node *);
    Node *del(int, Node *);
    int search(int, Node *);
    void display(Node *);
    Node *rotateRight(Node *);
    Node *rotateLeft(Node *);
    void inOrderTraversal(Node *);
    void levelOrderTraversal(Node *);
    Node *getroot(void);
    void destroyTree(Node *);

  public:
    Treap()
    {
        root = NULL;
    }

    ~Treap()
    {
        destroyTree(root);
    }

    int insert(int, int);
    int del(int);
    void display(void);
    int search(int);
};

// Method to get root of treap - O(1)
Node *Treap::getroot()
{
    return root;
}

// Method to insert a node into the treap - O(log n)
int Treap::insert(int key, int data)
{
    root = insert(key, data, root);

    if (root == NULL)
    {
        return 0;
    }

    return 1;
}

Node *Treap::insert(int key, int data, Node *temp)
{
    if (temp == NULL)
    {
        Node *newnode = (Node *)malloc(sizeof(Node));
        newnode->key = key;
        newnode->data = data;
        newnode->left = NULL;
        newnode->right = NULL;

        if (root == NULL)
        {
            root = newnode;
        }

        return newnode;
    }
    else if (temp->key > key)
    {
        temp->left = insert(key, data, temp->left);

        if (temp->left != NULL && temp->left->data > temp->data)
        {
            temp = rotateRight(temp);
        }
    }
    else
    {
        temp->right = insert(key, data, temp->right);

        if (temp->right != NULL && temp->right->data > temp->data)
        {
            temp = rotateLeft(temp);
        }
    }
    return temp;
}

Node *Treap::rotateRight(Node *temp)
{
    Node *leftNode = temp->left;
    Node *rightNode = leftNode->right;

    leftNode->right = temp;
    temp->left = rightNode;

    return leftNode;
}

Node *Treap::rotateLeft(Node *temp)
{
    Node *rightNode = temp->right;
    Node *leftNode = rightNode->left;

    rightNode->left = temp;
    temp->right = leftNode;

    return rightNode;
}

// Method to display the treap - O(n)
void Treap::display(Node *temp)
{
    if (root == NULL)
    {
        printf("Empty treap!\n");
        return;
    }

    printf("Inorder display of treap :\n");
    inOrderTraversal(temp);
    printf("\n");

    printf("Heapview of treap :\n");
    levelOrderTraversal(temp);
    printf("\n");
}

void Treap::inOrderTraversal(Node *temp)
{
    if (temp == NULL)
    {
        return;
    }

    inOrderTraversal(temp->left);
    printf("(%d,%d) ", temp->key, temp->data);
    inOrderTraversal(temp->right);
}

void Treap::levelOrderTraversal(Node *temp)
{
    if (temp == NULL)
    {
        return;
    }

    queue q;
    q.enqueue(temp);

    while (q.size() != 0)
    {
        int nodeCount = q.size();

        while (nodeCount > 0)
        {
            Node *node = q.frontpeek();
            printf("(%d,%d) ", node->key, node->data);

            q.dequeue();
            if (node->left)
            {
                q.enqueue(node->left);
            }

            if (node->right)
            {
                q.enqueue(node->right);
            }

            nodeCount--;
        }
        printf("\n");
    }
}

// Method to check if a key is present in the treap - O(log n)
int Treap::search(int num, Node *temp)
{
    if (temp == NULL)
    {
        return 0;
    }

    if (num == temp->key)
    {
        return 1;
    }
    else if (num < temp->key)
    {
        if (temp->left != NULL)
        {
            return search(num, temp->left);
        }
    }
    else
    {
        if (temp->right != NULL)
        {
            return search(num, temp->right);
        }
    }
    return 0;
}

// Method to delete a node a from the treap - O(log n)
Node *Treap::del(int num, Node *temp)
{
    if (temp == NULL)
    {
        return temp;
    }

    if (num < temp->key)
    {
        temp->left = del(num, temp->left);
    }
    else if (num > temp->key)
    {
        temp->right = del(num, temp->right);
    }
    else
    {
        if (temp == root && (temp->left == NULL || temp->right == NULL))
        {
            if (temp->left == NULL && temp->right == NULL)
            {
                free(temp);
                root = NULL;
            }
            else if (temp->left == NULL)
            {
                Node *rightChild = temp->right;
                free(temp);
                root = rightChild;
            }
            else
            {
                Node *leftChild = temp->left;
                free(temp);
                root = leftChild;
            }
            return root;
        }
        else
        {
            if (temp->left == NULL)
            {
                Node *rightChild = temp->right;
                free(temp);
                return rightChild;
            }
            else if (temp->right == NULL)
            {
                Node *leftChild = temp->left;
                free(temp);
                return leftChild;
            }
            else
            {
                Node *succParent = temp;
                Node *succ = temp->right;

                while (succ->left != NULL)
                {
                    succParent = succ;
                    succ = succ->left;
                }

                temp->key = succ->key;
                temp->data = succ->data;

                if (succParent != temp)
                {
                    succParent->left = del(succ->key, succParent->left);
                }
                else
                {
                    succParent->right = del(succ->key, succParent->right);
                }

                while (temp->left != NULL && temp->right != NULL &&
                       (temp->left->data > temp->data || temp->right->data > temp->data))
                {
                    if (temp->left->data > temp->right->data)
                    {
                        temp = rotateRight(temp);
                    }
                    else
                    {
                        temp = rotateLeft(temp);
                    }
                }
            }
        }
    }
    return temp;
}

// Method to delete the memory allocated to the tree - O(n)
void Treap::destroyTree(Node *temp)
{
    if (temp != nullptr)
    {
        destroyTree(temp->left);
        destroyTree(temp->right);
        free(temp);
    }
}

int Treap::del(int num)
{
    del(num, getroot());
    return 1;   
}

void Treap::display(void)
{
    display(getroot());
}

int Treap::search(int num)
{
    return search(num, getroot());
}
