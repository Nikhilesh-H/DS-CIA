#include <stdio.h>
#include <stdlib.h>
#define len 100

class treap{
    private:
        struct node{
            int key;
            int data;
            struct node* left;
            struct node* right;
        };
        struct node* root;
        int arr[len];
    public:
        treap(){
            root = NULL;
        }
        struct node* getroot();
        struct node* insert(int, int, struct node*);
        struct node* insert_tree(int, int, struct node*);
        void inorder(struct node*);
};

int main(){
    int choice;
    int key;
    int data;
    treap t;
    while(1){
        printf("\nMenu:\n\t1. Insert\n\t2. Delete\n\t3. Search\n\t4. Inorder display\n\t5. Exit\nEnter you choice : ");
        scanf("%d",&choice);
        switch(choice){
            case 1:{
                printf("Enter key : ");
                scanf("%d",&key);
                printf("Enter data : ");
                scanf("%d",&data);
                if(t.insert(key, data, t.getroot())){
                    printf("Successfully inserted (%d,%d).\n",key,data);
                }
                else{
                    printf("Insertion unsuccessfull.\n");
                }
                break;
            }
            case 4:{
                t.inorder(t.getroot());
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
struct treap::node* treap::insert(int key, int data, struct node*temp){
    insert_tree(key,data,temp);
    //Heapification should come here
    return root;
}

struct treap::node* treap::insert_tree(int key, int data, struct node* temp){
    if (temp == NULL){
        struct node *newnode = (struct node*)malloc(sizeof(struct node));
        newnode -> key = key;
        newnode -> data = data;
        newnode -> left = NULL;
        newnode -> right = NULL;
        if (root == NULL){
            root = newnode;
            return root;
        }
        else{
            temp = newnode;
            return temp;
        }
    }
    else if (temp -> key > key){
        temp ->left = insert_tree(key, data, temp -> left);
    }
    else{
        temp -> right = insert_tree(key, data, temp -> right);
    }
    return temp;
}

void treap::inorder(struct node* temp){
    if(temp==NULL){
        return;
    }
    inorder(temp->left);
    printf("(%d,%d) ",temp->key, temp->data);
    inorder(temp->right);
}
