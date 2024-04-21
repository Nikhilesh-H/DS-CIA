#include <iostream>
#include <queue>

using namespace std;

class Node {
public:
  int key;
  int data;
  Node *left;
  Node *right;
};

class treap {
private:
  struct Node *root;

  Node *rotateRight(Node *);
  Node *rotateLeft(Node *);
  void inorder(Node *);
  Node *insert(int, int, Node *);
  void levelOrderTraversal(Node *);
  void displayHandler(Node *);

public:
  treap() : root(nullptr) {}

  int insert(int, int);
  void display();
};

int main() {
  int choice, key, data;
  treap tree;

  while (1) {
    cout << endl << "Menu:" << endl;
    cout << "\t1. Insert" << endl;
    cout << "\t2. Delete" << endl;
    cout << "\t3. Search" << endl;
    cout << "\t4. Display" << endl;
    cout << "\t5. Exit" << endl;
    cout << "Enter you choice: ";

    cin >> choice;
    switch (choice) {
    case 1:
      cout << "Enter key: ";
      cin >> key;

      cout << "Enter data: ";
      cin >> data;

      if (tree.insert(key, data)) {
        cout << "Successfully inserted (" << key << "," << data << ")" << endl;
      } else {
        cout << "Insertion unsuccessfull." << endl;
      }

      break;
    case 4:
      tree.display();

      break;
    case 5:
      return 0;
    default:
      cout << "Error! Enter a valid choice." << endl;
    }
  }
  return 0;
}

// Method to insert a node into the treap - O(log n)
int treap::insert(int key, int data) {
  root = insert(key, data, root);

  if (root == nullptr) {
    return 0;
  }

  return 1;
}

Node *treap::insert(int key, int data, struct Node *temp) {
  if (temp == nullptr) {
    Node *newnode = new Node;

    newnode->key = key;
    newnode->data = data;
    newnode->left = nullptr;
    newnode->right = nullptr;

    if (root == nullptr) {
      root = newnode;
    }

    return newnode;
  } else if (temp->key > key) {
    temp->left = insert(key, data, temp->left);

    if (temp->left != nullptr && temp->left->data > temp->data) {
      temp = rotateRight(temp);
    }
  } else {
    temp->right = insert(key, data, temp->right);

    if (temp->right != nullptr && temp->right->data > temp->data) {
      temp = rotateLeft(temp);
    }
  }
  return temp;
}

void treap::displayHandler(struct Node *temp) {
  cout << "Inorder display of treap :" << endl;
  inorder(temp);
  cout << endl;

  cout << "Heapview of treap :" << endl;
  levelOrderTraversal(temp);
  cout << endl;
}

void treap::display() {
  displayHandler(root);
}

void treap::inorder(struct Node *temp) {
  if (temp == nullptr) {
    return;
  }

  inorder(temp->left);
  cout << "(" << temp->key << "," << temp->data << ") ";
  inorder(temp->right);
}

Node *treap::rotateRight(struct Node *y) {
  struct Node *x = y->left;
  struct Node *T2 = x->right;

  x->right = y;
  y->left = T2;

  return x;
}

Node *treap::rotateLeft(struct Node *x) {
  struct Node *y = x->right;
  struct Node *T2 = y->left;

  y->left = x;
  x->right = T2;

  return y;
}

void treap::levelOrderTraversal(struct Node *temp) {
  if (temp == nullptr) {
    return;
  }

  queue<Node *> q;
  q.push(root);

  while (!q.empty()) {
    int nodeCount = q.size();

    while (nodeCount > 0) {
      struct Node *node = q.front();
      cout << node->data;

      q.pop();
      if (node->left) {
        q.push(node->left);
      }
      if (node->right) {
        q.push(node->right);
      }

      nodeCount--;
    }
  }
}
