//To implement Queue ADT using linked list

#include<stdio.h>
#include<stdlib.h>

class Node
{
  public:
    int key;
    int data;
    Node *left;
    Node *right;
};


class queue{
    private:
        struct node{
            Node *data;
            struct node* next;
        };
        struct node* front;
        struct node* rear;
        int siz;
    public:
        queue(){
            front=NULL;
            rear=NULL;
            siz=0;
        }
        ~queue() {
            while (front != nullptr) {
                struct node* temp = front;
                front = front->next;
                delete temp;
            }
        }
        int enqueue(Node*);
        Node* dequeue(void);
        Node* frontpeek(void);
        int size(void);
        
};

//Method to enqueue a number into the queue - O(1)
int queue::enqueue(Node* data){
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    if (newnode==NULL){
        return 0;
    }
    newnode->data=data;
    newnode->next=NULL;
    if (front==NULL){
        front=newnode;
    }
    else{
        rear->next=newnode;
    }
    rear=newnode;
    siz++;
    return 1;
}

//Method to dequeue a number from the queue - O(1)
Node* queue::dequeue(void){
    if (front==NULL){
        return nullptr;
    }
    else{
        struct node* temp=front;
        Node* res=temp->data;
        front=front->next;
        free(temp);
        siz--;
        return res;
    }
}

//Method to view the frontpeek of the queue - O(1)
Node* queue::frontpeek(void){
    if (front==NULL){
        return nullptr;
    }
    return front->data;
}

//Method to return the size of the queue - O(1)
int queue::size(void){
    return siz;
}
