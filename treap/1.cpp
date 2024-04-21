#include <stdio.h>
#include <stdlib.h>
#include <queue>

class treap{
    private:
        struct node{
            int key;
            int data;
            struct node* left;
            struct node* right;
        };
        struct node* root;
        struct node* rotateRight(struct node*);
        struct node* rotateLeft(struct node*);
        void inorder(struct node*);
        struct node* insert(int key, int data, struct node* temp);
        void levelOrderTraversal(struct node*);
    public:
        treap(){
            root = NULL;
        }
        int insert(int , int );
        struct node* del(int,struct node*);
        void display(struct node*);
        struct node* getroot(void);
        int search(int, struct node*);
};

int main(){
    int choice;
    int key;
    int data;
    treap t;
    while(1){
        printf("\nMenu:\n\t1. Insert\n\t2. Delete\n\t3. Search\n\t4. Display\n\t5. Exit\nEnter you choice : ");
        scanf("%d",&choice);
        switch(choice){
            case 1:{
                printf("Enter key : ");
                scanf("%d",&key);
                printf("Enter data : ");
                scanf("%d",&data);
                if(t.insert(key, data)){
                    printf("Successfully inserted (%d,%d).\n",key,data);
                }
                else{
                    printf("Insertion unsuccessfull.\n");
                }
                break;
            }
            case 2:{
                printf("Enter key : ");
                scanf("%d",&key);
                if(t.search(key, t.getroot())){
                    t.del(key,t.getroot());
                    printf("Successfully deleted %d\n", key);
                }
                else{
                    printf("%d - Not found.\n", key);
                }
                break;
            }
            case 3:{
                printf("Enter key : ");
                scanf("%d",&key);
                if(t.search(key, t.getroot())){
                    printf("%d - Found.\n",key);
                }
                else{
                    printf("%d - Not found.\n", key);
                }
                break;
            }
            case 4:{
                t.display(t.getroot());
                break;
            }
            case 5:{
                exit(0);
            }
            default:{
                printf("Error! Enter a valid choice.\n");
            }
        }
    }
    return 0;
}

//Method to get root of treap - O(1)
struct treap::node* treap::getroot(){
    return root;
}

//Method to insert a node into the treap - O(log n)
int treap::insert(int key, int data){
    root = insert(key, data, root);
    if (root == NULL){
        return 0;
    }
    return 1;
}

treap::node* treap::insert(int key, int data, struct node* temp){
    if (temp == NULL){
        struct node *newnode = (struct node*)malloc(sizeof(struct node));
        newnode -> key = key;
        newnode -> data = data;
        newnode -> left = NULL;
        newnode -> right = NULL;
        if (root == NULL){
            root = newnode;
        }
        return newnode; 
    }
    else if (temp -> key > key){
        temp ->left = insert(key, data, temp -> left);
        if (temp->left != NULL && temp->left->data > temp->data) {
            temp = rotateRight(temp);
        }
    }
    else{
        temp -> right = insert(key, data, temp -> right);
        if (temp->right != NULL && temp->right->data > temp->data) {
            temp = rotateLeft(temp);
        }
    }
    return temp;
}


//Method to display the treap - O(n)
void treap::display(struct node* temp){
    if (root==NULL){
        printf("Empty treap!\n");
        return;
    }
    printf("Inorder display of treap :\n");
    inorder(temp);
    printf("\n");
    printf("Heapview of treap :\n");
    levelOrderTraversal(temp);
    printf("\n");
}

void treap::inorder(struct node* temp){
    if(temp==NULL){
        return;
    }
    inorder(temp->left);
    printf("(%d,%d) ",temp->key, temp->data);
    inorder(temp->right);
}

treap::node* treap::rotateRight(struct node* y) {
    struct node* x = y->left;
    struct node* T2 = x->right;
    x->right = y;
    y->left = T2;
    return x;
}

treap::node* treap::rotateLeft(struct node* x) {
    struct node* y = x->right;
    struct node* T2 = y->left;
    y->left = x;
    x->right = T2;
    return y;
}

void treap::levelOrderTraversal(struct node *temp) {
    if (temp == NULL)
        return;
    std::queue<node*> q;
    q.push(temp);
    while (!q.empty()) {
        int nodeCount = q.size();
        while (nodeCount > 0) {
            struct node* node = q.front();
            printf("(%d,%d) ",node->key, node->data);
            q.pop();
            if (node->left)
                q.push(node->left);
            if (node->right)
                q.push(node->right);
            nodeCount--;
        }
        printf("\n");
    }
}

//method to check if a key is present in the treap
int treap::search(int num, struct node* temp){
    if(temp==NULL){
        return 0;
    }
    if(num==temp->key){
        return 1;
    }
    else if(num<temp->key){
        if (temp->left!=NULL){
            return search(num,temp->left);
        }
    }
    else{
        if (temp->right!=NULL){
            return search(num,temp->right);
        }
    }
    return 0;
}

//Method to delete a node a from the treap 
treap::node* treap::del(int num, struct node* temp) {
    if (temp == NULL)
        return temp;
    
    if (num < temp->key)
        temp->left = del(num, temp->left);
    else if (num > temp->key)
        temp->right = del(num, temp->right);
    else {
        if (temp == root && (temp->left == NULL || temp->right == NULL)) {
            // Node to be deleted is the root node and has at most one child
            if (temp->left == NULL && temp->right == NULL) {
                free(temp);
                root = NULL;
            } else if (temp->left == NULL) {
                struct node* rightChild = temp->right;
                free(temp);
                root = rightChild;
            } else {
                struct node* leftChild = temp->left;
                free(temp);
                root = leftChild;
            }
            return root;
        } else {
            if (temp->left == NULL) {
                struct node* rightChild = temp->right;
                free(temp);
                return rightChild;
            } else if (temp->right == NULL) {
                struct node* leftChild = temp->left;
                free(temp);
                return leftChild;
            } else {
                struct node* succParent = temp;
                struct node* succ = temp->right;
                while (succ->left != NULL) {
                    succParent = succ;
                    succ = succ->left;
                }
                temp->key = succ->key;
                temp->data = succ->data;
                if (succParent != temp)
                    succParent->left = del(succ->key, succParent->left);
                else
                    succParent->right = del(succ->key, succParent->right);
                while (temp->left != NULL && temp->right != NULL &&
                       (temp->left->data > temp->data || temp->right->data > temp->data)) {
                    if (temp->left->data > temp->right->data) {
                        temp = rotateRight(temp);
                    } else {
                        temp = rotateLeft(temp);
                    }
                }
            }
        }
    }
    return temp;
}
